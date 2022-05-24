/*
 * DownlinkLoraWANHandler.c
 *
 * Created: 5/18/2022 3:21:33 PM
 *  Author: rokas
 */ 

#include "DownlinkLoraWANHandler.h"

// creating a task to handle the data received from loraWAN network.
void downlinkLoraWANHandler_createTask(UBaseType_t downlinkLorawantHandler_taskPrio){
	xTaskCreate(downlinkLoraWANHandler_Task,
	"downlinkLorawan_Task",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY+downlinkLorawantHandler_taskPrio,
		NULL);
}

// Task to handle loraWAN network.
void downlinkLoraWANHandler_Task(){
	for(;;){
		xMessageBufferReceive(downlinkMessageBuffer,&downlinkLoraWAN_Payload,sizeof(lora_driver_payload_t),portMAX_DELAY);
		printf("Message received-------: port No.: %d, with %d bytes",downlinkLoraWAN_Payload.portNo,downlinkLoraWAN_Payload.len);
		if(downlinkLoraWAN_Payload.len==1){
			uint16_t state = downlinkLoraWAN_Payload.bytes[0];
			configuration_setServoState(state);
			if(state!=-100){
				configuration_setAutomation(1);
			}else{
				configuration_setAutomation(0);
			}
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}