/*
 * Humidity.h
 *
 * Created: 5/4/2022 10:41:00 PM
 *  Author: Nick
 */ 

#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <hih8120.h>

#include "MeasureEventGroup.h"

void humidity_initializeDriver();
void humidity_HumidityTask(void* parameter);
void humidity_createTask(UBaseType_t Taskpriority);
