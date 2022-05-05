/*
 * TemperatureImpl.c
 *
 * Created: 5/3/2022 10:11:14 PM
 *  Author: Nick
 */ 

#include "Temperature.h"

#define TemperatureTaskStackSize (configMINIMAL_STACK_SIZE)

static uint16_t Temp;



void Temperature_initializeDriver(){
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();

	if ( HIH8120_OK == returnCode )
	{
		printf("Temperature Driver initialized");
	}
	
	else {
		printf("Error: %s", returnCode);
	}
}

void Temperature_Task(void* parameter){
	
	for(;;){
		EventBits_t measureBits;
		measureBits = xEventGroupWaitBits(
		measureEventGroup, // measure event group
		BIT_READY_TO_MEASURE_TEMPERATURE, // wait for temperature ready to measure
		pdFALSE, // no need to clear, clearing manually in callback
		pdTRUE, // wait for all bits(ONLY CO2)
		portMAX_DELAY // wait infinity till timeout
		);
		
		if((measureBits & BIT_READY_TO_MEASURE_TEMPERATURE)==BIT_READY_TO_MEASURE_TEMPERATURE){
			
			hih8120_driverReturnCode_t returnCode = hih8120_wakeup();
			
			vTaskDelay(pdMS_TO_TICKS(55)); 
			
			if(returnCode!= HIH8120_OK){
				printf("Temperature MEASSURING FAILED!!");
			}
			
			if(returnCode==HIH8120_OK){
				Temp = hih8120_getTemperature_x10();
				clearTemperatureBit();
			}
			
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
}

static void clearTemperatureBit(){
	EventBits_t clearedTempBit;
	
	clearedTempBit = xEventGroupClearBits(
	measureEventGroup, // clearing in measure event group the temperature bit after taking the measure;
	BIT_READY_TO_MEASURE_TEMPERATURE); // clearing the temperature bit
	if((clearedTempBit & BIT_READY_TO_MEASURE_TEMPERATURE) == BIT_READY_TO_MEASURE_TEMPERATURE){
		// BIT temperature was set before clear was called, now will be clear
		}else if((clearedTempBit & BIT_READY_TO_MEASURE_TEMPERATURE) !=0){
		/* temperature bit was set before clear was called,
		It will be clear now.*/
		}else{
		// Bits were not set
	}
}

void Temperature_createTask(UBaseType_t Taskpriority){
	Temperature_initializeDriver();
	
	xTaskCreate(
	Create_TemperatureTask,		
	"Temperature Task",		
	TemperatureTaskStackSize,
	NULL,
	tskIDLE_PRIORITY + Taskpriority,
	NULL
	);
	
}
