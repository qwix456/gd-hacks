#pragma once

#include <string>

struct settings
{
    // level
    bool show_layout;
    bool startpos_switcher;
    bool alt_keys;
    float speed = 1.0f;
    float fps = 60.0f;

    // labels
    bool labels;
    bool level_name;
    bool author;
    bool level_id;
    bool total_attempts;
    bool total_jumps;
    bool normal_percent;
    bool practice_percent;

    // player
    bool rainbow_icons;
    bool rainbow_color_1;
    bool rainbow_color_2;
    bool rainbow_wave_trail;
    float rainbow_speed;
    float pastel;

    // utils
    bool discord_rpc;

    // fps bypass and speedhack
    bool speedhack;
    bool fps_bypass;

    // gdbot
    char replay_name[999];
    bool checkpoint_fix;
    bool ignore_user_input;
};