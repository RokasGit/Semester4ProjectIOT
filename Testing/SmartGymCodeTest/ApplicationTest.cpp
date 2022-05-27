#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <Application.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

}

class ApplicationTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(ApplicationTest, ApplicationCreateTask) {
	application_createTask(3);
	ASSERT_EQ(1, xTaskCreate_fake.call_count);
}
TEST_F(ApplicationTest, ApplicationTask) {
	application_TaskRun(NULL);
	ASSERT_EQ(1, xEventGroupWaitBits_fake.call_count);
	ASSERT_EQ(1, vTaskDelay_fake.call_count);
	ASSERT_EQ(1, xEventGroupSetBits_fake.call_count);
}