#pragma once
#include "FlashMemoryDevice.h"
#include <stdexcept>
#include <string>

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {
public:
    ReadFailException(std::string msg) : exception{ msg.c_str() } {}
};

class WriteFailException : public std::exception {
public:
    WriteFailException(std::string msg) : exception{ msg.c_str() } {}
};