/*
* MeasureEventGroup.h
*
* Created: 5/3/2022 8:15:53 PM
*  Author: rokas
*/
#pragma once
#include <FreeRTOS.h>
#include <event_groups.h>

/* Measure Event Group */
#define BIT_READY_TO_MEASURE_CO2 (1 << 0)
#define BIT_READY_TO_MEASURE_TEMPERATURE (1 << 1)
#define BIT_READY_TO_MEASURE_HUMIDITY (1 << 2)
// extend the event group visibility
EventGroupHandle_t measureEventGroup;

void measureEventGroup_initialize();
