/*
 * Temperature.h
 *
 * Created: 5/3/2022 10:07:51 PM
 *  Author: Nick
 */ 

#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <hih8120.h>

#include "MeasureEventGroup.h"

void Temperature_initializeDriver();
void createTemperatureClass(void* parameter); 
void Create_TemperatureTask(UBaseType_t Taskpriority);
