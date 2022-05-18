/*
 * MotionImpl.c
 *
 * Created: 5/18/2022 12:30:18 PM
 *  Author: Nick
 */ 

#include "Motion.h"

#define MotionTaskStackSize (configMINIMAL_STACK_SIZE)

static int isMoving;

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
			isMoving = 1;
			NrOfMovements++;
			printf("MOVEMENT DETECTED");
		}
		else
		{
			// Nothing is detected
			isMoving = 0;
		}
		
	}
	
}


int Motion_getIsMoving (){
	return isMoving;
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


