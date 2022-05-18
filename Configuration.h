/*
 * Configuration.h
 *
 * Created: 5/18/2022 12:09:47 PM
 *  Author: rokas
 */ 
#pragma once

#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t configurationSemaphore;
uint16_t rcServoState;

void configuration_create();
void configuration_setServoState(uint16_t state);
uint16_t configuration_getServoState();
