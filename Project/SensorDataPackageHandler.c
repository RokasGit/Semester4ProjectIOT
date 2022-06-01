/*
* SensorDataPackageHandler.c
*
* Created: 5/3/2022 7:14:13 PM
*  Author: rokas
*/
#include "SensorDataPackageHandler.h"
// CO2 measurement in ppm;
static uint16_t co2Ppm;
// humidity measurement in percents
static uint16_t humidityPercent;
// temperature measurement in celsius.
static uint16_t temperatureCelsius;
// window state
static uint16_t servoState;
// LoraWAN package size;
static uint8_t loraPackageLength;
lora_driver_payload_t *uplink_payload;
// creates lora payload
void sensorDataPackageHandler_createLoraPayload(){
	uplink_payload=pvPortMalloc(sizeof(lora_driver_payload_t));
}

// function to set co2 in the package;
void sensorDataPackageHandler_setCo2Ppm(uint16_t ppm){
	co2Ppm = ppm;
}
// function to set Temperature celsius for package.
void sensorDataPackageHandler_setTemperature(uint16_t celsius){
	temperatureCelsius= celsius;
}
// function to set Humidity for package.
void sensorDataPackageHandler_setHumidity(uint16_t hum){
	humidityPercent=hum;
}
// function to set LoraWAN package size;
void sensorDataPackageHandler_setPackageLength(uint8_t packageLength){
	loraPackageLength=packageLength;
}
// function to set servo state
void sensorDataPackageHandler_setWindowState(uint16_t state){
servoState=state;
}
// function to create a package to upload to loraWAN gateway.
lora_driver_payload_t sensorDataPackageHandler_getLoraPayload(uint8_t port_No){
	
	
	
	
	if(uplink_payload !=NULL){
		uplink_payload->portNo=port_No;
		uplink_payload->len=loraPackageLength;
		uplink_payload->bytes[0]=co2Ppm >> 8;
		uplink_payload->bytes[1]=co2Ppm & 0xFF;
		uplink_payload->bytes[2]=temperatureCelsius >> 8;
		uplink_payload->bytes[3]=temperatureCelsius & 0xFF;
		uplink_payload->bytes[4]=humidityPercent >> 8;
		uplink_payload->bytes[5]=humidityPercent &0xFF;
		uplink_payload->bytes[6]=servoState >> 8;
		uplink_payload->bytes[7]=servoState &0xFF;
	}
	return *uplink_payload;
}