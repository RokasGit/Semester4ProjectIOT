/*
 * DownlinkLoraWANHandler.h
 *
 * Created: 5/18/2022 3:18:19 PM
 *  Author: rokas
 */ 
#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <lora_driver.h>

#include "DownlinkMessageBuffer.h"
#include "Configuration.h"

lora_driver_payload_t downlinkLoraWAN_Payload;

void downlinkLoraWANHandler_createTask(UBaseType_t downlinkLorawantHandler_taskPrio);
void downlinkLoraWANHandler_Task();