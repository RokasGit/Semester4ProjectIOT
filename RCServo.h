/*
 * RCServo.h
 *
 * Created: 5/18/2022 4:09:53 PM
 *  Author: rokas
 */ 
#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <rc_servo.h>
#include <semphr.h>

#include "Configuration.h"

SemaphoreHandle_t rcServoSemaphore;

void rcServo_CreateSemaphore();
void rcServo_Task();
void rcServo_CreateTask(UBaseType_t rcServo_task_priority);