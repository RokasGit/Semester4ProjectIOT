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
#include <semphr.h>




void Temperature_initializeDriver();
void Temperature_Task(void);
uint16_t Temperature_getTemperature();
void Temperature_createTask(UBaseType_t Taskpriority);
static void clearTemperatureBit();