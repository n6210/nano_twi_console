/*
  Copyright (c) 2022 fotonix@pm.me  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 */

extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "twi.h"
}

// TWI/I2C addres taken over from FTDI UM201XB
const uint8_t TWI_address = 0x22;

#ifdef ARDUINO_AVR_LARDU_328E
// LGT8F328 460800 boud @ 32MHz,
const uint32_t UART_speed = 460800;
#elif defined(ARDUINO_AVR_NANO)
// ATMega168 UART 1000000 boud
const uint32_t UART_speed = 1000000;
#else
// For unknow CPU just 115200 boud
const uint32_t UART_speed = 115200;
#endif

bool dataPresent = false;

/*
 *  Client receive data callback
 */
void onReceiveService(uint8_t* inBytes, int numBytes)
{
  //Get bytes from buffer and send to UART
  Serial.write(inBytes, numBytes);

  // Trigger LED
  dataPresent = true;
}

/*
 *  Setup HW (LED, UART, TWI/I2C)
 */
void setup()
{
  // Prepare LED GPIO
  pinMode(LED_BUILTIN, OUTPUT);

  // Prepare UART
  Serial.begin(UART_speed);
  Serial.println("NanoTWI console @ 0x22");

  // Initialize, set register callback, set slave address
  twi_init();
  twi_attachSlaveRxEvent(onReceiveService);
  twi_setAddress(TWI_address);
}

/*
 *  Main loop
 */
void loop()
{
  if (dataPresent) {
    // Blink LED when I2C is receiving data
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);

    dataPresent = 0;
  }
}
