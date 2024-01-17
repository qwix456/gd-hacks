#include "hooks.hpp"

extern struct settings hacks_;

namespace hooks {
    void __fastcall CCScheduler_update_H(CCScheduler *self, int, float dt) {
        dt *= hacks_.speed;
        CCScheduler_update(self, dt);
    }

    void __fastcall GameObject_setVisible_H(GameObject *self, int, bool visible) {
        if (hacks_.show_layout) {
            if (self->m_objectType() == 7) {
                GameObject_setVisible(self, false);
                return;
            }
            if (self->m_objectType() == 0) {
                return;
            }
        }

        GameObject_setVisible(self, visible);
    }

    void __fastcall GameObject_setOpacity_H(GameObject *self, int, unsigned char opacity) {
        if (hacks_.show_layout) {
            if (self->m_objectType() == 7) {
                GameObject_setOpacity(self, 0);
                return;
            }
            if (self->m_objectType() == 0) {
                return;
            }
        }

        GameObject_setOpacity(self, opacity);
    }

    void __fastcall GameObject_setGlowColor_H(GameObject *self, int, _ccColor3B const& color) {
        if (hacks_.show_layout) {
            GameObject_setGlowColor(self, ccc3(255, 255, 255));
            return;
        }

        GameObject_setGlowColor(self, color);
    }

    void __fastcall PlayLayer_updateVisibility_H(PlayLayer *self, int, void *dt, void *unk, void *unk_2) {
        if (hacks_.show_layout) {
            if (self->typeTrigger() == 899 || self->typeTrigger() == 1006 || self->typeTrigger() == 1007 || self->typeTrigger() == 2903) {
                return;
            }
        }

        PlayLayer_updateVisibility(self, dt, unk, unk_2);
    }

    void __fastcall GameObject_setObjectColor_H(GameObject *self, int, _ccColor3B const& color) {
        if (hacks_.show_layout) {
            if (self->m_objectType() != 7) {
                GameObject_setObjectColor(self, ccc3(255, 255, 255));
                return;
            }
        }

        GameObject_setObjectColor(self, color);
    }

    void __fastcall PlayLayer_resetLevel_H(PlayLayer *self) {
        if (hacks_.discord_rpc) {
            bool isRated = self->m_level()->m_stars() != 0;
            bool isRobTopLvl = self->m_level()->m_levelID() < 5004 && self->m_level()->m_levelID() > 0;

            if (self->m_level()->m_levelType() != 2) {
                state = std::string(self->m_level()->m_levelName().c_str()) + " by " + ((isRobTopLvl) ? "RobTop" : std::string(self->m_level()->m_levelAuthor().c_str()) + "(" + std::to_string(self->m_level()->m_normal()) + "%)");
            }

            rich::updateDiscordRP(
                "Playing Level",
                state,
                getAssetKey(self->m_level()),
                (isRated) ? "Rated" : "Not Rated",
                true
            );
        }
        
        PlayLayer_resetLevel(self);
    }

    void __fastcall GJBaseGameLayer_init_H(PlayLayer *self, void *unk) {
        pl = self;
        startPosObjects = {};
        startPosIndex = 0;

        GJBaseGameLayer_init(self);
    }

    bool __fastcall PlayLayer_init_H(PlayLayer *self, int edx, GJGameLevel *m_level, bool unk, bool unk_2) {
        if (hacks_.discord_rpc) {
            bool isRated = m_level->m_stars() != 0;
            bool isRobTopLvl = m_level->m_levelID() < 5004 && m_level->m_levelID() > 0;

            if (m_level->m_levelType() != 2) {
                state = std::string(m_level->m_levelName().c_str()) + " by " + ((isRobTopLvl) ? "RobTop" : std::string(m_level->m_levelAuthor().c_str()) + "(" + std::to_string(m_level->m_normal()) + "%)");
            }

            rich::updateDiscordRP(
                "Playing Level",
                state,
                getAssetKey(m_level),
                (isRated) ? "Rated" : "Not Rated",
                true
            );
        }

        return PlayLayer_init(self, m_level, unk, unk_2);
    }

    bool __fastcall MenuLayer_init_H(MenuLayer* self, void* unk) {
        if (hacks_.discord_rpc) {
            rich::initDiscordRP();
            rich::updateDiscordRP("Browsing Menu");
        }
        
        return MenuLayer_init(self);
    }

    bool __fastcall CreatorLayer_init_H(CreatorLayer* self, void* unk) {
        if (hacks_.discord_rpc) {
            rich::updateDiscordRP("Browsing Menu", "Creator Tab");
        }
        return CreatorLayer_init(self);
    }

    bool __fastcall LevelInfoLayer_init_H(LevelInfoLayer *self, int edx, GJGameLevel *m_level, bool unk) {
        if (hacks_.discord_rpc) {
            bool isRated = m_level->m_stars() != 0;

            rich::updateDiscordRP(
                "Viewing Level", 
                std::string(m_level->m_levelName().c_str()) + " by " + std::string(m_level->m_levelAuthor().c_str()),
                getAssetKey(m_level),
                (isRated) ? "Rated" : "Not Rated");
        }

        return LevelInfoLayer_init(self, m_level, unk);
    }

    bool __fastcall LevelSelectLayer_init_H(void *self, void* unk, int lvl)
    {
        if (hacks_.discord_rpc) {
            rich::updateDiscordRP("Browsing Menu", "Select RobTop Levels");
        }
        return LevelSelectLayer_init(self, lvl);
    }

    void __fastcall StartPosObject_init_H(void *self, void *unk) {
        startPosObjects.push_back((float*)self);
        startPosIndex = startPosObjects.size() - 1;
        StartPosObject_init(self);
    }

    void __fastcall GJBaseGameLayer_update_H(PlayLayer *self, int edx, float dt) {
        if (hacks_.rainbow_icons) {
            float r, g, b;
            ImGui::ColorConvertHSVtoRGB(ImGui::GetTime() * hacks_.rainbow_speed, hacks_.pastel, 1, r, g, b);
            ccColor3B color = {(GLubyte)(r * 255.0f), (GLubyte)(g * 255.0f), (GLubyte)(b * 255.0f)};

            if (hacks_.rainbow_color_1) {
                self->m_pPlayer1()->setColor(color);
                self->m_pPlayer2()->setColor(color);
            }
            if (hacks_.rainbow_color_2) {
                self->m_pPlayer1()->setSecondColor(color);
                self->m_pPlayer2()->setSecondColor(color);
            }
            if (hacks_.rainbow_wave_trail) {
                reinterpret_cast<CCNodeRGBA*>(self->m_pPlayer1()->m_waveTrail())->setColor(color);
			    reinterpret_cast<CCNodeRGBA*>(self->m_pPlayer2()->m_waveTrail())->setColor(color);
            }
        }
        GJBaseGameLayer_update(self, dt);
    }

    void __fastcall PlayLayer_destructor_H(PlayLayer *self, void *unk) {
        pl = nullptr;
        PlayLayer_destructor(self);
    }

    void handleKeyPress(int key) {
        if (pl == nullptr || !hacks_.startpos_switcher)
            return;

        if (!hacks_.alt_keys && (key == VK_LEFT || key == VK_RIGHT)) {
            switchStartPos(key == VK_RIGHT);
        } else if (hacks_.alt_keys && (key == 'A' || key == 'D')) {
            switchStartPos(key == 'D');
        }
    }

    void switchStartPos(bool dir) {
        if (pl == nullptr || !hacks_.startpos_switcher || startPosObjects.empty())
            return;

        if (dir) {
            startPosIndex = startPosIndex - 1;
            if (startPosIndex < -1) {
                startPosIndex = startPosObjects.size() - 1;
            }
        } else {
            startPosIndex = startPosIndex + 1;
            if ((startPosIndex) >= (int)startPosObjects.size()) {
                startPosIndex = -1;
            }
        }

        if (startPosIndex >= 0) {
            GJBaseGameLayer_setStartPosObject(pl, startPosObjects[startPosIndex]);
        } else {
            GJBaseGameLayer_setStartPosObject(pl, nullptr);
        }

        PlayLayer_resetLevel(pl);
    }

    void __fastcall GJBaseGameLayer_updateLevelColors_H(PlayLayer* self, void* unk) {
        if (hacks_.show_layout) {
            return;
        }
        
        GJBaseGameLayer_updateLevelColors(self);
    }

    void init() {
        MH_CreateHook((void*)(hacks::base + 0x27B450), MenuLayer_init_H, (void**)&MenuLayer_init);
        MH_CreateHook((void*)(hacks::base + 0x6F550), CreatorLayer_init_H, (void**)&CreatorLayer_init);
        MH_CreateHook((void*)(hacks::base + 0x2516A0), LevelInfoLayer_init_H, (void**)&LevelInfoLayer_init);
        MH_CreateHook((void*)(hacks::base + 0x13B890), GameObject_setVisible_H, (void**)&GameObject_setVisible);
        MH_CreateHook((void*)(hacks::base + 0x13B490), GameObject_setOpacity_H, (void**)&GameObject_setOpacity);
        MH_CreateHook((void*)(hacks::base + 0x2E2BF0), PlayLayer_updateVisibility_H, (void**)&PlayLayer_updateVisibility);
        MH_CreateHook((void*)(hacks::base + 0x3A7910), StartPosObject_init_H, (void**)&StartPosObject_init);
        MH_CreateHook((void*)(hacks::base + 0x190290), GJBaseGameLayer_init_H, (void**)&GJBaseGameLayer_init);
        MH_CreateHook((void*)(hacks::base + 0x2DC4A0), PlayLayer_init_H, (void**)&PlayLayer_init);
        MH_CreateHook((void*)(hacks::base + 0x1BB780), GJBaseGameLayer_update_H, (void**)&GJBaseGameLayer_update);
        MH_CreateHook((void*)(hacks::base + 0x2EA130), PlayLayer_resetLevel_H, (void**)&PlayLayer_resetLevel);
        MH_CreateHook((void*)(hacks::base + 0x2DB810), PlayLayer_destructor_H, (void**)&PlayLayer_destructor);
        MH_CreateHook((void*)(hacks::base + 0x1415F0), GameObject_setGlowColor_H, (void**)&GameObject_setGlowColor);
        MH_CreateHook((void*)(hacks::base + 0x141300), GameObject_setObjectColor_H, (void**)&GameObject_setObjectColor);
        MH_CreateHook((void*)(hacks::base + 0x194490), GJBaseGameLayer_updateLevelColors_H, (void**)&GJBaseGameLayer_updateLevelColors);
        MH_CreateHook((void*)(hacks::base + 0x267D00), LevelSelectLayer_init_H, (void**)&LevelSelectLayer_init);
        GJBaseGameLayer_setStartPosObject = (decltype(GJBaseGameLayer_setStartPosObject))(hacks::base + 0x199E90);
        MH_CreateHook((void*)(GetProcAddress((HMODULE)(hacks::cocos_base), "?update@CCScheduler@cocos2d@@UAEXM@Z")), CCScheduler_update_H, (void**)(&CCScheduler_update));
    }

    void console() {
        AllocConsole();
    }

    void print(std::string text) {
        text += "\n";
        freopen("CONOUT$", "w", stdout);
        printf(text.c_str());
    }
}