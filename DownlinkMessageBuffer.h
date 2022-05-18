/*
 * DownlinkMessageBuffer.h
 *
 * Created: 5/18/2022 12:04:22 PM
 *  Author: rokas
 */ 
#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <message_buffer.h>
#include <lora_driver.h>

MessageBufferHandle_t downlinkMessageBuffer;
void downlinkMessageBuffer_create();