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

//function to initialize the Motion driver, creates the instance and sets the port
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

//function to initialize the Motion task, checks if the sensor detects something and if it does adds to the nr of movements variable and sets isMoving in configuration 
void Motion_Task(void* parameter){
	
	for(;;){
		
		//Motion_initializeDriver();
		
		if ( hcsr501_isDetecting(hcsr501Inst) )
		{
			// Something is detected
			configuration_setIsMoving(1);
			NrOfMovements++;
			printf("MOVEMENT DETECTED: %d times \n",NrOfMovements);
			//hcsr501_destroy(hcsr501Inst);
			vTaskDelay(pdMS_TO_TICKS(300000));
		}
		else
		{
			// Nothing is detected
			configuration_setIsMoving(0);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
		
		
	}
	
}

//function to get nr of movements 
uint16_t Motion_NrOfMovements(){
	return NrOfMovements;
}

//function to create the Motion task 
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


