#include "Configuration.h"
void configuration_create() {
	rcServoState = -100;
	isMoving = 0;
	automationOff = 0;
	maxCO2Level = 1000;
	maxHumidityLevel = 550;
	minHumidityLevel = 400;
	ledOn = 0;
	configurationSemaphore = xSemaphoreCreateMutex();
	xSemaphoreGive(configurationSemaphore);
}
void configuration_setServoState(uint16_t state) {
	if (xSemaphoreTake(configurationSemaphore, portMAX_DELAY) == pdTRUE) {
		rcServoState = state;
		xSemaphoreGive(configurationSemaphore);
		xSemaphoreGive(rcServoSemaphore);
	}
}
void configuration_setServoStateRun(uint16_t state) {
	rcServoState = state;
	xSemaphoreGive(configurationSemaphore);
	xSemaphoreGive(rcServoSemaphore);
}
uint16_t configuration_getServoState() {
	if (xSemaphoreTake(configurationSemaphore, portMAX_DELAY) == pdTRUE) {
		uint16_t state = configuration_getServoStateRun();
		return state;
	}
}
uint16_t configuration_getServoStateRun() {
	xSemaphoreGive(configurationSemaphore);
	return rcServoState;
}
int configuration_getIsMoving() {
	return isMoving;
}
void configuration_setIsMoving(int moving) {
	isMoving = moving;

	configuration_SetLightOnAndOf();
}

void configuration_SetLightOnAndOf() {
	if (isMoving == 1)
	{
		printf("leds on!!!!!!!!!!!!!!!!!!! %d", isMoving);
		// Something is detected
		ledOn = 1;
	}
	else {
		ledOn = 0;
	}

}
uint16_t configuration_getMaxCO2Level() {
	return maxCO2Level;
}
uint16_t configuration_getMaxHumidityLevel() {
	return maxHumidityLevel;
}
uint16_t configuration_getMinHumidityLevel() {
	return minHumidityLevel;
}
void configuration_setAutomation(int automation) {
	if (xSemaphoreTake(configurationSemaphore, portMAX_DELAY) == pdTRUE)
	{
		automationOff = automation;
		xSemaphoreGive(configurationSemaphore);
	}
}
void configuration_setAutomationRun(int automation) {
	automationOff = automation;
	xSemaphoreGive(configurationSemaphore);
}
int configuration_getAutomation() {
	if (xSemaphoreTake(configurationSemaphore, portMAX_DELAY) == pdTRUE) {
		xSemaphoreGive(configurationSemaphore);
		return automationOff;
	}
}
int configuration_getAutomationRun() {
	xSemaphoreGive(configurationSemaphore);
	return automationOff;
}
