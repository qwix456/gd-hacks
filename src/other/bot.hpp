#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "../hacks/gd.hpp"

namespace bot
{
    struct PlayerInformation {
        float xpos;
        float ypos;
        float rotation;
        float playerSpeed;
        double yAccel;
        double xAccel;
        bool isHolding;
        bool isSliding;
        bool buttonPushed;
    };

    struct Click {
        float fps;
        int frame;
        int push;
        int button;
        float xpos;
        bool action;
        bool player;
    };

    struct Checkpoint {
        int frame;
        PlayerInformation P1;
        PlayerInformation P2;
    };

    inline int m_frame = 0;
    inline int m_mode = 0;
    inline bool p1ButtonPushed = false;
    inline bool p2ButtonPushed = false;
    inline int action_index;

    inline std::vector<Click> replay;
    inline std::vector<Checkpoint> checkpoints;

    void save_replay(std::string path);
    void load_replay(std::string path);
    int get_frame(PlayLayer* self);
};