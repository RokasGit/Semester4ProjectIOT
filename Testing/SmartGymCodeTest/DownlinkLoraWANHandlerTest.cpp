#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <DownlinkLoraWANHandler.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"

}

class DownlinkLoraWANHandlerTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(xMessageBufferReceive)
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(DownlinkLoraWANHandlerTest, ApplicationCreateTask) {
	downlinkLoraWANHandler_createTask(3);
	ASSERT_EQ(1, xTaskCreate_fake.call_count);
}
TEST_F(DownlinkLoraWANHandlerTest, ApplicationTask) {
	downlinkLoraWANHandler_TaskRun();
	ASSERT_EQ(1, xMessageBufferReceive_fake.call_count);
	ASSERT_EQ(1, vTaskDelay_fake.call_count);
}