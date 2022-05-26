#pragma once
/*
 * Temperature.h
 *
 * Created: 5/24/2022 10:07:51 PM
 *  Author: farouk
 */



#include <stdio.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

#include <event_groups.h>

#define TemperatureTaskStackSize (configMINIMAL_STACK_SIZE)
#define BIT_READY_TO_SEND_CO2 (1 << 0)
#define BIT_READY_TO_SEND_TEMPERATURE (1 << 1)
#define BIT_READY_TO_SEND_HUMIDITY (1 << 2)
#define BIT_READY_TO_MEASURE_CO2 (1 << 0)
EventGroupHandle_t measureEventGroupMockTemp;
EventGroupHandle_t dataReadyEventGroupMockTemp;


void Temperature_initializeDriver();
void Temperature_Task(void);
uint16_t Temperature_getTemperature();
void Temperature_createTask(UBaseType_t Taskpriority);
static void clearTemperatureBit();
void Temperature_Task_Run(void* parameter);