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
#include <hih8120.h>

#include "MeasureEventGroup.h"
#include "DataReadyEventGroup.h"

void Temperature_initializeDriver();
void Temperature_Task(void* parameter); 
uint16_t Temperature_getTemperature();
void Temperature_createTask(UBaseType_t Taskpriority);
static void clearTemperatureBit();
