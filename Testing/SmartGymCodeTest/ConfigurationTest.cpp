#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
extern "C" {
#include <Configuration.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

}

class ConfigurationTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(xSemaphoreGive);
		RESET_FAKE(xSemaphoreTake);
		configuration_create();
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(ConfigurationTest, DefaulValueTest) {
	// testing constructor, getServoState,getMaxCo2Level, getMaxHumidityLevel, getMinHumidityLevel, getIsMoving,getAutomation, semaphores
	ASSERT_EQ(1, xSemaphoreGive_fake.call_count);
	configuration_getServoState();
	EXPECT_EQ((uint16_t)-100, configuration_getServoStateRun());
	ASSERT_EQ(2, xSemaphoreGive_fake.call_count);
	ASSERT_EQ(1, xSemaphoreTake_fake.call_count);
	EXPECT_EQ((int) 0,configuration_getIsMoving());
	EXPECT_EQ((uint16_t)1000, configuration_getMaxCO2Level());
	EXPECT_EQ((uint16_t)550, configuration_getMaxHumidityLevel());
	EXPECT_EQ((uint16_t)400, configuration_getMinHumidityLevel());
	configuration_getAutomation();
	ASSERT_EQ(2, xSemaphoreTake_fake.call_count);
	EXPECT_EQ(0, configuration_getAutomationRun());
	ASSERT_EQ(3, xSemaphoreGive_fake.call_count);
}
TEST_F(ConfigurationTest, SettersTest) {
	// testing setServoState
	ASSERT_EQ(1, xSemaphoreGive_fake.call_count);
	configuration_setServoState(100);
	ASSERT_EQ(1, xSemaphoreTake_fake.call_count);
	configuration_setServoStateRun(100);
	ASSERT_EQ(3, xSemaphoreGive_fake.call_count);
	EXPECT_EQ((uint16_t)100, configuration_getServoStateRun());
	// testing setAutomation
	configuration_setAutomation(1);
	ASSERT_EQ(2, xSemaphoreTake_fake.call_count);
	configuration_setAutomationRun(1);
	ASSERT_EQ(5, xSemaphoreGive_fake.call_count);
	EXPECT_EQ(1, configuration_getAutomationRun());
	ASSERT_EQ(6, xSemaphoreGive_fake.call_count);
}

