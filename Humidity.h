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

void Humidity_initializeDriver();
void Humidity_Task(void* parameter);
static void clearHumidityBit()
void Humidity_createTask(UBaseType_t Taskpriority);
