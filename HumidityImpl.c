/*
 * HumidityImpl.c
 *
 * Created: 5/4/2022 10:43:34 PM
 *  Author: Nick
 */ 

#include "Temperature.h"

#define HumidityTaskStackSize (configMINIMAL_STACK_SIZE)

static uint16_t Hum;

void Humidity_initializeDriver(){
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();

	if ( HIH8120_OK == returnCode )
	{
		printf("Humidity Driver initialized");
	}
	
	else {
		printf("Error: %s", returnCode);
	}
}

void createHumidityClass(void* parameter){
	
	
	for(;;){
		EventBits_t measureBits;
		measureBits = xEventGroupWaitBits(
		measureEventGroup, // measure event group
		BIT_READY_TO_MEASURE_HUMIDITY, // wait for Humidity ready to measure
		pdFALSE, // no need to clear, clearing manually in callback
		pdTRUE, // wait for all bits(ONLY CO2)
		portMAX_DELAY // wait infinity till timeout
		);
		
		if((measureBits & BIT_READY_TO_MEASURE_HUMIDITY)==BIT_READY_TO_MEASURE_HUMIDITY){
			
			hih8120_driverReturnCode_t = hih8120_wakeup(void);
			
			vTaskDelay(pdMS_TO_TICKS(55));
			
			if(hih8120_driverReturnCode_t!= HIH8120_OK){
				printf("Humidity MEASSURING FAILED!!")
			}
			
			if(hih8120_driverReturnCode_t==HIH8120_OK){
				Hum = hih8120_getHumidityPercent_x10();
				clearHumidityBit();
			}
			
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
}

static void clearHumidityBit(){
	EventBits_t clearedHumBit;
	
	clearedHumBit = xEventGroupClearBits(
	measureEventGroup, // clearing in measure event group the humidity bit after taking the measure;
	BIT_READY_TO_MEASURE_HUMIDITY); // clearing the humidity bit
	if((clearedHumBit & BIT_READY_TO_MEASURE_HUMIDITY) == BIT_READY_TO_MEASURE_HUMIDITY){
		// BIT humidity was set before clear was called, now will be clear
		}else if((clearedHumBit & BIT_READY_TO_MEASURE_HUMIDITY) !=0){
		/* humidity bit was set before clear was called,
		It will be clear now.*/
		}else{
		// Bits were not set
	}
}

void Create_HumidityTask(UBaseType_t Taskpriority){
	Humidity_initializeDriver();
	
	xTaskCreate(
	Create_HumidityTask,
	"Humidity Task",
	HumidityTaskStackSize,
	NULL,
	tskIDLE_PRIORITY + Taskpriority,
	NULL
	);
}
