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

void initializeDriver();
void createTemperatureClass(UBaseType_t Taskpriority);
void TemperatureTask(void* parameter);
