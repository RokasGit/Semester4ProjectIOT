#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <Humidity.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
}

class HumidityTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(HumidityTest, ApplicationCreateTask) {
	Humidity_createTask(3);
	ASSERT_EQ(1, xTaskCreate_fake.call_count);
}
TEST_F(HumidityTest, ApplicationTask) {
	Humidity_Task();
	ASSERT_EQ(1, vTaskDelay_fake.call_count);
}