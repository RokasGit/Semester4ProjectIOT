/*
 * DataReadyEventGroup.h
 *
 * Created: 5/7/2022 3:38:26 PM
 *  Author: rokas
 */ 

#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <event_groups.h>

/* Measure Event Group */
#define BIT_READY_TO_SEND_CO2 (1 << 0)
#define BIT_READY_TO_SEND_TEMPERATURE (1 << 1)
#define BIT_READY_TO_SEND_HUMIDITY (1 << 2)
// extend the event group visibility
EventGroupHandle_t dataReadyEventGroup;

void dataReadyEventGroup_initialize();
