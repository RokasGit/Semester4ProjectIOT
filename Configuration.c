/*
 * Configuration.c
 *
 * Created: 5/18/2022 12:13:40 PM
 *  Author: rokas
 */ 
#include "Configuration.h"


void configuration_create(){
	rcServoState=-100;
	configurationSemaphore = xSemaphoreCreateMutex();
	xSemaphoreGive( configurationSemaphore);
}
void configuration_setServoState(uint16_t state){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE){
		rcServoState=state;
		xSemaphoreGive(configurationSemaphore);
		xSemaphoreGive(rcServoSemaphore);
	}
}
uint16_t configuration_getServoState(){
	if(xSemaphoreTake(configurationSemaphore,portMAX_DELAY)==pdTRUE){
		xSemaphoreGive(configurationSemaphore);
		return rcServoState;
	}
}
