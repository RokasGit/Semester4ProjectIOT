/*
 * TemperatureImpl.c
 *
 * Created: 5/3/2022 10:11:14 PM
 *  Author: Nick
 */ 

#include "Temperature.h"

#define TemperatureTaskStackSize (configMINIMAL_STACK_SIZE)


void initializeDriver(){
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();

	if ( HIH8120_OK == returnCode )
	{
		printf("Temperature Driver initialized");
	}
	
	else {
		printf("Error: %s", returnCode);
	}
}

void TemperatureTask(void* parameter){
	
}

void createTemperatureClass(UBaseType_t Taskpriority){
	initializeDriver();
	
	xTaskCreate(
	TemperatureTask,		
	"Temperature Task",		
	TemperatureTaskStackSize,
	NULL,
	Taskpriority,
	NULL
	);
	
}
