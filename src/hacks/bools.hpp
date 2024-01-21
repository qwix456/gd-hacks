#pragma once

#include <string>

struct settings
{
    // level
    bool show_layout;
    bool startpos_switcher;
    bool alt_keys;
    bool ignore_esc;
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
    bool noclip_p1;
    bool noclip_p2;
    bool unlock_all;
    bool unlock_all_levels;
    bool no_transition;
    bool no_shaders;
    bool no_death_effect;
    bool no_trail;
    bool trail_always_off;
    bool trail_always_on;
    bool no_wave_trail;
    bool no_camera_move;
    bool no_camera_zoom;
    bool no_particles;
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
    bool no_c_mark;

    // bypass
    bool text;
    bool treasure;
    bool chamber_of_time;
    bool unlock_shops;
    bool vault_of_secrets;
    bool free_shops;
    bool slider_limit;

    // utils
    bool discord_rpc;

    // fps bypass and speedhack
    bool speedhack;
    bool fps_bypass;

    // gdbot
    char replay_name[999];
    bool checkpoint_fix;
    bool ignore_user_input;

    // recorder
    std::string videoName, videoCodec, videoBitrate, videoExtraArgs, videoExtraAudioArgs;
    int videoWidth, videoHeight, videFps;
    bool videoIncludeAudio;
};