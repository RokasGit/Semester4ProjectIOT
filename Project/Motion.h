/*
 * Motion.h
 *
 * Created: 5/18/2022 12:26:28 PM
 *  Author: Nick
 */ 


#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <hcSr501.h>

#include "Configuration.h"

void Motion_initializeDriver();
void Motion_Task(void* parameter);
uint16_t Motion_NrOfMovements();
void Motion_createTask(UBaseType_t Taskpriority);
