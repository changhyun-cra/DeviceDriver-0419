#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project7/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, ReadFiveTimesSuccess) {
	FlashMemoryDeviceMock mock;

	EXPECT_CALL(mock, read)
		.Times(5)
		.WillRepeatedly(Return(10));

	DeviceDriver driver(&mock);
	EXPECT_EQ(driver.read(0x00), 10);
}

TEST(TestCaseName, ReadFiveTimesFail) {
	FlashMemoryDeviceMock mock;

	EXPECT_CALL(mock, read)
		.Times(5)
		.WillOnce(Return(9))
		.WillOnce(Return(9))
		.WillOnce(Return(9))
		.WillOnce(Return(9))
		.WillOnce(Return(10));

	DeviceDriver driver{ &mock };
	EXPECT_THROW(driver.read(0x00), ReadFailException);
}

TEST(TestCaseName, WriteSuccess) {
	FlashMemoryDeviceMock mock;

	EXPECT_CALL(mock, read)
		.Times(1)
		.WillOnce(Return(0xFF));
	EXPECT_CALL(mock, write(0x00, 777))
		.Times(1);

	DeviceDriver driver{ &mock };
	driver.write(0x00, 777);
}

TEST(TestCaseName, WriteFail) {
	FlashMemoryDeviceMock mock;

	EXPECT_CALL(mock, read)
		.Times(1)
		.WillOnce(Return(0xFE));

	DeviceDriver driver{ &mock };
	EXPECT_THROW(driver.write(0x00, 777), WriteFailException);
	
}