/*
 * MotionImpl.c
 *
 * Created: 5/18/2022 12:30:18 PM
 *  Author: Nick
 */ 

#include "Motion.h"

#define MotionTaskStackSize (configMINIMAL_STACK_SIZE)

static int isMoving;

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
		EventBits_t measureBits;
		measureBits = xEventGroupWaitBits(
		measureEventGroup, // measure event group
		BIT_READY_TO_MEASURE_MOTION, // wait for temperature ready to measure
		pdFALSE, // no need to clear, clearing manually in callback
		pdTRUE, // wait for all bits(ONLY CO2)
		portMAX_DELAY // wait infinity till timeout
		);
		
		if((measureBits & BIT_READY_TO_MEASURE_MOTION)==BIT_READY_TO_MEASURE_MOTION){
			
			if ( hcsr501_isDetecting(hcsr501Inst) )
			{
				// Something is detected
				isMoving = 1;
			}
			else
			{
				// Nothing is detected
				isMoving = 0;
			}
			
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
}


static void clearMotionBit(){
	EventBits_t clearedMotionBit;
	
	clearedMotionBit = xEventGroupClearBits(
	measureEventGroup, // clearing in measure event group the motion bit after taking the measure;
	BIT_READY_TO_MEASURE_MOTION); // clearing the motion bit
	if((clearedMotionBit & BIT_READY_TO_MEASURE_MOTION) == BIT_READY_TO_MEASURE_MOTION){
		// BIT motion was set before clear was called, now will be clear
		}else if((clearedMotionBit & BIT_READY_TO_MEASURE_MOTION) !=0){
		/* motion bit was set before clear was called,
		It will be clear now.*/
		}else{
		// Bits were not set
	}
}


int Motion_getIsMoving (){
	return isMoving;
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


