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

#include "RCServo.h"

SemaphoreHandle_t configurationSemaphore;
uint16_t rcServoState;
int isMoving;
uint16_t maxCO2Level;
uint16_t maxHumidityLevel;
uint16_t minHumidityLevel;
int automationOff;

void configuration_create();
void configuration_setServoState(uint16_t state);
uint16_t configuration_getServoState();
int configuration_getIsMoving();
void configuration_setIsMoving(int moving);
uint16_t configuration_getMaxCO2Level();
uint16_t configuration_getMaxHumidityLevel();
uint16_t configuration_getMinHumidityLevel();
void configuration_setAutomation(int automation);
int configuration_getAutomation();
