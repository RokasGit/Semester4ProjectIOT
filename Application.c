/*
* Application.c
*
* Created: 5/7/2022 3:50:22 PM
*  Author: rokas
*/
#include "Application.h"

// Creating application task
void application_createTask(UBaseType_t TaskPriority){
	xTaskCreate(
	application_Task // application task method
	, "ApplicationTask" // application name
	, configMINIMAL_STACK_SIZE // stack size for task
	, NULL
	, tskIDLE_PRIORITY+ TaskPriority
	, NULL);
}
// Application Task
void application_Task(void *pvParameters){
	for(;;){
		EventBits_t dataBits = xEventGroupWaitBits(dataReadyEventGroup
		, BIT_READY_TO_SEND_CO2| BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE // wait for these bits
		, pdTRUE // clear all bits after finishing the wait
		, pdTRUE // wait for all bits
		, portMAX_DELAY); // wait maximum amount of time
		if((dataBits & (BIT_READY_TO_SEND_CO2 | BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE))==(BIT_READY_TO_SEND_CO2 | BIT_READY_TO_SEND_HUMIDITY | BIT_READY_TO_SEND_TEMPERATURE)){
			printf("Ready to send measurements");
			printf("CO2: %d, Temperature: %d, Humidity: %d",CO2Sensor_getCO2(),Temperature_getTemperature(),Humidity_getHumidity());
			application_setPackageHandler();
			if(configuration_getAutomation()==0){
				if(CO2Sensor_getCO2 > configuration_getMaxCO2Level() || Humidity_getHumidity()>configuration_getMaxHumidityLevel()
				|| Humidity_getHumidity()<configuration_getMinHumidityLevel()){
					printf("Setting rc servo to open");
					configuration_setServoState(100);
					}else{
						printf("Setting rc servo to closed");
					configuration_setServoState(-100);
				}
			}
			vTaskDelay(pdMS_TO_TICKS(30000));
			xEventGroupSetBits(measureEventGroup, BIT_READY_TO_MEASURE_CO2);
			
		}
	}
	
}
// configuring package settings.
void application_setPackageHandler(){
	sensorDataPackageHandler_setPackageLength(6);
	sensorDataPackageHandler_setCo2Ppm(CO2Sensor_getCO2());
	sensorDataPackageHandler_setHumidity(Humidity_getHumidity());
	sensorDataPackageHandler_setTemperature(Temperature_getTemperature());
}