#include "hooks.hpp"
#include "other/bot.hpp"
#include "gui.hpp"

extern struct settings hacks_;

namespace hooks {
    void __fastcall CCScheduler_update_H(CCScheduler *self, int, float dt) {
        if (!hacks_.fps_bypass)
            return CCScheduler_update(self, dt);

        if (hacks_.speedhack)
            dt *= hacks_.speed;
        
        const float newdt = 1.f / hacks_.fps / self->getTimeScale();
        disable_render = true;

        const int times = min(static_cast<int>((dt + left_over) / newdt), 100);
        for (int i = 0; i < times; ++i) {
            if (i == times - 1)
                disable_render = false;
            CCScheduler_update(self, newdt);
        }
        left_over += dt - newdt * times;
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

    void __fastcall GameObject_setGlowOpacity_H(GameObject *self, int, unsigned char opacity)
    {
        if (hacks_.show_layout) {
            GameObject_setGlowOpacity(self, 0);
            return;
        }

        GameObject_setGlowOpacity(self, opacity);
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
        int lastCheckpointFrame = (bot::checkpoints.empty()) ? 0 : bot::checkpoints.back().frame;

        if (bot::m_mode == 2) {
            GJBaseGameLayer_handleButton(self, 0, 0, true);
            GJBaseGameLayer_handleButton(self, 0, 0, false);
        }

        if (hacks_.discord_rpc) {
            bool isRated = self->m_level()->m_stars() != 0;
            bool isRobTopLvl = self->m_level()->m_levelID() < 5004 && self->m_level()->m_levelID() > 0;
            bool isPlatformerLvl = self->m_level()->isPlatformer();

            if (self->m_level()->m_levelType() != 2) {
                state = std::string(self->m_level()->m_levelName().c_str()) + " by " + ((isRobTopLvl) ? "RobTop" : std::string(self->m_level()->m_levelAuthor().c_str()) + " (" + std::to_string(self->m_level()->m_normal()) + "%)");
            }

            rich::updateDiscordRP(
                (isPlatformerLvl) ? "Playing Platformer Level" : "Playing Level",
                state,
                getAssetKey(self->m_level()),
                (isRated) ? "Rated" : "Not Rated",
                true
            );
        }

        if (bot::checkpoints.size() != 0 && bot::replay.size() != 0) {
            if (hacks_.checkpoint_fix) {
                self->m_pPlayer1()->setPositionX(bot::checkpoints.back().P1.xpos);
                self->m_pPlayer2()->setPositionX(bot::checkpoints.back().P2.xpos);
                self->m_pPlayer1()->setPositionY(bot::checkpoints.back().P1.ypos);
                self->m_pPlayer2()->setPositionY(bot::checkpoints.back().P2.ypos);
                self->m_pPlayer1()->setRotation(bot::checkpoints.back().P1.rotation);
                self->m_pPlayer2()->setRotation(bot::checkpoints.back().P2.rotation);
                self->m_pPlayer1()->Setm_yAccel(bot::checkpoints.back().P1.yAccel);
                self->m_pPlayer2()->Setm_yAccel(bot::checkpoints.back().P2.yAccel);
                self->m_pPlayer1()->Setm_xAccel(bot::checkpoints.back().P1.xAccel);
                self->m_pPlayer2()->Setm_xAccel(bot::checkpoints.back().P2.xAccel);
                self->m_pPlayer1()->Setm_isHolding(bot::checkpoints.back().P1.isHolding);
                self->m_pPlayer2()->Setm_isHolding(bot::checkpoints.back().P2.isHolding);
                self->m_pPlayer1()->Setm_isSliding(bot::checkpoints.back().P1.isSliding);
                self->m_pPlayer2()->Setm_isSliding(bot::checkpoints.back().P2.isSliding);
                self->m_pPlayer1()->Setm_playerSpeed(bot::checkpoints.back().P1.playerSpeed);
                self->m_pPlayer2()->Setm_playerSpeed(bot::checkpoints.back().P2.playerSpeed);

                if (bot::checkpoints.back().P1.buttonPushed) {
                    GJBaseGameLayer_handleButton(self, 0, 0, true);
                }
                if (bot::checkpoints.back().P2.buttonPushed) {
                    GJBaseGameLayer_handleButton(self, 0, 0, false);
                }
            }
        }

        while (!bot::replay.empty() && bot::replay.back().frame > lastCheckpointFrame) {
            bot::replay.pop_back();
        }
        
        PlayLayer_resetLevel(self);
    }

    void __fastcall GJBaseGameLayer_init_H(PlayLayer *self, void *unk) {
        pl = self;
        startPosObjects = {};
        startPosIndex = 0;
        bot::checkpoints.clear();
        
        GJBaseGameLayer_init(self);
    }

    bool __fastcall MenuLayer_init_H(MenuLayer* self, void* unk) {
        if (hacks_.discord_rpc) {
            rich::initDiscordRP();
            rich::updateDiscordRP("Browsing Menus");
        }

        return MenuLayer_init(self);
    }

    bool __fastcall CreatorLayer_init_H(CreatorLayer* self, void* unk) {
        if (hacks_.discord_rpc) {
            rich::updateDiscordRP("Browsing Menus", "Creator Tab");
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
                (isRated) ? "Rated" : "Not Rated", true);
        }

        return LevelInfoLayer_init(self, m_level, unk);
    }

    bool __fastcall GJBaseGameLayer_handleButton_H(PlayLayer *self, uintptr_t, int push, int button, BOOL is_player1)
    {
        if (bot::m_mode == 1 && bot::get_frame(self) != 0 && push) {
            if (is_player1) {
                bot::p1ButtonPushed = true;
            } else {
                bot::p2ButtonPushed = true;
            }
            bot::Click click;
            click.frame = bot::get_frame(self);
            click.action = true;
            click.push = push;
            click.button = button;
            click.fps = hacks_.fps;
            click.xpos = self->m_pPlayer1()->getPositionX();
            click.player = is_player1;
            bot::replay.push_back(click);
        }
        if (bot::m_mode == 1 && bot::get_frame(self) != 0 && !push) {
            if (is_player1) {
                bot::p1ButtonPushed = false;
            } else {
                bot::p2ButtonPushed = false;
            }
            bot::Click click;
            click.frame = bot::get_frame(self);
            click.action = false;
            click.push = push;
            click.button = button;
            click.fps = hacks_.fps;
            click.xpos = self->m_pPlayer1()->getPositionX();
            click.player = is_player1;
            bot::replay.push_back(click);
        }

        if (hacks_.ignore_user_input && bot::m_mode == 2)
            return false;

        return GJBaseGameLayer_handleButton(self, push, button, is_player1);
    }

    bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer *self, void *, GJGameLevel *level, bool unk)
    {
        if (hacks_.discord_rpc) {
            rich::updateDiscordRP(
                "Editing Level", 
                std::string(level->m_levelName().c_str()) + " by " + std::string(level->m_levelAuthor().c_str()), "", "", true);
        }
        return LevelEditorLayer_init(self, level, unk);
    }

    bool __fastcall PlayLayer_init_H(PlayLayer *self, int edx, GJGameLevel *m_level, bool unk, bool unk_2)
    {
        return PlayLayer_init(self, m_level, unk, unk_2);
    }

    bool __fastcall LevelSelectLayer_init_H(void *self, void* unk, int lvl)
    {
        if (hacks_.discord_rpc) {
            rich::updateDiscordRP("Browsing Menus", "Select RobTop Levels");
        }
        return LevelSelectLayer_init(self, lvl);
    }

    void __fastcall StartPosObject_init_H(void *self, void *unk)
    {
        startPosObjects.push_back((float*)self);
        startPosIndex = startPosObjects.size() - 1;
        StartPosObject_init(self);
    }

    void __fastcall GJBaseGameLayer_update_H(PlayLayer *self, int edx, float dt) {
        if (hacks_.show_layout)
            self->m_background()->setColor({40, 125, 255});
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

        if (self->m_hasComplete()) {
            rich::updateDiscordRP("Level " + std::string(self->m_level()->m_levelName().c_str()) + " Complete ", "Attempts: " + std::to_string(self->m_attempts()) + " Jumps: " + std::to_string(self->m_jumps()), "", "", true);
        }

        if (bot::m_mode == 2 && !bot::replay.empty()) {
            for (size_t i = 0; i < bot::replay.size(); i++) {
                 if (bot::replay[i].frame == bot::get_frame(self)) {
                    GJBaseGameLayer_handleButton(self, bot::replay[i].push, bot::replay[i].button, bot::replay[i].player);
                }
            }
        }

        GJBaseGameLayer_update(self, dt);

        if (hacks_.show_layout)
            self->m_background()->setColor({40, 125, 255});
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

    void __fastcall PlayLayer_onQuit_H(PlayLayer *self)
    {
        bot::m_frame = 0;
        bot::replay.clear();
        bot::checkpoints.clear();
        PlayLayer_onQuit(self);
    }

    void __fastcall PlayLayer_createCheckpoint_H(PlayLayer *self)
    {
        bot::Checkpoint checkpoint;
        checkpoint.frame = bot::get_frame(self);
        if (hacks_.checkpoint_fix) {
            checkpoint.P1.xpos = self->m_pPlayer1()->getPositionX();
            checkpoint.P2.xpos = self->m_pPlayer2()->getPositionX();
            checkpoint.P1.ypos = self->m_pPlayer1()->getPositionY();
            checkpoint.P2.ypos = self->m_pPlayer2()->getPositionY();
            checkpoint.P1.buttonPushed = bot::p1ButtonPushed;
            checkpoint.P2.buttonPushed = bot::p2ButtonPushed;
            checkpoint.P1.isHolding = self->m_pPlayer1()->m_isHolding();
            checkpoint.P2.isHolding = self->m_pPlayer2()->m_isHolding();
            checkpoint.P1.isSliding = self->m_pPlayer1()->m_isSliding();
            checkpoint.P2.isSliding = self->m_pPlayer2()->m_isSliding();
            checkpoint.P1.playerSpeed = self->m_pPlayer1()->m_playerSpeed();
            checkpoint.P2.playerSpeed = self->m_pPlayer2()->m_playerSpeed();
            checkpoint.P1.yAccel = self->m_pPlayer1()->m_yAccel();
            checkpoint.P2.yAccel = self->m_pPlayer2()->m_yAccel();
            checkpoint.P1.xAccel = self->m_pPlayer1()->m_xAccel();
            checkpoint.P2.xAccel = self->m_pPlayer2()->m_xAccel();
        }

        bot::checkpoints.push_back(checkpoint);
        PlayLayer_createCheckpoint(self);
    }

    void __fastcall PlayLayer_removeCheckpoint_H(PlayLayer *self, void *, bool unk)
    {
        if (bot::checkpoints.size() > 0) {
            bot::checkpoints.pop_back();
        }
        PlayLayer_removeCheckpoint(self, unk);
    }

    void setFPS()
    {
        interval = 1.0f / hacks_.fps;
        target_fps = hacks_.fps;
    }

    void init()
    {
        MH_CreateHook((void*)(base + 0x27B450), MenuLayer_init_H, (void**)&MenuLayer_init);
        MH_CreateHook((void*)(base + 0x6F550), CreatorLayer_init_H, (void**)&CreatorLayer_init);
        MH_CreateHook((void*)(base + 0x2516A0), LevelInfoLayer_init_H, (void**)&LevelInfoLayer_init);
        MH_CreateHook((void*)(base + 0x13B890), GameObject_setVisible_H, (void**)&GameObject_setVisible);
        MH_CreateHook((void*)(base + 0x13B490), GameObject_setOpacity_H, (void**)&GameObject_setOpacity);
        MH_CreateHook((void*)(base + 0x2E2BF0), PlayLayer_updateVisibility_H, (void**)&PlayLayer_updateVisibility);
        MH_CreateHook((void*)(base + 0x3A7910), StartPosObject_init_H, (void**)&StartPosObject_init);
        MH_CreateHook((void*)(base + 0x190290), GJBaseGameLayer_init_H, (void**)&GJBaseGameLayer_init);
        MH_CreateHook((void*)(base + 0x1BB780), GJBaseGameLayer_update_H, (void**)&GJBaseGameLayer_update);
        MH_CreateHook((void*)(base + 0x2EA130), PlayLayer_resetLevel_H, (void**)&PlayLayer_resetLevel);
        MH_CreateHook((void*)(base + 0x2DB810), PlayLayer_destructor_H, (void**)&PlayLayer_destructor);
        MH_CreateHook((void*)(base + 0x1415F0), GameObject_setGlowColor_H, (void**)&GameObject_setGlowColor);
        MH_CreateHook((void*)(base + 0x141300), GameObject_setObjectColor_H, (void**)&GameObject_setObjectColor);
        MH_CreateHook((void*)(base + 0x194490), GJBaseGameLayer_updateLevelColors_H, (void**)&GJBaseGameLayer_updateLevelColors);
        MH_CreateHook((void*)(base + 0x267D00), LevelSelectLayer_init_H, (void**)&LevelSelectLayer_init);
        MH_CreateHook((void*)(base + 0x1B69F0), GJBaseGameLayer_handleButton_H, (void**)&GJBaseGameLayer_handleButton);
        MH_CreateHook((void*)(base + 0x2EB480), PlayLayer_onQuit_H, (void**)&PlayLayer_onQuit);
        MH_CreateHook((void*)(base + 0x2E76E0), PlayLayer_createCheckpoint_H, (void**)&PlayLayer_createCheckpoint);
        MH_CreateHook((void*)(base + 0x2E8D70), PlayLayer_removeCheckpoint_H, (void**)&PlayLayer_removeCheckpoint);
        MH_CreateHook((void*)(base + 0x239A70), LevelEditorLayer_init_H, (void**)&LevelEditorLayer_init);
        MH_CreateHook((void*)(base + 0x2DC4A0), PlayLayer_init_H, (void**)&PlayLayer_init);
        GJBaseGameLayer_setStartPosObject = (decltype(GJBaseGameLayer_setStartPosObject))(base + 0x199E90);
        MH_CreateHook((void*)(GetProcAddress((HMODULE)(cocos_base), "?update@CCScheduler@cocos2d@@UAEXM@Z")), CCScheduler_update_H, (void**)(&CCScheduler_update));
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