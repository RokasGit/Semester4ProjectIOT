/*
* Application.c
*
* Created: 5/7/2022 3:50:22 PM
*  Author: rokas
*/
#include "Application.h"

// Creating application task
void application_createTask(UBaseType_t TaskPriority) {
	xTaskCreate(
		application_Task // application task method
		, "ApplicationTask" // application name
		, configMINIMAL_STACK_SIZE // stack size for task
		, NULL
		,  TaskPriority
		, NULL);
}
// Application Task
void application_Task(void* pvParameters) {
	for (;;) {
		application_TaskRun(pvParameters);
	}

}
void application_TaskRun(void* pvParameters) {
	EventBits_t dataBits = xEventGroupWaitBits(dataReadyEventGroup
		, BIT_READY_TO_SEND_CO2 | BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE // wait for these bits
		, pdTRUE // clear all bits after finishing the wait
		, pdTRUE // wait for all bits
		, portMAX_DELAY); // wait maximum amount of time
	// checking and opening or closing the window here
	if ((dataBits & (BIT_READY_TO_SEND_CO2 | BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE)) == (BIT_READY_TO_SEND_CO2 | BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE)) {
		application_setPackageHandler();
		// open or close servo on condition
		

	}
	vTaskDelay(pdMS_TO_TICKS(30000));
	xEventGroupSetBits(measureEventGroup, BIT_READY_TO_MEASURE_CO2);
}
// configuring package settings.
void application_setPackageHandler() {

}