#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++) {        
        if (result != (int)(m_hardware->read(address))) {
            throw ReadFailException("Read ����� ��� ���� ���� �ƴմϴ�");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    int value = (int)(m_hardware->read(address));
    if (value != 0xFF) {
        throw WriteFailException("�̹� ���� �����ֽ��ϴ�.");
    }
    m_hardware->write(address, (unsigned char)data);
}
