/*
 * DownlinkLoraWANHandler.c
 *
 * Created: 5/18/2022 3:21:33 PM
 *  Author: rokas
 */

#include "DownlinkLoraWANHandler.h"

 // creating a task to handle the data received from loraWAN network.
void downlinkLoraWANHandler_createTask(UBaseType_t downlinkLorawantHandler_taskPrio) {
	xTaskCreate(downlinkLoraWANHandler_Task,
		"downlinkLorawan_Task",
		configMINIMAL_STACK_SIZE,
		NULL,
		downlinkLorawantHandler_taskPrio,
		NULL);
}
// Task to handle loraWAN network.
void downlinkLoraWANHandler_Task() {
	for (;;) {
		downlinkLoraWANHandler_TaskRun();
	}
}
void downlinkLoraWANHandler_TaskRun() {
	xMessageBufferReceive(downlinkMessageBufferMock, &downlinkLoraWAN_Payload, sizeof(lora_driver_payload_t), portMAX_DELAY);
	if (downlinkLoraWAN_Payload.len == 1) {
		uint16_t state = downlinkLoraWAN_Payload.bytes[0];
		// open window
		if (state != -100) {
			// turn off automation
		}
		else {
			// turn on automation
		}
	}
	vTaskDelay(pdMS_TO_TICKS(200));
}