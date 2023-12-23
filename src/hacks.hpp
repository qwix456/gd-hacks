#pragma once

#include <vector>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <unordered_map>

struct settings
{
    bool noclip;
    bool practice_music_hack;
    bool practice_in_platformer;
    bool unlock_all;
    bool unlock_all_levels;
    bool copy_hack;
    bool verify_hack;
    bool level_edit;
    bool no_wave_trail;
    bool slider_bypass;
    bool keymaster_bypass;
    bool vault_of_secrets_bypass;
    bool vault_of_secrets_key_bypass;
    bool buy_item_bypass;
    bool scratch_bypass;
    bool potbor_bypass;
    bool the_mechanic_bypass;
    bool diamond_shopkeeper_bypass;
    bool treasure_room_bypass;
    bool no_death_texture;
    bool no_death_parcticle;
    bool no_particles;
    bool no_transition;
    bool custom_object_bypass;
    bool testmode_bypass;
    bool ignore_esc;
    bool ignore_pause_esc;
    bool audio_speedhack;
};

static float speed = 1.0f;

static void writeBytes(std::uintptr_t address, std::vector<uint8_t> bytes)
{
    static std::unordered_map<uintptr_t, uint8_t*> values;
	if (values.find(address) == values.end()) {
		auto data = new uint8_t[bytes.size()];
		memcpy(data, reinterpret_cast<void*>(address), bytes.size());
		values[address] = data;
	}
	DWORD old_prot;
	VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(reinterpret_cast<void*>(address), bytes.data(), bytes.size());
	VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), old_prot, &old_prot);
}

static void(__thiscall* CCScheduler_update)(void*, float);
static void __fastcall CCScheduler_update_H(void* self, int, float dt)
{
    dt *= speed;
    CCScheduler_update(self, dt);
}

namespace hacks
{
    static auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    static auto cocos_base = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll"));

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

    static void practice_in_platformer(bool active)
    {
        if(active){
            writeBytes(base + 0x2B3B0C, {0x90, 0x90});
            writeBytes(base + 0x2B3AE1, {0x75});
        }
        else{
            writeBytes(base + 0x2B3B0C, {0xEB, 0x50});
            writeBytes(base + 0x2B3AE1, {0x74});
        }
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

    static void unlock_all_levels(bool active)
    {
        if(active)
            writeBytes(base + 0x2676A4, {0xEB});
        else
            writeBytes(base + 0x2676A4, {0x7E});
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
        if(active) {
            writeBytes(base + 0x381BF5, {0x75});
            writeBytes(base + 0x80617, {0xBA, 0xA8});
            writeBytes(base + 0x9D538, {0x90, 0x90});
        }
        else {
            writeBytes(base + 0x381BF5, {0x74});
            writeBytes(base + 0x80617, {0xBA, 0xB4});
            writeBytes(base + 0x9D538, {0x75, 0x11});
        }
    }

    static void level_edit(bool active)
    {
        if(active)
        {
            writeBytes(base + 0x2B3A3A, {0x0F, 0x84});
            writeBytes(base + 0x2B3A85, {0xB9, 0x80, 0x4D});
            writeBytes(base + 0x2B3A9D, {0x90, 0x90, 0x90});
            writeBytes(base + 0x2B4D9F, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
            writeBytes(base + 0x2B4E15, {0x75});
            writeBytes(base + 0x2D707D, {0xEB});
        }
        else
        {
            writeBytes(base + 0x2B3A3A, {0x0F, 0x85});
            writeBytes(base + 0x2B3A85, {0xB9, 0x90, 0x4C});
            writeBytes(base + 0x2B3A9D, {0x0F, 0x44, 0xCA});
            writeBytes(base + 0x2B4D9F, {0x0F, 0x85, 0xBD, 0x00, 0x00, 0x00});
            writeBytes(base + 0x2B4E15, {0x74});
            writeBytes(base + 0x2D707D, {0x75});
        }
    }

    static void keymaster_bypass(bool active)
    {
        if(active)
           writeBytes(base + 0x70CB5, {0x90, 0x90});
        else
           writeBytes(base + 0x70CB5, {0x74});
    }

    static void vault_of_secrets_bypass(bool active)
    {
        if (active) {
            writeBytes(base + 0x70991, { 0x75 });
            writeBytes(base + 0x2FF97C, { 0x75 });
        }
        else {
            writeBytes(base + 0x70991, { 0x74 });
            writeBytes(base + 0x2FF97C, { 0x74 });
        }
    }

    static void vault_of_secrets_key_bypass(bool active)
    {
        if (active)
        {
            writeBytes(base + 0x30515F, { 0x0F, 0x84 });
            writeBytes(base + 0x305307, { 0x0F, 0x84 });
            writeBytes(base + 0x3054B3, { 0x0F, 0x84 });
        }
        else
        {
            writeBytes(base + 0x30515F, { 0x0F, 0x85 });
            writeBytes(base + 0x305307, { 0x0F, 0x85 });
            writeBytes(base + 0x3054B3, { 0x0F, 0x85 });
        }
    }

    static void slider_bypass(bool active)
    {
        if(active) {
            writeBytes(base + 0x4CDAA, {0xEB});
            writeBytes(base + 0x4CDD8, {0xEB});
            writeBytes(base + 0xDE538, { 0xEB });
        }
        else{
            writeBytes(base + 0x4CDAA, {0x76});
            writeBytes(base + 0x4CDD8, {0x76});
            writeBytes(base + 0xDE538, { 0x75 });
        }
    }

    static void no_wave_trail(bool active)
    {
        if(active)
            writeBytes(base + 0x221C29, {0xE9, 0xA7, 0x08, 0x00, 0x00, 0x90});
        else
            writeBytes(base + 0x221C29, {0xF, 0x84, 0xA6, 0x08, 0x00, 0x00});
    }

    static void no_particles(bool active)
    {
        if(active)
            writeBytes(cocos_base + 0xBC8D9, {0x74});
        else
            writeBytes(cocos_base + 0xBC8D9, {0x75});
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

    static void no_death_texture(bool active)
    {
        if (active)
            writeBytes(base + 0x2BA6AF, { 0xE9, 0xB8, 0x02, 0x00, 0x00, 0x90 });
        else
            writeBytes(base + 0x2BA6AF, { 0x0F, 0x85, 0xB7, 0x02, 0x00, 0x00 });
    }

    static void no_death_parcticle(bool active)
    {
        if (active)
            writeBytes(base + 0x2CC3AE, { 0xEB });
        else
            writeBytes(base + 0x2CC3AE, { 0x75 });
    }

    static void no_transition(bool active)
    {
        if(active)
            writeBytes(cocos_base + 0xA907F, {0x90, 0x90, 0x90, 0x90, 0x90});
        else
            writeBytes(cocos_base + 0xA907F, {0xF3, 0x0F, 0x11, 0x04, 0x24});
    }

    static void treasure_room_bypass(bool active)
    {
        if (active)
            writeBytes(base + 0x2F742A, { 0xE9, 0x5D, 0x01, 0x00, 0x00, 0x90 });
        else
            writeBytes(base + 0x2F742A, { 0x0F, 0x8D, 0x5C, 0x01, 0x00, 0x00 });
    }

    static void ignore_esc(bool active)
    {
        if (active)
            writeBytes(base + 0x2B4FAE, { 0xEB });
        else
            writeBytes(base + 0x2B4FAE, { 0x7F });
    }

    static void ignore_pause_esc(bool active)
    {
        if (active)
            writeBytes(base + 0x2E4FDF, { 0xE9, 0x5A, 0x01, 0x00, 0x00, 0x90 });
        else
            writeBytes(base + 0x2E4FDF, { 0x0F, 0x85, 0x59, 0x01, 0x00, 0x00 });
    }

    static void custom_object_bypass(bool active)
    {
        if (active)
        {
            writeBytes(base + 0xA76A4, { 0xE9, 0x83, 0x00 });
            writeBytes(base + 0xA7854, { 0x90, 0x90 });
        }
        else
        {
            writeBytes(base + 0xA76A4, { 0x0F, 0x86, 0x82 });
            writeBytes(base + 0xA7854, { 0x77, 0x3A });
        }
    }

    static void testmode_bypass(bool active)
    {
        if(active)
            writeBytes(base + 0x2D7D75, {0x0F, 0x85});
        else
            writeBytes(base + 0x2D7D75, {0x0F, 0x84});
    }
} // namespace name
