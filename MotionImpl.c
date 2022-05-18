/*
 * MotionImpl.c
 *
 * Created: 5/18/2022 12:30:18 PM
 *  Author: Nick
 */ 

#include "Motion.h"

#define MotionTaskStackSize (configMINIMAL_STACK_SIZE)


static uint16_t NrOfMovements;

hcsr501_p hcsr501Inst = NULL;

void Motion_initializeDriver(){

	hcsr501Inst = hcsr501_create(&PORTE, PE5);
	
	if ( NULL != hcsr501Inst )
	{
		// Driver created OK
		// If NULL is returned the driver is not created!!!
	} else {
		printf("Motion Driver FAILED TO BE INITIALIZED");
	}
}


void Motion_Task(void* parameter){
	
	for(;;){
		
		if ( hcsr501_isDetecting(hcsr501Inst) )
		{
			// Something is detected
			configuration_setIsMoving(1);
			NrOfMovements++;
			printf("MOVEMENT DETECTED: %d times \n",NrOfMovements);
		}
		else
		{
			// Nothing is detected
			configuration_setIsMoving(0);
			printf("FCK OFF not moving %d \n", configuration_getIsMoving());
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}
	
}

uint16_t Motion_NrOfMovements(){
	return NrOfMovements;
}


void Motion_createTask(UBaseType_t Taskpriority){
	Motion_initializeDriver();
	
	xTaskCreate(
	Motion_Task,
	"Motion Task",
	MotionTaskStackSize,
	NULL,
	tskIDLE_PRIORITY + Taskpriority,
	NULL
	);
	
}


