#pragma once

struct settings
{
    // level
    bool show_layout;
    bool startpos_switcher;
    bool alt_keys;

    // labels
    bool level_id;
    bool total_attempts;
    bool total_jumps;
    bool normal_percent;
    bool practice_percent;

    // player
    bool noclip;
    bool unlock_all;
    bool no_transition;
    bool no_shaders;

    // creator
    bool copy_hack;
    bool verify_hack;
    bool custom_object_bypass;

    // bypass
    bool text_bypass;

    float speed = 1.0f;
};