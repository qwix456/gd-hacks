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
        if (f)
            f.write((char*)&hacks_, sizeof(settings));
        f.close();
    }

    void Load() {
        std::ifstream f;
        f.open("gd-hacks/hacks.bin", std::fstream::binary);
        if (f) {
            f.read((char*)&hacks_, sizeof(settings));
            hacks::copy_hack(hacks_.copy_hack);
            hacks::layout_mode(hacks_.show_layout);
            hacks::no_shaders(hacks_.no_shaders);
            hacks::no_transition(hacks_.no_transition);
            hacks::noclip(hacks_.noclip);
            hacks::text_bypass(hacks_.text_bypass);
            hacks::unlock_all(hacks_.unlock_all);
            hacks::custom_object_bypass(hacks_.custom_object_bypass);
            hacks::verify_hack(hacks_.verify_hack);
        }
        f.close();
    }
} // namespace saving