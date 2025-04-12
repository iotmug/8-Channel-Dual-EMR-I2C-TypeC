import smbus2
import time

# I2C addresses of the two relay boards
I2C_ADDRESS1 = 0x20  # Replace with the address of the first board
I2C_ADDRESS2 = 0x21  # Replace with the address of the second board

# Define register addresses
ControlRegisterLow = 0x02
ControlRegisterHigh = 0x03
EnableRegisterLow = 0x06
EnableRegisterHigh = 0x07

# Define relay bitmasks for relays 1 to 8
relays = [0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080]

# Initialize I2C bus
bus = smbus2.SMBus(1)  # I2C bus 1 for Raspberry Pi

# Function to enable all relays on a board
def enable_all_relays(board_address):
    # Enable all relays by writing 0xFF to the enable registers
    bus.write_byte_data(board_address, EnableRegisterLow, 0x00)
    bus.write_byte_data(board_address, EnableRegisterHigh, 0x00)

# Function to switch a relay on/off
def switch_relay(board_address, relay, state):
    # Read current states
    low_state = bus.read_byte_data(board_address, ControlRegisterLow)
    high_state = bus.read_byte_data(board_address, ControlRegisterHigh)

    # Modify relay state
    if state == "on":
        low_state |= (relay & 0xFF)  # Turn ON relay in low byte
        high_state |= (relay >> 8)   # Turn ON relay in high byte
    else:
        low_state &= ~(relay & 0xFF)  # Turn OFF relay in low byte
        high_state &= ~(relay >> 8)   # Turn OFF relay in high byte

    # Write the updated states back to the registers
    bus.write_byte_data(board_address, ControlRegisterLow, low_state)
    bus.write_byte_data(board_address, ControlRegisterHigh, high_state)

# Enable all relays on both boards
enable_all_relays(I2C_ADDRESS1)
enable_all_relays(I2C_ADDRESS2)

# Main loop to control relays on both boards
try:
    while True:
        # Control relays on the first board
        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS1, relay, "on")
            print(f"Relay {i + 1} on board 1 turned ON.")
            time.sleep(1)
            switch_relay(I2C_ADDRESS1, relay, "off")
            print(f"Relay {i + 1} on board 1 turned OFF.")
            time.sleep(1)


        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS1, relay, "on")
            print(f"Relay {i + 1} on board 1 turned ON.")

        time.sleep(1)

        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS1, relay, "off")
            print(f"Relay {i + 1} on board 1 turned off.")

        # Control relays on the second board
        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS2, relay, "on")
            print(f"Relay {i + 1} on board 2 turned ON.")
            time.sleep(1)
            switch_relay(I2C_ADDRESS2, relay, "off")
            print(f"Relay {i + 1} on board 2 turned OFF.")
            time.sleep(1)
            
        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS2, relay, "on")
            print(f"Relay {i + 1} on board 1 turned ON.")

        time.sleep(1)

        for i in range(8):
            relay = relays[i]
            switch_relay(I2C_ADDRESS2, relay, "off")
            print(f"Relay {i + 1} on board 1 turned off.")




except KeyboardInterrupt:
    print("Exiting program...")
