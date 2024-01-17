#pragma once

#include "bools.hpp"
#include "hacks.hpp"
#include <fstream>

extern struct settings hacks_;

namespace saving
{
    void Save() {
        std::ofstream f;
        f.open("gdhacks/hacks.bin", std::fstream::binary);
        if (f) {
            f.write(reinterpret_cast<char*>(&hacks_), sizeof(settings));
            f.close();
        }
    }

    void Load() {
        std::ifstream f;
        f.open("gdhacks/hacks.bin", std::fstream::binary);
        if (f) {
            f.read(reinterpret_cast<char*>(&hacks_), sizeof(settings));
            f.close();
            hacks::copy_hack(hacks_.copy_hack);
            hacks::layout_mode(hacks_.show_layout);
            hacks::no_shaders(hacks_.no_shaders);
            hacks::no_transition(hacks_.no_transition);
            hacks::noclip(hacks_.noclip);
            hacks::text_bypass(hacks_.text);
            hacks::unlock_all(hacks_.unlock_all);
            hacks::custom_object_bypass(hacks_.custom_object_bypass);
            hacks::verify_hack(hacks_.verify_hack);
            hacks::treasure_room_bypass(hacks_.treasure);
            hacks::scratch_bypass(hacks_.scratch);
            hacks::potbor_bypass(hacks_.potbor);
            hacks::the_mechanic_bypass(hacks_.the_mechanic);
            hacks::diamond_shopkeeper_bypass(hacks_.diamond_shopkeeper);
            hacks::vault_of_secrets(hacks_.vault_of_secrets);
            hacks::free_shops(hacks_.free_shops);
            hacks::no_death_effect(hacks_.no_death_effect);
            hacks::unlock_all_levels(hacks_.unlock_all_levels);
            hacks::no_trail(hacks_.no_trail);
            hacks::no_wave_trail(hacks_.no_wave_trail);
            hacks::no_camera_move(hacks_.no_camera_move);
            hacks::no_camera_zoom(hacks_.no_camera_zoom);
        }
    }
} // namespace saving