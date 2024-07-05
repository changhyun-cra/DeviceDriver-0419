#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++) {        
        if (result != (int)(m_hardware->read(address))) {
            throw ReadFailException("Read 결과가 모두 같은 값이 아닙니다");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    int value = (int)(m_hardware->read(address));
    if (value != 0xFF) {
        throw WriteFailException("이미 값이 적혀있습니다.");
    }
    m_hardware->write(address, (unsigned char)data);
}
