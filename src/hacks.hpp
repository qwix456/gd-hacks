#include "utils.hpp"

namespace hacks
{
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

    static void noclip(bool active)
    {
        if(active)
            writeBytes(base + 0x2E0AD9, {0xE9, 0x9C, 0x07, 0x00, 0x00, 0x90});
        else
            writeBytes(base + 0x2E0AD9, {0xF, 0x85, 0x9B, 0x07, 0x00, 0x00});
    }

    static void practice(bool active)
    {
        if(active)
            writeBytes(base + 0x2E4F35, {0xEB});
        else
            writeBytes(base + 0x2E4F35, {0x75});
    }

    static void unlock_all(bool active)
    {
        if(active) {
            writeBytes(base + 0x1EDCC8, {0xEB});
            writeBytes(base + 0x1EE4E4, {0xEB});
            writeBytes(base + 0x5FC2E, {0x90, 0x90});
        }
        else
        {
            writeBytes(base + 0x1EDCC8, {0x75});
            writeBytes(base + 0x1EE4E4, {0x75});
            writeBytes(base + 0x5FC2E, {0x74});
        }
    }

    static void copy_hack(bool active)
    {
        if(active)
            writeBytes(base + 0x24E0CE, {0xE9, 0xE6, 0x00, 0x00, 0x00, 0x90});
        else
            writeBytes(base + 0x24E0CE, {0x0F, 0x8F, 0xE5, 0x00, 0x00, 0x00});
    }

    static void verify_hack(bool active)
    {
        if(active)
            writeBytes(base + 0x381BF5, {0xEB});
        else
            writeBytes(base + 0x381BF5, {0x74});
    }

    static void keymaster_bypass(bool active)
    {
        if(active)
            writeBytes(base + 0x70CB5, {0x90, 0x90});
        else
            writeBytes(base + 0x70CB5, {0x74});
    }
} // namespace name
