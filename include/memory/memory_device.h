#pragma once
#include "types.h"

namespace gameboy {
    class memory_device {

    public:

        virtual ~memory_device() = default;

        virtual bool in_range(addr16_t addr) const = 0;

        virtual uint8_t read(addr16_t addr) = 0;
        virtual void write(addr16_t addr, uint8_t value) = 0;
    };
}