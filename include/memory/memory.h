#pragma once
#include <vector>
#include <exception>
#include "memory/basic_memory_device.h"
#include "memory/echo_memory_device.h"

namespace gameboy {

    template<addr16_t StartAddr, addr16_t EndAddr>
    using ROM = basic_memory_device<StartAddr, EndAddr, true, false>;

    template<addr16_t StartAddr, addr16_t EndAddr>
    using RAM = basic_memory_device<StartAddr, EndAddr, true, false>;

    template<addr16_t StartAddr, addr16_t EndAddr>
    using Unused = basic_memory_device<StartAddr, EndAddr, false, false>;

    template<addr16_t StartAddr, addr16_t EndAddr, addr16_t EchoAddr>
    using Echo = echo_memory_device<StartAddr, EndAddr, EchoAddr>;
    
    class memory : public memory_device {

        ROM<0x0000,0x3FFF> rom_bank0;
        ROM<0x4000,0x7FFF> rom_bankN;
        RAM<0x8000,0x9FFF> vram;
        RAM<0xA000,0xBFFF> external_ram;
        RAM<0xC000,0xDFFF> wram;
        Echo<0xE000,0xFDFF,0xC000> echo;
        RAM<0xFE00,0xFE9F> oam;
        Unused<0xFEA0,0xFEFF> unused;
        RAM<0xFF00,0xFF7F> io_registers;
        RAM<0xFF80,0xFFFE> hram;
        RAM<0xFFFF,0xFFFF> ie_register;

        std::array<memory_device*, 15> device_pages{};
        std::array<std::vector<memory_device*>, 16> device_pages_F{};

        memory_device* get_addr_device(addr16_t addr) {
            uint8_t digit4 = addr >> 12;
            uint8_t digit3 = (addr >> 8) & 0xF;
            if (digit4 == 0xF) {
                for (memory_device* device : device_pages_F[digit3]) {
                    if (device->in_range(addr)) return device;
                }
                throw new std::exception();
            }
            return device_pages[digit4];
        }

    public:

        memory() {
            echo = Echo<0xE000,0xFDFF,0xC000>(this);

            device_pages[0x0] = &rom_bank0;
            device_pages[0x1] = &rom_bank0;
            device_pages[0x2] = &rom_bank0;
            device_pages[0x3] = &rom_bank0;
            device_pages[0x4] = &rom_bankN;
            device_pages[0x5] = &rom_bankN;
            device_pages[0x6] = &rom_bankN;
            device_pages[0x7] = &rom_bankN;
            device_pages[0x8] = &vram;
            device_pages[0x9] = &vram;
            device_pages[0xA] = &external_ram;
            device_pages[0xB] = &external_ram;
            device_pages[0xC] = &wram;
            device_pages[0xD] = &wram;
            device_pages[0xE] = &echo;

            device_pages_F[0x0] = std::vector<memory_device*>{&echo};
            device_pages_F[0x1] = std::vector<memory_device*>{&echo};
            device_pages_F[0x2] = std::vector<memory_device*>{&echo};
            device_pages_F[0x3] = std::vector<memory_device*>{&echo};
            device_pages_F[0x4] = std::vector<memory_device*>{&echo};
            device_pages_F[0x5] = std::vector<memory_device*>{&echo};
            device_pages_F[0x6] = std::vector<memory_device*>{&echo};
            device_pages_F[0x7] = std::vector<memory_device*>{&echo};
            device_pages_F[0x8] = std::vector<memory_device*>{&echo};
            device_pages_F[0x9] = std::vector<memory_device*>{&echo};
            device_pages_F[0xA] = std::vector<memory_device*>{&echo};
            device_pages_F[0xB] = std::vector<memory_device*>{&echo};
            device_pages_F[0xC] = std::vector<memory_device*>{&echo};
            device_pages_F[0xD] = std::vector<memory_device*>{&echo};
            device_pages_F[0xE] = std::vector<memory_device*>{&oam, &unused};
            device_pages_F[0xF] = std::vector<memory_device*>{&io_registers, &hram, &ie_register};
        }
        virtual ~memory() noexcept = default; 


        bool in_range(addr16_t addr) const override
        {
            return addr >= 0 && addr <= 0xFFFF;
        }

        uint8_t read(addr16_t addr) override
        {
            memory_device* device = get_addr_device(addr);
            return device->read(addr);
        }

        void write(addr16_t addr, uint8_t value) override
        {
            memory_device* device = get_addr_device(addr);
            device->write(addr, value);
        }

    };
}