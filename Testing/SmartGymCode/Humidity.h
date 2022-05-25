/*
 * Humidity.h
 *
 * Created: 5/4/2022 10:41:00 PM
 *  Author: Farouk
 */

#include <stdio.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include <task.h>


#include "MeasureEventGroup.h"
#include "DataReadyEventGroup.h"

void Humidity_initializeDriver();
void Humidity_Task(void);
uint16_t Humidity_getHumidity();
static void clearHumidityBit();
void Humidity_createTask(UBaseType_t Taskpriority);

