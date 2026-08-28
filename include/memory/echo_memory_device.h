#pragma once
#include "memory/memory_device.h"

namespace gameboy {

    template <addr16_t StartAddr, addr16_t EndAddr, addr16_t EchoAddr>
    class echo_memory_device : public memory_device {

        static_assert(StartAddr >= 0 && StartAddr <= 0xFFFF);
        static_assert(EndAddr >= 0 && EndAddr <= 0xFFFF);
        static_assert(EchoAddr >= 0 && EchoAddr <= 0xFFFF);
        static_assert(StartAddr <= EndAddr);

        memory_device* device;

        addr16_t get_echo_addr(addr16_t addr) {
            return (addr - StartAddr) + EchoAddr;
        }

    public:

        echo_memory_device() : device(nullptr) {}
        echo_memory_device(memory_device* device) : device(device) {}

        bool in_range(addr16_t addr) const override
        {
            return addr >= StartAddr && addr <= EndAddr;
        }

        uint8_t read(addr16_t addr) override
        {
            addr16_t echoAddr = get_echo_addr(addr);
            return device->read(echoAddr);
        }

        void write(addr16_t addr, uint8_t value) override
        {
            addr16_t echoAddr = get_echo_addr(addr);
            device->write(echoAddr, value);
        }
    };

}