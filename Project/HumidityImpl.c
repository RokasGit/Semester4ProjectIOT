/*
 * HumidityImpl.c
 *
 * Created: 5/4/2022 10:43:34 PM
 *  Author: Farouk
 */ 

#include "Humidity.h"

#define HumidityTaskStackSize (configMINIMAL_STACK_SIZE)

static uint16_t Hum;

//function to get Humidity
uint16_t Humidity_getHumidity(){
	return Hum;
}

//function to initialize the humidity driver, checks if the return code is ok and print out the result
void Humidity_initializeDriver(){
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();

	if ( HIH8120_OK == returnCode )
	{
		printf("Humidity Driver initialized");
	}
	
	else {
		printf("Error: %d", returnCode);
	}
}

//function to initialize the Humidity task, first it wakes up the driver then it takes the measure and sets the Humidity bits
void Humidity_Task(void* parameter){
	
	
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
			
			hih8120_driverReturnCode_t returnCode = hih8120_wakeup();
			
			vTaskDelay(pdMS_TO_TICKS(55));
			
			if(HIH8120_OK !=  hih8120_measure()){
				printf("Humidity MEASSURING FAILED!!");
				continue;
			}

			vTaskDelay(pdMS_TO_TICKS(10));
			
			if(returnCode==HIH8120_OK){
				Hum = hih8120_getHumidityPercent_x10();
				xEventGroupSetBits(dataReadyEventGroup,BIT_READY_TO_SEND_HUMIDITY);
				clearHumidityBit();
			}
			
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
}

//function to clear Humidity bits  
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

//function to create the Humidity task 
void Humidity_createTask(UBaseType_t Taskpriority){
	Humidity_initializeDriver();
	
	xTaskCreate(
	Humidity_Task,
	"Humidity Task",
	HumidityTaskStackSize,
	NULL,
	tskIDLE_PRIORITY + Taskpriority,
	NULL
	);
}
