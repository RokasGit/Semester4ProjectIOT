/*
* CO2Sensor.h
*
* Created: 5/24/2022 8:31:10 PM
*  Author: farouk
*/
#pragma once
#include <stdio.h>
#include <FreeRTOS.h>
#include <event_groups.h>

#include "MeasureEventGroup.h"
#include "DataReadyEventGroup.h"

// extend visibility of CO2 sensor status

void CO2Sensor_createTask(UBaseType_t TaskPriority);
void CO2Sensor_Task();
static void clearCO2ReadyBit();
static void mh_z19_callBack(uint16_t ppm);
uint16_t CO2Sensor_getCO2();
void CO2Sensor_initializeDriver();
void CO2Sensor_Task_Run();

