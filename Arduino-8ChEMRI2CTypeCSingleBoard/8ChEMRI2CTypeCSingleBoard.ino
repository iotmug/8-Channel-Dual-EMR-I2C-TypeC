#include <Wire.h>

#define RELAY_BOARD_ADDR 0x20  // Change this if your board uses a different address

// XL9535K Register Addresses
#define CONFIG_REG 0x06     // Configuration register (1 = input, 0 = output)
#define OUTPUT_REG 0x02     // Output port register

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Set all 8 pins on Port 0 to OUTPUT
  Wire.beginTransmission(RELAY_BOARD_ADDR);
  Wire.write(CONFIG_REG);
  Wire.write(0x00);  // Port 0 = all outputs
  Wire.write(0xFF);  // Port 1 = inputs or unused
  Wire.endTransmission();

  // Start with all relays OFF (HIGH = off, assuming active LOW relays)
  setRelayState(0xFF);

  Serial.println("Relay board initialized");
}

void loop() {
  // Turn on each relay one by one
  for (int i = 0; i < 8; i++) {
    byte relayState = ~(1 << i);  // Only one LOW at a time (active LOW)
    setRelayState(relayState);
    delay(500);
  }

  // Turn all relays OFF
  setRelayState(0xFF);
  delay(1000);
}

// Function to set relay states on Port 0
void setRelayState(uint8_t state) {
  Wire.beginTransmission(RELAY_BOARD_ADDR);
  Wire.write(OUTPUT_REG);
  Wire.write(state);  // Port 0 (relay outputs)
  Wire.write(0xFF);   // Port 1 (not used)
  Wire.endTransmission();
}
