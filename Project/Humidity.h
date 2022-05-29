/*
 * Humidity.h
 *
 * Created: 5/4/2022 10:41:00 PM
 *  Author: Farouk
 */ 

#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <hih8120.h>

#include "MeasureEventGroup.h"
#include "DataReadyEventGroup.h"

void Humidity_Task(void* parameter);
uint16_t Humidity_getHumidity();
static void clearHumidityBit();
void Humidity_createTask(UBaseType_t Taskpriority);
