#ifndef SDCONFIG_H
#define SDCONFIG_H

#include <SD.h>
#include <SPI.h>

#define SD_CS_PIN BUILTIN_SDCARD
#define CONFIG_FILE "brightness.bin"

#define SD_DEBUG 0

// sdconfig structure for brightness
struct Brightnesssdconfig {
  uint8_t version;      // sdconfig version for future compatibility
  int brightness;       // Current brightness value
  uint8_t checksum;     // Simple checksum for data integrity
};

class sdconfig {
public:
  static bool init();
  static bool saveBrightness(int brightness);
  static int loadBrightness(int defaultValue = 20);

private:
  static bool sdInitialized;
  static uint8_t calculateChecksum(const Brightnesssdconfig& config);
  static bool validatesdconfig(const Brightnesssdconfig& config);
};

// Static member initialization
bool sdconfig::sdInitialized = false;

bool sdconfig::init() {
  if (sdInitialized) {
    #if SD_DEBUG
      Serial.println("SD already initialized");
    #endif
    return true;
  }
  #if SD_DEBUG
    Serial.print("Attempting to initialize SD card on pin ");
    Serial.println(SD_CS_PIN);
  #endif
  
  if (SD.begin(SD_CS_PIN)) {
    sdInitialized = true;
    #if SD_DEBUG
      Serial.println("SD card initialized successfully");
    #endif
    return true;
  }

  Serial.println("SD card initialization FAILED");
  return false;
}

uint8_t sdconfig::calculateChecksum(const Brightnesssdconfig& config) {
  uint8_t checksum = 0;
  checksum ^= config.version;
  checksum ^= (config.brightness & 0xFF);
  checksum ^= ((config.brightness >> 8) & 0xFF);
  return checksum;
}

bool sdconfig::validatesdconfig(const Brightnesssdconfig& config) {
  // Check version
  if (config.version != 1) {
    return false;
  }

  // Check brightness range (0-255)
  if (config.brightness < 0 || config.brightness > 255) {
    return false;
  }

  // Check checksum
  uint8_t expectedChecksum = calculateChecksum(config);
  if (config.checksum != expectedChecksum) {
    return false;
  }

  return true;
}

bool sdconfig::saveBrightness(int brightness) {
  #if SD_DEBUG
    Serial.print("Attempting to save brightness: ");
    Serial.println(brightness);
  #endif
  
  if (!init()) {
    Serial.println("Save failed: SD not initialized");
    return false;
  }

  Brightnesssdconfig config;
  config.version = 1;
  config.brightness = brightness;
  config.checksum = calculateChecksum(config);

  // Remove existing file first to ensure clean write
  if (SD.exists(CONFIG_FILE)) {
    SD.remove(CONFIG_FILE);
  }

  File file = SD.open(CONFIG_FILE, FILE_WRITE);
  if (!file) {
    Serial.println("Save failed: Unable to open file for writing");
    return false;
  }

  // Write the config structure
  size_t written = file.write((uint8_t*)&config, sizeof(config));
  file.close();

  if (written == sizeof(config)) {
    #if SD_DEBUG
      Serial.println("Brightness saved successfully");
    #endif
  } else {
    Serial.println("Save failed: Incomplete write");
  }

  return written == sizeof(config);
}

int sdconfig::loadBrightness(int defaultValue) {
  if (!init()) {
    return defaultValue;
  }

  if (!SD.exists(CONFIG_FILE)) {
    return defaultValue;
  }

  File file = SD.open(CONFIG_FILE, FILE_READ);
  if (!file) {
    return defaultValue;
  }

  Brightnesssdconfig config;
  size_t bytesRead = file.read((uint8_t*)&config, sizeof(config));
  file.close();

  if (bytesRead != sizeof(config)) {
    return defaultValue;
  }

  if (!validatesdconfig(config)) {
    return defaultValue;
  }

  return config.brightness;
}

#endif


