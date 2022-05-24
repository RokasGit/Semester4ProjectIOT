/*
* MeasureEventGroup.c
*
* Created: 5/3/2022 8:19:33 PM
*  Author: rokas
*/
#include "MeasureEventGroup.h"

//function to initialize the measure event group 
void measureEventGroup_initialize(){
	measureEventGroup = xEventGroupCreate();
	xEventGroupSetBits(measureEventGroup, BIT_READY_TO_MEASURE_CO2);
}
