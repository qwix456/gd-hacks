#pragma once

#include <vector>
#include <string>
#include <windows.h>

static void WriteBytes(std::uintptr_t address, std::vector<uint8_t> bytes)
{
	DWORD old_prot;
	VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(reinterpret_cast<void*>(address), bytes.data(), bytes.size());
	VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), old_prot, &old_prot);
}

namespace hacks
{
    static auto base = (uintptr_t)(GetModuleHandleA(0));
    static auto cocos_base = (uintptr_t)(GetModuleHandleA("libcocos2d.dll"));

    static void layout_mode(bool active)
    {
        if (active) {
            WriteBytes(base + 0x13EFA1, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x13E180, {0x88, 0x87, 0x62, 0x04, 0x00, 0x00});
        }
    }
    
    static void noclip(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2E6779, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xC6, 0x83, 0x88, 0x2D, 0x00, 0x00, 0x01, 0xE9, 0x8F, 0x07, 0x00, 0x00});
        }
        else {
            WriteBytes(base + 0x2E6779, {0x0F, 0x85, 0x9B, 0x07, 0x00, 0x00, 0x38, 0x83, 0xC2, 0x2A, 0x00, 0x00, 0x0F, 0x85, 0x8F, 0x07, 0x00, 0x00});
        }
    }

    static void unlock_all(bool active)
    {
        if (active) {
            WriteBytes(base + 0x1224BB, {0xEB, 0x77});
            WriteBytes(base + 0x121FBB, {0xE9, 0xA5, 0x00, 0x00, 0x00});
        }
        else {
            WriteBytes(base + 0x1224BB, {0x8B, 0xD9});
            WriteBytes(base + 0x121FBB, {0x8B, 0xD9, 0x8B, 0x7D, 0x0C});
        }
    }

    static void no_transition(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xA93DF, {0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(cocos_base + 0xA93DF, {0xF3, 0x0F, 0x11, 0x04, 0x24});
        }
    }

    static void no_shaders(bool active)
    {
        if (active) {
            WriteBytes(base + 0x3836DD, {0xE9, 0x27, 0x01, 0x00});
        }
        else {
            WriteBytes(base + 0x3836DD, {0x0F, 0x8B, 0x26, 0x01, 0x00});
        }
    }

    static void copy_hack(bool active)
    {
        if (active) {
            WriteBytes(base + 0x25296C, {0x0F, 0x85});
        }
        else {
            WriteBytes(base + 0x25296C, {0x0F, 0x84});
        }
    }

    static void custom_object_bypass(bool active)
    {
        if (active) {
            WriteBytes(base + 0xA8214, {0xE9, 0x83, 0x00});
            WriteBytes(base + 0xA83C4, {0x90, 0x90});
        }
        else {
            WriteBytes(base + 0xA8214, {0x0F, 0x86, 0x82});
            WriteBytes(base + 0xA83C4, {0x77, 0x3A});
        }
    }

    static void verify_hack(bool active)
    {
        if (active) {
            WriteBytes(base + 0x80C77, {0xBA, 0xE8});
            WriteBytes(base + 0x9E038, {0x74});
            WriteBytes(base + 0x388F8E, {0xEB});
        }
        else {
            WriteBytes(base + 0x80C77, {0xBA, 0xF4});
            WriteBytes(base + 0x9E038, {0x75});
            WriteBytes(base + 0x388F8E, {0x75});
        }
    }

    static void text_bypass(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2F9A7, {0xEB});
        }
        else {
            WriteBytes(base + 0x2F9A7, {0x7C});
        }
    }
} // namespace name