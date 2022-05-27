/*
 * Motion.h
 *
 * Created: 5/18/2022 12:26:28 PM
 *  Author: Nick
 */


#include <stdio.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>


void Motion_initializeDriver();
void Motion_Task(void* parameter);
uint16_t Motion_NrOfMovements();
void Motion_TaskRun();
void Motion_createTask(UBaseType_t Taskpriority);
