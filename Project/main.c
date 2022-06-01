/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>

// Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

// Application functionality
#include "DataReadyEventGroup.h"
#include "MeasureEventGroup.h"
#include "Application.h"
#include "DownlinkMessageBuffer.h"
#include "Configuration.h"
#include "SensorDataPackageHandler.h"
// Sensors/Hardware
#include "Temperature.h"
#include "CO2Sensor.h"
#include "Humidity.h"
#include "RCServo.h"



// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);


void initialiseGroupsBuffers(){
	dataReadyEventGroup_initialize();
	measureEventGroup_initialize();
	downlinkMessageBuffer_create();
	configuration_create();
	rcServo_CreateSemaphore();
	sensorDataPackageHandler_createLoraPayload();
	
}
/*-----------------------------------------------------------*/
void createTasks(void)
{
	CO2Sensor_createTask(1);
	Temperature_createTask(1);
	Humidity_createTask(1);
	// motion sensor is off, as there is not enough Heap space to initialize the task and driver.
	//Motion_createTask(1);
	application_createTask(2);
	rcServo_CreateTask(1);
	downlinkLoraWANHandler_createTask(3);
	
}

/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	// creating buffers and groups
	initialiseGroupsBuffers();
	// Let's create some tasks
	createTasks();

	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(6); // Priority 5 for internal task
	
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_initialise(1, downlinkMessageBuffer);
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(4);
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	/* Replace with your application code */
	while (1)
	{

	}
}

