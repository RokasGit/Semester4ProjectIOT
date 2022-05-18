/*
 * Application.h
 *
 * Created: 5/7/2022 3:33:27 PM
 *  Author: rokas
 */ 
#pragma once
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

// config to control window automatically
#include "Configuration.h"
// package to send to lorawan gateway
#include "SensorDataPackageHandler.h"
// event groups to start measuring and wait for results
#include "MeasureEventGroup.h"
#include "DataReadyEventGroup.h"

// sensors
#include "CO2Sensor.h"
#include "Temperature.h"
#include "Humidity.h"

void application_createTask(UBaseType_t TaskPriority);
void application_Task(void *pvParameters);
void application_setPackageHandler();