/*
 * DataReadyEventGroup.c
 *
 * Created: 5/7/2022 3:45:00 PM
 *  Author: rokas
 */ 
#include "DataReadyEventGroup.h"

//function to initialize the data redy event group
void dataReadyEventGroup_initialize(){
	dataReadyEventGroup = xEventGroupCreate();
}
