#ifndef TRILLBAR_H
#define TRILLBAR_H

#include "main.h"

#if DEBUG
  #define TRILL_DEBUG 0
  #define TRILL_MOMENTUM_DEBUG 0
  #define ACCEL_DEBUG 0
  #define RATE_DEBUG 1
#endif

// extern bool loopTimer;
// extern unsigned long loopStartTime;
// extern unsigned long loopDuration;
// extern unsigned long loopCheckpoint;
// extern unsigned long deltaTime;

void scanLEDs(LayoutKey* (*layoutMatrix)[columnsCount]);
void ledsDEC();
void ledsINC();

class trillbar {
public:
  static void setup();
  static void loop();
  static bool isLedOverride();
  static int getMode();
  static void setMode(int newMode);

  static const int MODE_ARROWS = 1;
  static const int MODE_BRIGHTNESS = 2;
  static const int MODE_SCROLL = 3;
  static const int MODE_MOUSE = 4;

private:
  static Trill sensor;

  static const float FILTER_WEIGHT;
  static const float TAP_THRESHOLD;

  static bool active;                         
  static unsigned long startTime;             
  static int count;                           
  static bool wasQuickTap;                    


  static int rawPos;                          
  static int lastRawPos;                      
  static int size;                            
  static int lastSize;                        
  static int adjustedSize;                    
  static int rawDelta;                        
  static float filteredDelta;                 
  static float accumulatedMovement;           

  static int spread;
  static int lastSpread;


  static int mode;
  static int holdCounter;
  static bool ledsOverride;

  // Momentum system
  static float velocity;
  static float friction;
  static float threshold;
  static bool momentumActive;
  static unsigned long lastUpdate;            // Timing for updates
  static const unsigned long updateInterval;  // ~60Hz updates

  // Timing control
  static unsigned long lastRead;              // Last sensor read time
  static unsigned long inactiveInterval;          // Default polling interval
  static unsigned long activeInterval;        // Faster polling when active

  // Flag for triple touch
  static bool tripleActionTriggered;          // Prevent repeated play/pause
  static bool quadActionTriggered;            // Prevent repeated mute

  static unsigned long lastTouchCountChange;
  static const unsigned int touchDebounceTime = 10;

  static float calculateSensitivity(int rawDelta);
  static float applyFilter(float input);
  static int processMovement();
  static void sendKeyPress(int key, int repeats);
  static void sendLeftKeys(int count);
  static void sendRightKeys(int count);
  static void handleScrolling(int direction, int magnitude);
  static void handleMode1(int actionUnits);   // Arrows
  static void handleMode2(int actionUnits);   // Brightness
  static void handleMode3(int actionUnits);   // Scrolling
  static void handleMode4(int actionUnits);   // Mouse movement
  static void handleDualTouch();              // Volume control
  static void handleTripleTouch();            // Media control
  static void handleQuadTouch();              // Mute control
  static void handleTouchRelease();
};

Trill trillbar::sensor;

const float trillbar::FILTER_WEIGHT = 0.5f;
const float trillbar::TAP_THRESHOLD = 300.0f;
const unsigned long trillbar::updateInterval = 16;

bool trillbar::active = false;
unsigned long trillbar::startTime = 0;
int trillbar::count = 0;
bool trillbar::wasQuickTap = false;
int trillbar::rawPos = 0;
int trillbar::lastRawPos = 0;
int trillbar::size = 0;
int trillbar::lastSize = 0;
int trillbar::adjustedSize = 0;
int trillbar::rawDelta = 0;
float trillbar::filteredDelta = 0;
float trillbar::accumulatedMovement = 0;
int trillbar::spread = 0;
int trillbar::lastSpread = 0;
int trillbar::mode = 1;
int trillbar::holdCounter = 0;
bool trillbar::ledsOverride = false;
float trillbar::velocity = 0.0f;
float trillbar::friction = 0.98f;
float trillbar::threshold = 0.3f;
bool trillbar::momentumActive = false;
unsigned long trillbar::lastUpdate = 0;
unsigned long trillbar::lastRead = 0;
unsigned long trillbar::inactiveInterval = 4;
unsigned long trillbar::activeInterval = 1;
bool trillbar::tripleActionTriggered = false;
bool trillbar::quadActionTriggered = false;
unsigned long trillbar::lastTouchCountChange = 0;

// Calculate adaptive sensitivity based on movement speed using a linear acceleration curve
float trillbar::calculateSensitivity(int rawDelta) {
  // Base sensitivity value
  const float baseSensitivity = 1.0f / 50.0f;

  // Use absolute value for calculations
  int absDelta = abs(rawDelta);

  // Define the range for scaling
  const int minDelta = 1;    // Below this, use minimum sensitivity
  const int maxDelta = 500;   // Above this, use maximum sensitivity

  // Define sensitivity multiplier range
  const float minMultiplier = 0.44f;   // For slow movements
  const float maxMultiplier = 3.0f;   // For fast movements

  // Calculate the normalized position within the range [0.0-1.0]
  float normalizedDelta = constrain(absDelta, minDelta, maxDelta);
  normalizedDelta = (normalizedDelta - minDelta) / (maxDelta - minDelta);

  // Linear interpolation between min and max multiplier
  float multiplier = minMultiplier + normalizedDelta * (maxMultiplier - minMultiplier);

  // Apply multiplier to base sensitivity
  float finalSensitivity = baseSensitivity * multiplier;

  // Diagnostic output - only output every N calls to avoid flooding serial
  static int debugCounter = 0;
  if (++debugCounter >= 4) { // Output every Nth call
    debugCounter = 0;

    #if ACCEL_DEBUG
    Serial.print("ACCEL: rawDelta=");
    Serial.print(rawDelta);
    Serial.print(" absDelta=");
    Serial.print(absDelta);
    Serial.print(" normalized=");
    Serial.print(normalizedDelta, 3);
    Serial.print(" multiplier=");
    Serial.print(multiplier, 3);
    Serial.print(" sensitivity=");
    Serial.println(finalSensitivity, 6);
    #endif
  }

  return finalSensitivity;
}

// Apply exponential smoothing filter
float trillbar::applyFilter(float input) {
  static float lastOutput = 0.0f;
  float output = (input * FILTER_WEIGHT) + (lastOutput * (1.0f - FILTER_WEIGHT));
  lastOutput = output;
  return output;
}

// Helper to send repeated key presses
void trillbar::sendKeyPress(int key, int repeats) {
  for (int i = 0; i < repeats; i++) {
    Keyboard.press(key);
    Keyboard.release(key);
  }
}

// Helper for left key presses
void trillbar::sendLeftKeys(int count) {
  if (count == 0) return;
  count = abs(count);
  sendKeyPress(KEY_LEFT, count);
}

// Helper for right key presses
void trillbar::sendRightKeys(int count) {
  if (count == 0) return;
  count = abs(count);
  sendKeyPress(KEY_RIGHT, count);
}

// Helper for mouse scrolling
void trillbar::handleScrolling(int direction, int magnitude) {
  if (magnitude == 0) return;
  Mouse.scroll(direction * magnitude);
}

// Process movement and return action units
int trillbar::processMovement() {
  // Skip movement processing during touch count debounce period
  if (millis() - lastTouchCountChange < touchDebounceTime) {
    return 0;
  }

  // Calculate raw delta
  rawDelta = rawPos - lastRawPos;

  #if ACCEL_DEBUG
  Serial.print("processMovement: rawPos=");
  Serial.print(rawPos);
  Serial.print(" lastRawPos=");
  Serial.print(lastRawPos);
  Serial.print(" rawDelta=");
  Serial.println(rawDelta);
  #endif

  // Apply adaptive sensitivity based on movement speed
  float sensitivity = calculateSensitivity(rawDelta);
  float scaledDelta = rawDelta * sensitivity;

  // Apply filtering for smoother movement
  filteredDelta = applyFilter(scaledDelta);

  // Accumulate fractional movements
  accumulatedMovement += filteredDelta;

  // Extract whole units of movement (integer part)
  int actionUnits = (int)accumulatedMovement;

  const int maxActionUnits = 5;
  actionUnits = max(actionUnits, -maxActionUnits);
  actionUnits = min(actionUnits, maxActionUnits);

  #if TRILL_DEBUG
  Serial.print(" actionUnits=");
  Serial.println(actionUnits);
  #endif

  // Keep only the fractional part for next time
  accumulatedMovement -= actionUnits;

  // Update momentum velocity based on filtered movement
  velocity = (velocity * 0.7f) + (filteredDelta * 0.3f * 2.5f);

  return actionUnits;
}

// Handle mode 1: arrow keys
void trillbar::handleMode1(int actionUnits) {
  if (actionUnits == 0) return;

  if (actionUnits > 0) {
    //sendLeftKeys(actionUnits);
  } else {
    //sendRightKeys(-actionUnits);
  }

  #if TRILL_DEBUG
  Serial.print("Arrow keys: ");
  Serial.println(actionUnits);
  #endif
}

// Handle mode 2: LED brightness
void trillbar::handleMode2(int actionUnits) {
  if (actionUnits == 0) return;

  ledsOverride = true;
  scanLEDs(layer0);

  if (actionUnits > 0) {
    for (int i = 0; i < actionUnits; i++) {
      ledsDEC();
    }
  } else {
    for (int i = 0; i < -actionUnits; i++) {
      ledsINC();
    }
  }

  #if TRILL_DEBUG
  Serial.print("Brightness: ");
  Serial.println(actionUnits);
  #endif
}

// Handle mode 3: Mouse scrolling
void trillbar::handleMode3(int actionUnits) {
  if (actionUnits == 0) return;

  handleScrolling(-actionUnits, 1);

  #if TRILL_MOMENTUM_DEBUG
  Serial.print("Manual scroll: ");
  Serial.print(-actionUnits);
  Serial.print(", Velocity: ");
  Serial.println(velocity);
  #endif
}

// Handle mode 4: Mouse movement
void trillbar::handleMode4(int actionUnits) {
  // Use raw delta instead of processed actionUnits for more direct control
  if (rawDelta == 0) return;

  // Mouse sensitivity - adjust this value to taste
  const float mouseSensitivity = 1.0f;
  int mouseUnits = (int)(rawDelta * mouseSensitivity);

  // Apply minimum threshold to avoid tiny movements
  if (abs(mouseUnits) < 1) return;
  Mouse.move(-mouseUnits, 0);

  #if TRILL_DEBUG
  Serial.print("Raw mouse movement - rawDelta: ");
  Serial.print(rawDelta);
  Serial.print(", mouseUnits: ");
  Serial.println(mouseUnits);
  #endif
}

// Handle dual touch (volume control)
void trillbar::handleDualTouch() {
  static int lastAvgPos = -1;

  // Calculate spread between touches
  int pos1 = sensor.touchLocation(0);
  int pos2 = sensor.touchLocation(1);

  // Calculate average position and spread
  int avgPos = (pos1 + pos2) / 2;
  int spread = abs(pos1 - pos2);

  // Update spread tracking
  lastSpread = spread;

  // FEATURE 1: VOLUME (based on horizontal position)
  // Initialize lastAvgPos if needed
  if (lastAvgPos == -1) {
    lastAvgPos = avgPos;
    return;
  }

  int avgPosDelta = avgPos - lastAvgPos;

  if (abs(avgPosDelta) > 30) {
    lastAvgPos = avgPos;

    if (avgPosDelta < 0) {
      sendKeyPress(KEY_MEDIA_VOLUME_INC, 1);
      #if TRILL_DEBUG
      Serial.println("Volume up");
      #endif
    } else {
      sendKeyPress(KEY_MEDIA_VOLUME_DEC, 1);
      #if TRILL_DEBUG
      Serial.println("Volume down");
      #endif
    }
  }
}

void trillbar::handleTripleTouch() {
  if (!tripleActionTriggered) {
    sendKeyPress(KEY_MEDIA_PLAY_PAUSE, 1);
    tripleActionTriggered = true;

    #if TRILL_DEBUG
    Serial.println("Play/Pause");
    #endif
  }
}

void trillbar::handleQuadTouch() {
  if (!quadActionTriggered) {
    sendKeyPress(KEY_MEDIA_MUTE, 1);
    quadActionTriggered = true;

    #if TRILL_DEBUG
    Serial.println("Mute");
    #endif
  }
}

void trillbar::handleTouchRelease() {
  unsigned long touchDuration = millis() - startTime;
  wasQuickTap = (touchDuration < TAP_THRESHOLD);

  /* Commented out tap detection play/pause
  if (wasQuickTap) {
    sendKeyPress(KEY_MEDIA_PLAY_PAUSE, 1);
    #if TRILL_DEBUG
    Serial.println("Tap gesture: Play/Pause");
    #endif
  }
  */

  ledsOverride = false;
  
  // Only save brightness if we were in brightness mode
  if (mode == MODE_BRIGHTNESS) {
    sdconfig::saveBrightness(brightness);
  }

  if (mode == MODE_SCROLL && abs(velocity) > threshold) {
    momentumActive = true;
    lastUpdate = millis();

    #if TRILL_MOMENTUM_DEBUG
    Serial.print("Starting momentum with velocity: ");
    Serial.print(velocity);
    Serial.print(", mode: ");
    Serial.println(mode);
    #endif
  }
  #if TRILL_MOMENTUM_DEBUG
  else if (mode == MODE_SCROLL) {
    Serial.print("Momentum not started. Velocity: ");
    Serial.print(velocity);
    Serial.print(", threshold: ");
    Serial.println(threshold);
  }
  #endif

  holdCounter = 0;
  tripleActionTriggered = false;
  quadActionTriggered = false;
}

// Public interface implementation
void trillbar::setup() {
  int ret = sensor.setup(Trill::TRILL_BAR);
  if(ret != 0) {
    #if TRILL_DEBUG
    Serial.println("Failed to initialize trillSensor");
    Serial.print("Error code: ");
    Serial.println(ret);
    #endif
  }
//  sensor.setScanSettings(0, 9);
////  (Speed, Resolution) - Speed goes from 3 to 0, Resolution from 9 to 16, default (0, 12)

//  sensor.setNoiseThreshold(4);
////  0 to 255, filters smaller values, default 4

//  sensor.setPrescaler(3);
////  1 to 8, seems to be a touch sensitivity multiplier, default 3

//  sensor.setAutoScanInterval(1);
////  nonzero value, default 1 (fastest)
}

void trillbar::loop() {

  unsigned long currentTime = millis();

  // Dynamic polling interval based on touch state
  unsigned long pollingInterval = active ? activeInterval : inactiveInterval;

  // Process momentum scrolling regardless of touch state
  if (momentumActive && currentTime - lastUpdate >= updateInterval) {
    lastUpdate = currentTime;

    // Apply friction to slow down
    velocity *= friction;

    if (abs(velocity) > threshold) {
      // CHANGE: Accumulate fractional scrolling over time
      static float scrollAccumulator = 0;
      scrollAccumulator += velocity;

      // Only scroll when we've accumulated a full unit
      int scrollAmount = (int)scrollAccumulator;

      if (scrollAmount != 0) {
        // Scroll by the accumulated amount
        Mouse.scroll(-scrollAmount);

        // Keep only the fractional part
        scrollAccumulator -= scrollAmount;

        #if TRILL_MOMENTUM_DEBUG
        Serial.print("Momentum scroll: ");
        Serial.print(scrollAmount);
        Serial.print(", Remaining: ");
        Serial.println(scrollAccumulator);
        #endif
      }
    } else {
      // Reset on stop
      momentumActive = false;
      velocity = 0;

      #if TRILL_MOMENTUM_DEBUG
      Serial.println("Momentum stopped");
      #endif
    }
  }

  // Read trill sensor at appropriate interval
  if (currentTime - lastRead >= pollingInterval) {

#if LOOP_TIMER_DEBUG
if (loopTimer) {
logThis = true;
loopDuration = micros() - loopStartTime;
deltaTime = loopDuration - loopCheckpoint;
loopCheckpoint = loopDuration;
Serial.print("scan: ");
Serial.print(scanCheckpoint);
Serial.print("  |  ");
Serial.print("pre-sensor Δ: ");
Serial.print(deltaTime);
Serial.print("  |  ");
}
#endif

    lastRead = currentTime;
    // Read sensor data
    sensor.read();

#if LOOP_TIMER_DEBUG
if (loopTimer && logThis) {
loopDuration = micros() - loopStartTime;
deltaTime = loopDuration - loopCheckpoint;
loopCheckpoint = loopDuration;
Serial.print("sensor read Δ: ");
Serial.print(deltaTime);
Serial.print("  |  ");
}
#endif

    // Get touch count
    int touchCount = sensor.getNumTouches();

    // Check if touch count changed
    if (touchCount != count) {
      lastTouchCountChange = currentTime;
      // Reset accumulated movement to prevent unwanted inputs when touch count changes
      accumulatedMovement = 0;

      #if TRILL_DEBUG
      Serial.print("Touch count changed from ");
      Serial.print(count);
      Serial.print(" to ");
      Serial.println(touchCount);
      #endif
    }

    count = touchCount;

    if (touchCount > 0) {
      // Store previous position and size for calculations
      lastRawPos = rawPos;

      // Read position of first touch
      rawPos = sensor.touchLocation(0);
      size = sensor.touchSize(0);
      adjustedSize = size / 200;  // Scale like original

      #if TRILL_DEBUG
      Serial.print("Positions - Last: ");
      Serial.print(lastRawPos);
      Serial.print(", Current: ");
      Serial.print(rawPos);
      Serial.print(", Delta: ");
      Serial.print(rawPos - lastRawPos);
      Serial.print(", Size: ");
      Serial.println(size);
      #endif

      #if TRILL_DEBUG
      Serial.print("Raw: ");
      Serial.print(rawPos);
      Serial.print(", Size: ");
      Serial.print(size);
        Serial.println();
      #endif

      // If this is a new touch, reset state
      if (!active) {
        active = true;
        startTime = currentTime;
        lastRawPos = rawPos;  // Initialize to prevent jumps
        lastSize = size;      // Initialize size tracking
        holdCounter = 0;
        // Reset accumulated movement when starting a new touch
        accumulatedMovement = 0;
      }

      // Increment hold counter (used to stabilize initial touch)
      holdCounter++;

      // Only process movement after initial stabilization and touch debounce period
      if (holdCounter > 2 && (currentTime - lastTouchCountChange > touchDebounceTime)) {
        int actionUnits = processMovement();


#if LOOP_TIMER_DEBUG
if (loopTimer && logThis) {
loopDuration = micros() - loopStartTime;
deltaTime = loopDuration - loopCheckpoint;
loopCheckpoint = loopDuration;
Serial.print("processMovement Δ: ");
Serial.print(deltaTime);
Serial.print("  |  ");
}
#endif

        // Handle based on touch count and size
        if (touchCount == 1 && adjustedSize <= 30) {
          // Single touch - use current mode
          switch (mode) {
            case MODE_ARROWS: handleMode1(actionUnits); break;
            case MODE_BRIGHTNESS: handleMode2(actionUnits); break;
            case MODE_SCROLL: handleMode3(actionUnits); break;;
            case MODE_MOUSE: handleMode4(actionUnits); break;
          }
        }

#if LOOP_TIMER_DEBUG
if (loopTimer && logThis) {
loopDuration = micros() - loopStartTime;
deltaTime = loopDuration - loopCheckpoint;
loopCheckpoint = loopDuration;
Serial.print("handModes Δ: ");
Serial.print(deltaTime);
Serial.print("  |  ");
}
#endif
        else if ((touchCount == 2 && adjustedSize > 8) ||
                  (touchCount == 1 && adjustedSize > 30 && adjustedSize <= 50)) {
          // Dual touch or medium-large single touch - volume control
          handleDualTouch();
        }
        else if (touchCount >= 3 || adjustedSize > 50) {
          // Triple touch or very large single touch - media control
          if (touchCount >= 4) {
            handleQuadTouch();
          } else {
            handleTripleTouch();
          }
        }
        #if TRILL_DEBUG
        else if (actionUnits != 0) {
          Serial.print("Ignoring movement (touch unstable): ");
          Serial.println(actionUnits);
        }
        #endif
      }
      else {
        // Reset accumulated movement during debounce period
        accumulatedMovement = 0;
      }

      // Disable momentum while touching
      momentumActive = false;

    }
    else if (active) {
      #if TRILL_MOMENTUM_DEBUG
        int currentMode = mode;
        float currentVelocity = velocity;
      #endif
      // Handle touch release
      handleTouchRelease();
      #if TRILL_MOMENTUM_DEBUG
        if (currentMode == MODE_SCROLL) {
          Serial.print("After touch release - Velocity: ");
          Serial.print(currentVelocity);
          Serial.print(" -> ");
          Serial.print(velocity);
          Serial.print(", Momentum: ");
          Serial.println(momentumActive ? "active" : "inactive");
        }
      #endif
      active = false;
    }
  }
#if LOOP_TIMER_DEBUG
if (loopTimer && logThis) {
loopDuration = micros() - loopStartTime;
deltaTime = loopDuration - loopCheckpoint;
loopCheckpoint = loopDuration;
Serial.print("polling Δ: ");
Serial.print(deltaTime);
Serial.print("  |  ");
}
#endif
}

bool trillbar::isLedOverride() {
  return ledsOverride;
}

int trillbar::getMode() {
  return mode;
}

void trillbar::setMode(int newMode) {
  mode = newMode;
}

#endif
