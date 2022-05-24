/*
* Configuration.c
*
* Created: 5/18/2022 12:13:40 PM
*  Author: rokas, farouk
*/
#include "Configuration.h"

//function to create the configuration 
void configuration_create(){
	rcServoState=-100;
	isMoving=0;
	automationOff=0;
	maxCO2Level = 1000;
	maxHumidityLevel = 550;
	minHumidityLevel = 400;
	configurationSemaphore = xSemaphoreCreateMutex();
	xSemaphoreGive( configurationSemaphore);
}

//function to set rc servo state
void configuration_setServoState(uint16_t state){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE){
		rcServoState=state;
		xSemaphoreGive(configurationSemaphore);
		xSemaphoreGive(rcServoSemaphore);
	}
}

//function to get rc servo state
uint16_t configuration_getServoState(){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE){
		xSemaphoreGive(configurationSemaphore);
		return rcServoState;
	}
}

//function to get if the motion sensor detected something 
int configuration_getIsMoving(){
	return isMoving;
}

//function to set if the motion sensor detected something 
void configuration_setIsMoving(int moving){
	isMoving=moving;
	
	configuration_SetLightOnAndOf();
}

//function to set light on and of
void configuration_SetLightOnAndOf(){
		if (isMoving == 1)
		{
			printf("leds on!!!!!!!!!!!!!!!!!!! %d",isMoving);
			// Something is detected
			status_leds_ledOn(led_ST4);
		}else{
			status_leds_ledOff(led_ST4);
		}
		
}

//function to get the max co2 level 
uint16_t configuration_getMaxCO2Level(){
	return maxCO2Level;
}

//function to get if the max humidity level 
uint16_t configuration_getMaxHumidityLevel(){
	return maxHumidityLevel;
}

//function to get if the min humidity level 
uint16_t configuration_getMinHumidityLevel(){
	return minHumidityLevel;
}

//function to setup automation
void configuration_setAutomation(int automation){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE)
	{
		automationOff=automation;
		xSemaphoreGive(configurationSemaphore);
	}
}

//function to get automation
int configuration_getAutomation(){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE){
		xSemaphoreGive(configurationSemaphore);
		return automationOff;
	}
}
