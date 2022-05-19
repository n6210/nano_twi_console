Simple FTDI UM201XB replacement.

Act as a TWI/I2C slave device at the address 0x22
and passes all data to the UART (one direction).

This implementation works with TWI speed 400kbit and
maximal length  of the single transfer 64 bytes.
It can be easly changed in twi.h.

Checked with a boards:
- Arduino Nano ATMega168 (1Mbit UART)
- LGT8F328P (460kbit UART)

Connections:
- SCL (A5)
- SDA (A4)
- GND

![ArduinoNanoPinout](ArduinoNanoPinout.jpeg)

Project uses twi.c - TWI/I2C library for Wiring & Arduino
Copyright (c) 2006 Nicholas Zambetti
