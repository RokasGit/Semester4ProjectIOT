/*
 * DownlinkLoraWANHandler.h
 *
 * Created: 5/18/2022 3:18:19 PM
 *  Author: rokas
 */
#pragma once

#include <stdint.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <message_buffer.h>

typedef struct lora_driver_payload {
	uint8_t portNo; /**< Port_no the data is received on, or to transmit to [1..223]*/
	uint8_t len; /**< Length of the payload (no of bytes) - MAX 20 bytes is allowed in this implementation! */
	uint8_t bytes[20]; /**< Array to hold the payload to be send, or that has been received */
} lora_driver_payload_t;

lora_driver_payload_t downlinkLoraWAN_Payload;

MessageBufferHandle_t downlinkMessageBuffer;
void downlinkLoraWANHandler_createTask(UBaseType_t downlinkLorawantHandler_taskPrio);
void downlinkLoraWANHandler_Task();
void downlinkLoraWANHandler_TaskRun();