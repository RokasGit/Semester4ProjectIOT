/*
 * RCServo.c
 *
 * Created: 5/18/2022 4:15:24 PM
 *  Author: rokas
 */ 
#include "RCServo.h"

void rcServo_CreateSemaphore(){
	rcServoSemaphore = xSemaphoreCreateBinary();
}
void rcServo_CreateTask(UBaseType_t rcServo_task_priority){
	rc_servo_initialise();
	xTaskCreate(rcServo_Task,
	"RCServo_Task",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY+rcServo_task_priority,
	NULL);
}
void rcServo_Task(){
	for(;;){
		if(xSemaphoreTake(rcServoSemaphore,portMAX_DELAY)==pdTRUE){
			uint16_t state = configuration_getServoState();
			printf("Setting rc servo state: %d \n",state);
			rc_servo_setPosition(1,state);
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}