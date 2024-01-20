#include "rich.hpp"
#include <ctime>

void rich::initDiscordRP()
{
    DiscordEventHandlers handlers;
    Discord_Initialize(APPLICATION_ID, &handlers, 1, "322170");
    Discord_RunCallbacks();
}

void rich::updateDiscordRP(std::string details, std::string state, std::string smallImageKey, std::string smallImageText, bool useTime) {
    DiscordRichPresence discordPresence{};
    discordPresence.details = details.c_str();
    discordPresence.state = state.c_str();
    discordPresence.largeImageKey = "gd_large";
    discordPresence.startTimestamp = std::time(0);
    discordPresence.largeImageText = GameManager::sharedState()->m_nPlayerName().c_str();
    if (smallImageKey != "") {
        discordPresence.smallImageKey = smallImageKey.c_str();
		discordPresence.smallImageText = smallImageText.c_str();
    }
    discordPresence.instance = 0;
    Discord_UpdatePresence(&discordPresence);
}