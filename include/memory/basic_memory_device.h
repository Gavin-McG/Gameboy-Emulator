#pragma once
#include <array>
#include "memory/memory_device.h"

namespace gameboy {

    template <addr16_t StartAddr, addr16_t EndAddr, bool CanRead, bool CanWrite>
    class basic_memory_device : public memory_device {

        static_assert(StartAddr >= 0 && StartAddr <= 0xFFFF);
        static_assert(EndAddr >= 0 && EndAddr <= 0xFFFF);
        static_assert(StartAddr <= EndAddr);

        static constexpr std::size_t Size = EndAddr - StartAddr + 1;

        std::array<uint8_t, Size> data{};

    public:

        bool in_range(addr16_t addr) const override
        {
            return addr >= StartAddr && addr <= EndAddr;
        }

        uint8_t read(addr16_t addr) override
        {
            if constexpr (!CanRead)
                return 0xFF;

            return data[addr - StartAddr];
        }

        void write(addr16_t addr, uint8_t value) override
        {
            if constexpr (CanWrite)
                data[addr - StartAddr] = value;
        }
    };

}