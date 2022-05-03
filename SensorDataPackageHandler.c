/*
* SensorDataPackageHandler.c
*
* Created: 5/3/2022 7:14:13 PM
*  Author: rokas
*/
#include "SensorDataPackageHandler.h"
// CO2 measurement in ppm;
static uint16_t co2Ppm;
// LoraWAN package size;
static uint8_t loraPackageLength;

// function to set co2 in the package;
void sensorDataPackageHandler_setCo2Ppm(uint16_t ppm){
	co2Ppm = ppm;
}
// function to set LoraWAN package size;
void sensorDataPackageHandler_setPackageLength(uint8_t packageLength){
	loraPackageLength=packageLength;
}
lora_driver_payload_t sensorDataPackageHandler_getLoraPayload(uint8_t port_No){
	lora_driver_payload_t *uplink_payload;
	
	uplink_payload=pvPortMalloc(sizeof(lora_driver_payload_t));
	
	if(uplink_payload !=NULL){
		uplink_payload->portNo=port_No;
		uplink_payload->len=loraPackageLength;
		uplink_payload->bytes[0]=co2Ppm >> 8;
		uplink_payload->bytes[1]=co2Ppm & 0xFF;
	}
	return *uplink_payload;
}