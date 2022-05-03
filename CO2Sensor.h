/*
* CO2Sensor.h
*
* Created: 5/3/2022 8:31:10 PM
*  Author: rokas
*/
#pragma once
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <mh_z19.h>
#include <event_groups.h>

#include "MeasureEventGroup.h"

// extend visibility of CO2 sensor status
extern mh_z19_returnCode_t CO2Sensor_returnCode;

void CO2Sensor_createTask(UBaseType_t TaskPriority);
void CO2Sensor_Task();
static void mh_z19_callBack(uint16_t ppm);
uint16_t CO2Sensor_getCO2();
void CO2Sensor_initializeDriver();
