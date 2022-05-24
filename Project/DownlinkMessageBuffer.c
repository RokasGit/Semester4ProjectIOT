/*
 * DownlinkMessageBuffer.c
 *
 * Created: 5/18/2022 12:06:32 PM
 *  Author: rokas
 */ 
#include "DownlinkMessageBuffer.h"

//function to create the downlink message buffer
void downlinkMessageBuffer_create(){
	downlinkMessageBuffer = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
}