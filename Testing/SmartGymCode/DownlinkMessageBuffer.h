/*
 * DownlinkMessageBuffer.h
 *
 * Created: 5/18/2022 12:04:22 PM
 *  Author: rokas
 */
#pragma once

#include <FreeRTOS.h>
#include <message_buffer.h>
typedef struct lora_driver_payload {
	uint8_t portNo; /**< Port_no the data is received on, or to transmit to [1..223]*/
	uint8_t len; /**< Length of the payload (no of bytes) - MAX 20 bytes is allowed in this implementation! */
	uint8_t bytes[20]; /**< Array to hold the payload to be send, or that has been received */
} lora_driver_payload_t;

MessageBufferHandle_t downlinkMessageBuffer;
void downlinkMessageBuffer_create();