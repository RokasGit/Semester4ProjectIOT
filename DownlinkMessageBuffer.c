/*
 * DownlinkMessageBuffer.c
 *
 * Created: 5/18/2022 12:06:32 PM
 *  Author: rokas
 */ 
#include "DownlinkMessageBuffer.h"

void downlinkMessageBuffer_create(){
	downlinkMessageBuffer = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
}