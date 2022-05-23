#pragma once

#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"

SemaphoreHandle_t rcServoSemaphore;
SemaphoreHandle_t configurationSemaphore;
uint16_t rcServoState;
int isMoving;
uint16_t maxCO2Level;
uint16_t maxHumidityLevel;
uint16_t minHumidityLevel;
int automationOff;
int ledOn;

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
void configuration_SetLightOnAndOf();
uint16_t configuration_getServoStateRun();
void configuration_setAutomationRun(int automation);
