#pragma once
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

#define BIT_READY_TO_SEND_CO2 (1 << 0)
#define BIT_READY_TO_SEND_TEMPERATURE (1 << 1)
#define BIT_READY_TO_SEND_HUMIDITY (1 << 2)
#define BIT_READY_TO_MEASURE_CO2 (1 << 0)
EventGroupHandle_t measureEventGroup;
EventGroupHandle_t dataReadyEventGroup;
void application_createTask(UBaseType_t TaskPriority);
void application_Task(void* pvParameters);
void application_TaskRun(void* pvParameters);
void application_setPackageHandler();