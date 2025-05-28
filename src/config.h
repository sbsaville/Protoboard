#ifndef CONFIG_H
#define CONFIG_H

#include <SD.h>
#include <SPI.h>

// SD card configuration
#define SD_CS_PIN BUILTIN_SDCARD  // Teensy 3.6 built-in SD card
#define CONFIG_FILE "brightness.bin"

// Config structure for brightness
struct BrightnessConfig {
  uint8_t version;      // Config version for future compatibility
  int brightness;       // Current brightness value
  uint8_t checksum;     // Simple checksum for data integrity
};

class Config {
public:
  static bool init();
  static bool saveBrightness(int brightness);
  static int loadBrightness(int defaultValue = 20);
  
private:
  static bool sdInitialized;
  static uint8_t calculateChecksum(const BrightnessConfig& config);
  static bool validateConfig(const BrightnessConfig& config);
};

// Static member initialization
bool Config::sdInitialized = false;

bool Config::init() {
  if (sdInitialized) {
    return true;
  }
  
  if (SD.begin(SD_CS_PIN)) {
    sdInitialized = true;
    return true;
  }
  
  return false;
}

uint8_t Config::calculateChecksum(const BrightnessConfig& config) {
  uint8_t checksum = 0;
  checksum ^= config.version;
  checksum ^= (config.brightness & 0xFF);
  checksum ^= ((config.brightness >> 8) & 0xFF);
  return checksum;
}

bool Config::validateConfig(const BrightnessConfig& config) {
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

bool Config::saveBrightness(int brightness) {
  if (!init()) {
    return false;
  }
  
  BrightnessConfig config;
  config.version = 1;
  config.brightness = brightness;
  config.checksum = calculateChecksum(config);
  
  File file = SD.open(CONFIG_FILE, FILE_WRITE);
  if (!file) {
    return false;
  }
  
  // Write the config structure
  size_t written = file.write((uint8_t*)&config, sizeof(config));
  file.close();
  
  return written == sizeof(config);
}

int Config::loadBrightness(int defaultValue) {
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
  
  BrightnessConfig config;
  size_t bytesRead = file.read((uint8_t*)&config, sizeof(config));
  file.close();
  
  if (bytesRead != sizeof(config)) {
    return defaultValue;
  }
  
  if (!validateConfig(config)) {
    return defaultValue;
  }
  
  return config.brightness;
}

#endif
