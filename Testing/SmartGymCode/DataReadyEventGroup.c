/*
 * DataReadyEventGroup.c
 *
 * Created: 5/7/2022 3:45:00 PM
 *  Author: rokas
 */
#include "DataReadyEventGroup.h"
void dataReadyEventGroup_initialize() {
	dataReadyEventGroup = xEventGroupCreate();
}
