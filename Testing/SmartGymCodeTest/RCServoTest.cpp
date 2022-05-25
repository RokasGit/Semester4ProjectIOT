#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <RCServo.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
}

class RCServoTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(RCServoTest, ApplicationCreateTask) {
	rcServo_CreateTask(3);
	ASSERT_EQ(1, xTaskCreate_fake.call_count);
}


TEST_F(RCServoTest, ApplicationTask) {
	rcServo_TaskRun();
	ASSERT_EQ(1, vTaskDelay_fake.call_count);
}

TEST_F(RCServoTest, ApplicationSemaphore) {
	rcServo_CreateSemaphore();
	ASSERT_EQ(1, xSemaphoreCreateBinary_fake.call_count);
}



