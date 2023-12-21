#include <vector>
#include <string>
#include <windows.h>

struct settings
{
    bool noclip;
    bool practice_music_hack;
    bool unlock_all;
    bool copy_hack;
    bool verify_hack;
    bool no_wave_trail;
    bool slider_bypass;
    bool keymaster_bypass;
    bool buy_item_bypass;
    bool scratch_bypass;
    bool potbor_bypass;
    bool the_mechanic_bypass;
    bool diamond_shopkeeper_bypass;
};

inline bool writeBytes(std::uintptr_t address, std::vector<uint8_t> bytes)
{
        return WriteProcessMemory(
        GetCurrentProcess(),
        reinterpret_cast<LPVOID>(address),
        bytes.data(),
        bytes.size(),
        nullptr);
}

namespace hacks
{
    inline uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    inline HMODULE cocos_base = GetModuleHandleA("libcocos2d.dll");

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

    static void slider_bypass(bool active)
    {
        if(active) {
            writeBytes(base + 0x4CDAA, {0xEB});
            writeBytes(base + 0x4CDD8, {0xEB});
        }
        else{
            writeBytes(base + 0x4CDAA, {0x76});
            writeBytes(base + 0x4CDD8, {0x76});
        }
    }

    static void no_wave_trail(bool active)
    {
        if(active)
            writeBytes(base + 0x221C29, {0xE9, 0xA7, 0x08, 0x00, 0x00, 0x90});
        else
            writeBytes(base + 0x221C29, {0xF, 0x84, 0xA6, 0x08, 0x00, 0x00});
    }

    static void buy_item_bypass(bool active) // idk what name
    {
        if (active) 
        {
            writeBytes(base + 0x216670, { 0x90, 0x90 });
            writeBytes(base + 0x216666, { 0xEB });
            writeBytes(base + 0x218AF4, { 0x90, 0x90 });
            writeBytes(base + 0x216670, { 0x90, 0x90 });
        }
        else
        {
            writeBytes(base + 0x216670, { 0xEB });
            writeBytes(base + 0x216666, { 0x74 });
            writeBytes(base + 0x218AF4, { 0x74, 0x14 });
            writeBytes(base + 0x216670, { 0xEB, 0x1D });
        }
    }

    static void scratch_bypass(bool active)
    {
        if (active)
            writeBytes(base + 0x2F70EA, { 0xEB });
        else
            writeBytes(base + 0x2F70EA, { 0x75 });
    }

    static void potbor_bypass(bool active)
    {
        if (active)
            writeBytes(base + 0x2F710E, { 0x74 });
        else
            writeBytes(base + 0x2F710E, { 0x75 });
    }

    static void the_mechanic_bypass(bool active)
    {
        if (active)
            writeBytes(base + 0x2F7132, { 0x74 });
        else
            writeBytes(base + 0x2F7132, { 0x75 });
    }

    static void diamond_shopkeeper(bool active)
    {
        if (active)
            writeBytes(base + 0x2F7156, { 0x74 });
        else
            writeBytes(base + 0x2F7156, { 0x75 });
    }
} // namespace name
