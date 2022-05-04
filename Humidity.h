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

#include "MeasureEventGroup.h"

void Humidity_initializeDriver();
void createHumidityClass(void* parameter);
void Create_HumidityTask(UBaseType_t Taskpriority);
