#include <Wire.h>

// I2C addresses of the two XL9535K boards
#define BOARD1_ADDR 0x20  // Change based on your board's A0/A1/A2 settings
#define BOARD2_ADDR 0x21  // Change accordingly

// XL9535K Register Addresses
#define CONFIG_REG 0x06     // Configuration register (1 = input, 0 = output)
#define OUTPUT_REG 0x02     // Output port register

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Set all pins to OUTPUT (0) on both boards
  configAsOutput(BOARD1_ADDR);
  configAsOutput(BOARD2_ADDR);

  // Turn off all relays initially (HIGH = off if active low)
  writeRelayState(BOARD1_ADDR, 0xFF);  // All off
  writeRelayState(BOARD2_ADDR, 0xFF);  // All off

  delay(1000);
}

void loop() {
  // Turn on relays one by one on both boards
  for (int i = 0; i < 8; i++) {
    byte state1 = ~(1 << i);  // Active LOW: set only one LOW at a time
    writeRelayState(BOARD1_ADDR, state1);
    writeRelayState(BOARD2_ADDR, state1);
    delay(500);
  }

  // Turn off all relays
  writeRelayState(BOARD1_ADDR, 0xFF);
  writeRelayState(BOARD2_ADDR, 0xFF);
  delay(1000);
}

// Helper function: Set all pins to output
void configAsOutput(uint8_t addr) {
  Wire.beginTransmission(addr);
  Wire.write(CONFIG_REG);
  Wire.write(0x00);  // Port 0 - all outputs
  Wire.write(0x00);  // Port 1 - all outputs
  Wire.endTransmission();
}

// Helper function: Write relay state (8 bits to port 0, assume port 1 unused)
void writeRelayState(uint8_t addr, uint8_t state) {
  Wire.beginTransmission(addr);
  Wire.write(OUTPUT_REG);
  Wire.write(state);  // Port 0 (P0_0 to P0_7)
  Wire.write(0xFF);   // Port 1 (not used)
  Wire.endTransmission();
}
