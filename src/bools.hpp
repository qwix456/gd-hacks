#pragma once

struct settings
{
    // level
    bool show_layout;
    bool startpos_switcher;
    bool alt_keys;
    float speed = 1.0f;

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
    bool treasure_room_bypass;
    bool scratch_bypass;
    bool potbor_bypass;
    bool the_mechanic_bypass;
    bool diamond_shopkeeper_bypass;
};