#include "bot.hpp"
#include "../hacks/bools.hpp"
#include "../hacks/gd.hpp"
#include "../hooks.hpp"

extern struct settings hacks_;

namespace bot {
    void save_replay(std::string path)
    {
        std::ofstream out;
        out.open("gdhacks\\macros\\" + path + ".bin", std::ios::binary);
        out.write((char*)replay.data(),sizeof(Click)*replay.size());
        m_mode = 0;
    }

    void load_replay(std::string path)
    {
        std::ifstream in;
        in.open("gdhacks\\macros\\" + path + ".bin", std::ios::binary);
        size_t count = in.seekg(0, std::ios::end).tellg() / sizeof(Click);
        replay.resize(count);
        in.seekg(0);
        in.read((char*)replay.data(), sizeof(Click) * count); 
        hooks::setFPS();
        m_mode = 2;
    }

    int get_frame(PlayLayer* self)
    {
        if (self) {
            auto time = *(double*)(((char*)self) + 0x328);
            return static_cast<int>(time * hacks_.fps);
        }
        return 0;
    }
}