#pragma once

struct settings
{
    // level
    bool show_layout;
    bool startpos_switcher;
    bool alt_keys;
    float speed = 1.0f;

    // labels
    bool level_name;
    bool author;
    bool level_id;
    bool total_attempts;
    bool total_jumps;
    bool normal_percent;
    bool practice_percent;

    // player
    bool noclip;
    bool unlock_all;
    bool unlock_all_levels;
    bool no_transition;
    bool no_shaders;
    bool no_death_effect;
    bool no_trail;
    bool no_wave_trail;
    bool no_camera_move;
    bool no_camera_zoom;
    bool rainbow_icons;
    bool rainbow_color_1;
    bool rainbow_color_2;
    bool rainbow_wave_trail;
    float rainbow_speed;
    float pastel;

    // creator
    bool copy_hack;
    bool verify_hack;
    bool custom_object_bypass;

    // bypass
    bool text;
    bool treasure;
    bool scratch;
    bool potbor;
    bool the_mechanic;
    bool diamond_shopkeeper;
    bool free_shops;
    bool vault_of_secrets;

    // utils
    bool discord_rpc;
};