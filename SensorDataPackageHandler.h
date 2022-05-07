/*
* SensorDataPackageHandler.h
*
* Created: 5/3/2022 7:26:17 PM
*  Author: rokas
*/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>

void sensorDataPackageHandler_setCo2Ppm(uint16_t ppm);
void sensorDataPackageHandler_setTemperature(uint16_t celsius);
void sensorDataPackageHandler_setHumidity(uint16_t hum);
void sensorDataPackageHandler_setPackageLength(uint8_t packageLength);
lora_driver_payload_t sensorDataPackageHandler_getLoraPayload(uint8_t port_No);

