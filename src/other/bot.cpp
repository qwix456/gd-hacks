#include "bot.hpp"
#include "../hacks/bools.hpp"
#include "../hacks/gd.hpp"
#include "../hooks.hpp"

struct settings hacks_;

namespace bot {
    void save_replay(std::string path)
    {
        if (replay.empty()) {
            return;
        }

        std::ofstream file("gdhacks/macros/" + path + ".bin", std::ios::binary);

        file.write(reinterpret_cast<char*>(&hacks_.fps), sizeof(hacks_.fps));
        size_t replaySize = replay.size();
        file.write(reinterpret_cast<char*>(&replaySize), sizeof(replaySize));
        file.write(reinterpret_cast<char*>(replay.data()), sizeof(Click) * replaySize);

        file.close();

        m_mode = 0;
    }

    void load_replay(std::string path)
    {
        std::ifstream in("gdhacks/macros/" + path + ".bin", std::ios::binary);

        if (!in.is_open()) {
            return;
        }

        in.read(reinterpret_cast<char*>(&hacks_.fps), sizeof(hacks_.fps));
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        replay.resize(count);
        in.read(reinterpret_cast<char*>(replay.data()), sizeof(Click) * count);

        in.close();

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