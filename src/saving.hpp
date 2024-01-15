#pragma once

#include "bools.hpp"
#include "hacks.hpp"
#include <fstream>

extern struct settings hacks_;

namespace saving
{
    void Save() {
        std::ofstream f;
        f.open("gd-hacks/hacks.bin", std::fstream::binary);
        if (f) {
            f.write(reinterpret_cast<char*>(&hacks_), sizeof(settings));
            f.close();
        }
    }

    void Load() {
        std::ifstream f;
        f.open("gd-hacks/hacks.bin", std::fstream::binary);
        if (f) {
            f.read(reinterpret_cast<char*>(&hacks_), sizeof(settings));
            f.close();
            hacks::copy_hack(hacks_.copy_hack);
            hacks::layout_mode(hacks_.show_layout);
            hacks::no_shaders(hacks_.no_shaders);
            hacks::no_transition(hacks_.no_transition);
            hacks::noclip(hacks_.noclip);
            hacks::text_bypass(hacks_.text_bypass);
            hacks::unlock_all(hacks_.unlock_all);
            hacks::custom_object_bypass(hacks_.custom_object_bypass);
            hacks::verify_hack(hacks_.verify_hack);
            hacks::treasure_room_bypass(hacks_.treasure_room_bypass);
            hacks::scratch_bypass(hacks_.scratch_bypass);
            hacks::potbor_bypass(hacks_.potbor_bypass);
            hacks::the_mechanic_bypass(hacks_.the_mechanic_bypass);
            hacks::diamond_shopkeeper_bypass(hacks_.diamond_shopkeeper_bypass);
        }
    }
} // namespace saving