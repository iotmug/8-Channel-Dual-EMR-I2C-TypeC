#include <Wire.h>
#include "XL9535KxVxx.h"

// Define the I2C addresses for both relay boards
#define I2C_ADDRESS1 0x20  // I2C address of the first relay board
#define I2C_ADDRESS2 0x21  // I2C address of the second relay board

// Create instances of XL9535KxVxx for both relay boards
XL9535KxVxx relayBoard1(A4, A5, I2C_ADDRESS1); // First board
XL9535KxVxx relayBoard2(A4, A5, I2C_ADDRESS2); // Second board

void setup() {
    // Initialize serial communication for debugging (remove if not needed)
    Serial.begin(115200);

    // Initialize the first relay board
    if (relayBoard1.Init()) {
        Serial.println(F("Relay board 1 initialized successfully."));
    } else {
        Serial.println(F("Failed to initialize relay board 1."));
    }

    // Initialize the second relay board
    if (relayBoard2.Init()) {
        Serial.println(F("Relay board 2 initialized successfully."));
    } else {
        Serial.println(F("Failed to initialize relay board 2."));
    }

    // Enable all relays on both boards
    relayBoard1.EnableRelay(RelayALL, Enable);
    relayBoard2.EnableRelay(RelayALL, Enable);
}

void loop() {
    // Control relays on board 1
    for (int i = 0; i < 8; i++) {
        int relay = 1 << i;  // Calculate the relay bitmask (1, 2, 4, 8, etc.)
        relayBoard1.SwitchRelay(relay, Open);  // Turn ON the relay on board 1
        delay(1000);  // Wait for 1 second
        relayBoard1.SwitchRelay(relay, Close);  // Turn OFF the relay on board 1
        delay(1000);  // Wait for 1 second
    }

    // Control relays on board 2
    for (int i = 0; i < 8; i++) {
        int relay = 1 << i;  // Calculate the relay bitmask (1, 2, 4, 8, etc.)
        relayBoard2.SwitchRelay(relay, Open);  // Turn ON the relay on board 2
        delay(1000);  // Wait for 1 second
        relayBoard2.SwitchRelay(relay, Close);  // Turn OFF the relay on board 2
        delay(1000);  // Wait for 1 second
    }
}
