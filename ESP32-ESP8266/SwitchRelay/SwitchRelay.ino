#include "XL9535KxVxx.h"

// Define I2C addresses for your relay boards
#define I2C_ADDRESS_DEVICE_1 0x20 // I2C address of the first device
#define I2C_ADDRESS_DEVICE_2 0x21 // I2C address of the second device

// Initialize XL9535KxVxx objects for both devices
XL9535KxVxx relayBoard1(21, 22, I2C_ADDRESS_DEVICE_1); // SCL, SDA, I2C address for device 1
XL9535KxVxx relayBoard2(21, 22, I2C_ADDRESS_DEVICE_2); // SCL, SDA, I2C address for device 2

void setup() {
    Serial.begin(9600);
  
    // Initialize both relay boards
    if (!relayBoard1.Init()) {
        Serial.println("Failed to initialize relay board 1");
    }
    if (!relayBoard2.Init()) {
        Serial.println("Failed to initialize relay board 2");
    }


    // Başlangıçta tüm röleleri kapat
    // Board 1 için tüm röleleri kapat
    for (int relay = RelayA1; relay <= RelayA8; relay <<= 1) {
        relayBoard1.EnableRelay(relay, Enable);      // Röleyi etkinleştir
        relayBoard1.SwitchRelay(relay, Close);       // Röleyi kapat (Close)
        Serial.print("Board 1, Relay ");
        Serial.print(relay);
        Serial.println(" Başlangıçta kapatıldı.");
    }
  
    // Board 2 için tüm röleleri kapat
    for (int relay = RelayA1; relay <= RelayA8; relay <<= 1) {
        relayBoard2.EnableRelay(relay, Enable);      // Röleyi etkinleştir
        relayBoard2.SwitchRelay(relay, Close);       // Röleyi kapat (Close)
        Serial.print("Board 2, Relay ");
        Serial.print(relay);
        Serial.println(" Başlangıçta kapatıldı.");
    }
}

void loop() {
    // Board 1: Sırayla 3 röleyi açıp kapatma
    for (int relay = RelayA1; relay <= RelayA8; relay <<= 1) {
        relayBoard1.EnableRelay(relay, Enable);      // Röleyi etkinleştir
        relayBoard1.SwitchRelay(relay, Open);        // Röleyi aç (Open)
        Serial.print("Board 1, Relay ");
        Serial.print(relay);
        Serial.println(" Open");
        delay(500);                                 // 2 saniye bekle

        relayBoard1.SwitchRelay(relay, Close);       // Röleyi kapat (Close)
        Serial.print("Board 1, Relay ");
        Serial.print(relay);
        Serial.println(" Close");
        delay(500);                                 // 2 saniye bekle
    }

    // Board 2: Sırayla 3 röleyi açıp kapatma
    for (int relay = RelayA1; relay <= RelayA8; relay <<= 1) {
        relayBoard2.EnableRelay(relay, Enable);      // Röleyi etkinleştir
        relayBoard2.SwitchRelay(relay, Open);        // Röleyi aç (Open)
        Serial.print("Board 2, Relay ");
        Serial.print(relay);
        Serial.println(" Open");
        delay(500);                                 // 2 saniye bekle

        relayBoard2.SwitchRelay(relay, Close);       // Röleyi kapat (Close)
        Serial.print("Board 2, Relay ");
        Serial.print(relay);
        Serial.println(" Close");
        delay(500);                                 // 2 saniye bekle
    }

    // Döngü başa dönsün
}
