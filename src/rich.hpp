#pragma once

#include <discord_register.h>
#include <discord_rpc.h>
#include <string>

static const char* APPLICATION_ID = "1178492879627366472";

namespace rich
{
    void initDiscordRP();
    void updateDiscordRP(std::string details, std::string state = "", std::string smallImageKey = "", std::string smallImageText = "", bool useTime = false);
}