#pragma once

#include <vector>
#include <string>
#include "utils.hpp"
#include "gd.hpp"
#include <map>

using namespace utils;

namespace hacks
{
    static void layout_mode(bool active)
    {
        if (active) {
            WriteBytes(base + 0x13EFA1, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x13EFA1, {0x88, 0x87, 0x62, 0x04, 0x00, 0x00});
        }
    }

    static void ignore_esc(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2BA31E, {0xEB});
            WriteBytes(base + 0x2BA26F, {0xE9, 0x84, 0x00, 0x00, 0x00});
        }
        else {
            WriteBytes(base + 0x2BA31E, {0x7F});
            WriteBytes(base + 0x2BA26F, {0x74, 0x1D, 0xC6, 0x86, 0xB9});
        }
    }
    
    static void noclip(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2E6779, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xC6, 0x83, 0x88, 0x2D, 0x00, 0x00, 0x01, 0xE9, 0x8F, 0x07, 0x00, 0x00});
        }
        else {
            WriteBytes(base + 0x2E6779, {0x0F, 0x85, 0x9B, 0x07, 0x00, 0x00, 0x38, 0x83, 0xC2, 0x2A, 0x00, 0x00, 0x0F, 0x85, 0x8F, 0x07, 0x00, 0x00});
        }
    }

    static void unlock_all(bool active)
    {
        if (active) {
            WriteBytes(base + 0x1224BB, {0xEB, 0x77});
            WriteBytes(base + 0x121FBB, {0xE9, 0xA5, 0x00, 0x00, 0x00});
        }
        else {
            WriteBytes(base + 0x1224BB, {0x8B, 0xD9});
            WriteBytes(base + 0x121FBB, {0x8B, 0xD9, 0x8B, 0x7D, 0x0C});
        }
    }

    static void unlock_all_levels(bool active)
    {
        if (active) {
            WriteBytes(base + 0x26C113, {0xEB});
        }
        else {
            WriteBytes(base + 0x26C113, {0x7E});
        }
    }

    static void no_transition(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xA93DF, {0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(cocos_base + 0xA93DF, {0xF3, 0x0F, 0x11, 0x04, 0x24});
        }
    }

    static void no_shaders(bool active)
    {
        if (active) {
            WriteBytes(base + 0x3836DD, {0xE9, 0x27, 0x01, 0x00});
        }
        else {
            WriteBytes(base + 0x3836DD, {0x0F, 0x8B, 0x26, 0x01, 0x00});
        }
    }

    static void no_death_effect(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2D1C12, {0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x2D1C12, {0xE8, 0x59, 0x88, 0xFE, 0xFF});
        }
    }

    static void no_trail(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xB1010, {0x0F, 0x85});
        }
        else {
            WriteBytes(cocos_base + 0xB1010, {0x0F, 0x84});
        }
    }

    static void trail_always_off(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xB11DC, {0xE9, 0x69, 0x02, 0x00, 0x00, 0x90});
        }
        else {
            WriteBytes(cocos_base + 0xB11DC, {0x0F, 0x84, 0x68, 0x02, 0x00, 0x00});
        }
    }

    static void trail_always_on(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xB11DC, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(cocos_base + 0xB11DC, {0x0F, 0x84, 0x68, 0x02, 0x00, 0x00});
        }
    }

    static void no_wave_trail(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2D8A0E, {0x0F, 0x84});
        }
        else {
            WriteBytes(base + 0x2D8A0E, {0x0F, 0x85});
        }
    }

    static void no_camera_move(bool active)
    {
        if (active) {
            WriteBytes(base + 0x3B2B40, {0xC2, 0x0C, 0x00});
        }
        else {
            WriteBytes(base + 0x3B2B40, {0x55, 0x8B, 0xEC});
        }
    }

    static void no_camera_zoom(bool active)
    {
        if (active) {
            WriteBytes(base + 0x39DBE4, {0xEB, 0x44, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x39DBE4, {0xFF, 0xB7, 0xE0, 0x05, 0x00, 0x00});
        }
    }

    static void no_particles(bool active)
    {
        if (active) {
            WriteBytes(cocos_base + 0xBD52A, {0x0F, 0x85});
        }
        else {
            WriteBytes(cocos_base + 0xBD52A, {0x0F, 0x84});
        }
    }

    static void no_mirror(bool active)
    {
        if (active) {
            WriteBytes(base + 0x1C87F1, {0x0F, 0x85});
        }
        else {
            WriteBytes(base + 0x1C87F1, {0x0F, 0x84});
        }
    }

    static void copy_hack(bool active)
    {
        if (active) {
            WriteBytes(base + 0x25292E, {0xE9, 0x37, 0x01, 0x00});
        }
        else {
            WriteBytes(base + 0x25292E, {0x0F, 0x84, 0x36, 0x01, 0x00});
        }
    }

    static void custom_object_bypass(bool active)
    {
        if (active) {
            WriteBytes(base + 0xA8214, {0xE9, 0x83, 0x00});
            WriteBytes(base + 0xA83C4, {0x90, 0x90});
        }
        else {
            WriteBytes(base + 0xA8214, {0x0F, 0x86, 0x82});
            WriteBytes(base + 0xA83C4, {0x77, 0x3A});
        }
    }

    static void no_c_mark(bool active)
    {
        if (active) {
            WriteBytes(base + 0xFBAE0, {0x6A, 0x00, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            WriteBytes(base + 0xFBAE0, {0xFF, 0xB5, 0x94, 0xFE, 0xFF, 0xFF});
        }
    }

    static void verify_hack(bool active)
    {
        if (active) {
            WriteBytes(base + 0x80C77, {0xBA, 0xE8});
            WriteBytes(base + 0x9E038, {0x74});
            WriteBytes(base + 0x388F8E, {0xEB});
        }
        else {
            WriteBytes(base + 0x80C77, {0xBA, 0xF4});
            WriteBytes(base + 0x9E038, {0x75});
            WriteBytes(base + 0x388F8E, {0x75});
        }
    }

    static void text_bypass(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2F9A7, {0xEB});
        }
        else {
            WriteBytes(base + 0x2F9A7, {0x7C});
        }
    }

    static void treasure_room_bypass(bool active)
    {
        if (active) {
            WriteBytes(base + 0x700FB, {0x90, 0x90, 0x90});
            WriteBytes(base + 0x71175, {0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x700FB, {0x0F, 0x44, 0xCA});
            WriteBytes(base + 0x71175, {0x74, 0x4C});
        }
    }

    static void chamber_of_time(bool active)
    {
        if (active) {
            WriteBytes(base + 0x26BC77, {0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x26BC77, {0x74, 0x61});
        }
    }

    static void unlock_shops(bool active)
    {
        if (active) {
            WriteBytes(base + 0x2FE5BA, {0xEB});
            WriteBytes(base + 0x2FE5DE, {0xEB});
            WriteBytes(base + 0x2FE602, {0xEB});
            WriteBytes(base + 0x2FE626, {0xEB});
        }
        else {
            WriteBytes(base + 0x2FE5BA, {0x75});
            WriteBytes(base + 0x2FE5DE, {0x75});
            WriteBytes(base + 0x2FE602, {0x75});
            WriteBytes(base + 0x2FE626, {0x75});
        }
    }

    static void vault_of_secrets(bool active)
    {
        if (active) {
            WriteBytes(base + 0x6FEB4, {0x90, 0x90, 0x90});
            WriteBytes(base + 0x6FF41, {0x0F, 0x84});
            WriteBytes(base + 0x70E51, {0x90, 0x90});
            WriteBytes(base + 0x306E7C, {0x90, 0x90});
            WriteBytes(base + 0x30C39F, {0x0F, 0x84});
            WriteBytes(base + 0x30C547, {0x0F, 0x84});
            WriteBytes(base + 0x30C6F3, {0x0F, 0x84});
        }
        else {
            WriteBytes(base + 0x6FEB4, {0x0F, 0x44, 0xC2});
            WriteBytes(base + 0x6FF41, {0x0F, 0x85});
            WriteBytes(base + 0x70E51, {0x74, 0x4A});
            WriteBytes(base + 0x306E7C, {0x74, 0x4A});
            WriteBytes(base + 0x30C39F, {0x0F, 0x85});
            WriteBytes(base + 0x30C547, {0x0F, 0x85});
            WriteBytes(base + 0x30C6F3, {0x0F, 0x85});
        }
    }

    static void free_shops(bool active)
    {
        if (active) {
            WriteBytes(base + 0x21B3A6, {0xEB});
            WriteBytes(base + 0x16A199, {0x90, 0x90});
            WriteBytes(base + 0x16A195, {0x90, 0x90});
        }
        else {
            WriteBytes(base + 0x21B3A6, {0x74});
            WriteBytes(base + 0x16A199, {0xEB, 0x7B});
            WriteBytes(base + 0x16A195, {0x7D, 0x04});
        }
    }

    static void slider_limit(bool active)
    {
        if (active) {
            WriteBytes(base + 0x4D04A, {0xEB});
            WriteBytes(base + 0x4D078, {0xEB});
            WriteBytes(base + 0xDF1E8, {0xEB});
        }
        else {
            WriteBytes(base + 0x4D04A, {0x76});
            WriteBytes(base + 0x4D078, {0x76});
            WriteBytes(base + 0xDF1E8, {0x75});
        }
    }
} // namespace name