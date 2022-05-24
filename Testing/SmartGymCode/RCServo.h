#pragma once

#pragma once

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>



SemaphoreHandle_t rcServoSemaphore;

void rcServo_CreateSemaphore();
void rcServo_Task();
void rcServo_CreateTask(UBaseType_t rcServo_task_priority);
void rcServo_TaskRun();
