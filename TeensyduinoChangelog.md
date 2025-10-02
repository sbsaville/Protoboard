Changes since Teensyduino 1.58:

C++17 used for Teensy 3.x and 4.x
Enable LTO options in Arduino Tools > Optimization menu
Fix startup for LTO optimization
Remove serialEvent_default, refactor yield_active_check_flags
Add inplace_function for callbacks
IntervalTimer use inplace_function
IntervalTimer demo callback backwards compatibility
Delete unused flags from String
Use C++17 to simplify IntervalTimer (Luni)
Fault handler use main vs process stack pointer (Christian Kahlo)
USBHost_t36 update DriveInfo example (Warren Watson)
FastLED fix C++17 compiler warnings
Tlc5940 update documentation, SCLK overshoot sensitivity
Fix const init on Wire, SPI, HardwareSerial
Update FlexIO_t4 - ??? (KurtE)
define SPI_HAS_NOTUSINGINTERRUPT
define WIRE_INTERFACES_COUNT and SPI_INTERFACES_COUNT
make availableForWrite virtual (Shawn Silverman)
remove old abs() and round() (mjs513)
CrashReport breadcrumbs improved
update example Makefile
fix Lockable Teensy auto-reboot with optimize smallest size with LTO
fix USB Touchscreen on Teensy 4.x with Windows
extmem_calloc() clears memory (Shawn Silverman)
add Print::vprintf() (Randy Palamar)
Audio improve AudioEffectWaveshaper initialization
Update ILI9488_t3 - ???
Update Keypad - Allow time for signals to settle
Update LittleFS - Add support for GigaDevice NOR Flash
Update RA8875 - ???
Update ST7735_t3 - ???
USBHost_t36 improve timers, fixes simultaneous transmit to 3+ devices
USBHost_t36 fix MIDI fast sustained receive
USBHost_t36 HID parser changes??? (KurtE)
USBHost_t36 RawHID improvements (KurtE)
USBHost_t36 Serial example update (KurtE)
teensy_secure add encrypthex_unlocksnvs option
Teensy monitor on Windows avoid 0 baud setting - not yet in IDE2 packages
Publish Arduino IDE 2.x.x packages using zstd compression
SD/SdFat Workaround for old version 1 cards with SDIO on Teensy 4.1
SD/SdFat Handle cards which falsely claim high speed support (tompilot)
FlexIO_t4 add setClock(), setClockUsingAudioPLL(), setClockUsingVideoPLL()
FlexIO_t4 fix minor issues and update examples
HardwareSerial base class
SoftwareSerial fix for MicroMod (KurtE)
SPI fix constinit for Teensy 3.x
Don't allow writing to ITCM after startup on Teensy 4.x
Update Stream parseInt and parseFloat for LookaheadMode
USB MIDI add realtime send functions (same API as MIDI library)
Add alternate names for FlexIO register bit fields
Fix Serial2 on MicroMod (KurtE)
Fix vprintf on Teensy 2.0
Fix pulldown on half duplex serial (KurtE)
Use namespace "teensy" for inplace_function
IPAddress compare operators are const (ssilverman)
ILI9431 fix DemoSauce example
ILI9488_t3 for clearChangedRange() on Teensy 3.2 (mjs513)
LittleFS fix wrote info in example (karelv)
USBHost_t36 fix race condition in MIDI read()
USBHost_t36 fix sustained fast MIDI receive
USBHost_t36 improve USBDriverTimer to fix fast transmit to 3+ USB devices
USBHost_t36 fix USBHIDDumper example (KurtE)
USBHost_t36 fix typos and spelling mistakes in comments (KurtE)
USBHost_t36 update virtual function defs (pr8x)
Show warning if IDE 2.x.x package used on IDE 1.8.x
analogRead() disable pin input keeper on Teensy 4.x
attachInterrupt always turn on pin hystersis on Teensy 4.x
Add DSB before return from interrupts from attachInterrupt
Wire: Scanner example scans all ports
Wire: Use WIRE_INTERFACES_COUNT for instances on Teensy 3.x
Add SEMC bitfield defines
Add MPU config for SEMC needed by SDRAM_t4 library
SdFat: Fix compiler warning with LTO linking on Teensy 4.x
SdFat: Removed a couple extraneous printfs (mjs513)
Fix makeWord() return type
Fix compiler warning with LTO on Teensy 3.x
LittleFS: Fix compiler warning with LTO linker
Close Teensy Loader on Arduino IDE 2.2.2 Boards Manager uninstall
Fix for wrong Teensy auto-reboot during upload
USB Serial emulation availableForWrite()
Add LCDIF defines (A-Dunstan)
Remove unused IntervalTimer code (Luni)
Audio fix CS4274 (WeTac)
Snooze fix on Teensy 4.x (BriComp)
Fix unable to auto-reboot on Linux
Fix for launching Teensy Loader on MacOS Sonoma from Arduino 1.8.19