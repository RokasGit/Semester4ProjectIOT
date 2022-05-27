/*
 * RCServo.c
 *
 * Created: 5/18/2022 4:15:24 PM
 *  Author: rokas
 */
#include "RCServo.h"

 //function to create the rcServo semaphore
void rcServo_CreateSemaphore() {
	rcServoSemaphore = xSemaphoreCreateBinary();
}

//function to create the rcServo task 
void rcServo_CreateTask(UBaseType_t rcServo_task_priority) {
	xTaskCreate(rcServo_Task,
		"RCServo_Task",
		configMINIMAL_STACK_SIZE,
		NULL,
		rcServo_task_priority,
		NULL);
}

//function to initialize the rcServo task 
void rcServo_Task() {
	for (;;) {
		rcServo_TaskRun();
	}
}

void rcServo_TaskRun() {
	if (xSemaphoreTake(rcServoSemaphore, portMAX_DELAY) == pdTRUE) {
		//open servo
	}
	vTaskDelay(pdMS_TO_TICKS(200));
}