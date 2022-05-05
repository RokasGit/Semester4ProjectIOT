/*
* CO2Sensor.c
*
* Created: 5/3/2022 8:36:56 PM
*  Author: rokas
*/
#include "CO2Sensor.h"
static uint16_t lastCO2ppm;

//declaration of functions
static void mh_z19_callBack(uint16_t ppm);
void CO2Sensor_initializeDriver();
uint16_t CO2Sensor_getCO2();
void CO2Sensor_Task();
static void clearCO2ReadyBit();
void CO2Sensor_createTask(UBaseType_t TaskPriority);

static void mh_z19_callBack(uint16_t ppm){
	lastCO2ppm = ppm;
}
void CO2Sensor_initializeDriver(){
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(mh_z19_callBack);
}
uint16_t CO2Sensor_getCO2(){
	return lastCO2ppm;
}
void CO2Sensor_Task(){
	for(;;){
		EventBits_t measureBits;
		measureBits = xEventGroupWaitBits(
		measureEventGroup, // measure event group
		BIT_READY_TO_MEASURE_CO2, // wait for CO2 ready to measure
		pdFALSE, // no need to clear, clearing manually in callback
		pdTRUE, // wait for all bits(ONLY CO2)
		portMAX_DELAY // wait infinity till timeout
		);
		if((measureBits & BIT_READY_TO_MEASURE_CO2)==BIT_READY_TO_MEASURE_CO2){
			CO2Sensor_returnCode = mh_z19_takeMeassuring();
			if(CO2Sensor_returnCode!= MHZ19_OK){
				printf("CO2 MEASSURING FAILED!!");
			}
			if(CO2Sensor_returnCode==MHZ19_OK){
				clearCO2ReadyBit();
			}
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}
static void clearCO2ReadyBit(){
	EventBits_t clearedCO2Bit;
	clearedCO2Bit = xEventGroupClearBits(
	measureEventGroup, // clearing in measure event group the co2 bit after taking the measure;
	BIT_READY_TO_MEASURE_CO2); // clearing the co2 bit
	if((clearedCO2Bit & BIT_READY_TO_MEASURE_CO2) == BIT_READY_TO_MEASURE_CO2){
		// BIT CO2 was set before clear was called, now will be clear
		}else if((clearedCO2Bit & BIT_READY_TO_MEASURE_CO2) !=0){
		/* CO2 bit was set before clear was called,
		It will be clear now.*/
		}else{
		// Bits were not set
	}
}
void CO2Sensor_createTask(UBaseType_t TaskPriority){
	// initializing CO2 driver
	CO2Sensor_initializeDriver();
	// Creating CO2 TASK
	xTaskCreate(
	CO2Sensor_Task,
	"CO2Sensor_Task",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY + TaskPriority,
	NULL);
}
