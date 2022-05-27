#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <DownlinkMessageBuffer.h>
#include <DataReadyEventGroup.h>
#include <MeasureEventGroup.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "event_groups.h"

}

class EventGroupsBufferTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(xMessageBufferCreate);
		RESET_FAKE(xEventGroupCreate);
		RESET_FAKE(xEventGroupSetBits);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(EventGroupsBufferTest, initialize) {
	downlinkMessageBuffer_create();
	ASSERT_EQ(1, xMessageBufferCreate_fake.call_count);
	measureEventGroup_initialize();
	ASSERT_EQ(1, xEventGroupCreate_fake.call_count);
	ASSERT_EQ(1, xEventGroupSetBits_fake.call_count);
	dataReadyEventGroup_initialize();
	ASSERT_EQ(2, xEventGroupCreate_fake.call_count);
}