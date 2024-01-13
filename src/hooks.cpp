#include "hooks.hpp"
#include "hacks.hpp"
#include "bools.hpp"

extern struct settings hacks_;

namespace CheatHooks {
    void __fastcall CCScheduler_update_H(void *self, int, float dt) {
        dt *= hacks_.speed;
        CCScheduler_update(self, dt);
    }

    void __fastcall GameObject_setVisible_H(uint32_t *self, int, bool visible) {
        if (hacks_.show_layout) {
            uint32_t objectID = self[0xE1];
            int objectType = MBO(int, self, 0x31c);

            if (objectType == 7) {
                GameObject_setVisible(self, false);
                return;
            } else if (objectType == 0) {
                GameObject_setVisible(self, true);
                return;
            }
        }

        GameObject_setVisible(self, visible);
    }

    void __fastcall GameObject_setOpacity_H(uint32_t *self, int, unsigned char opacity) {
        if (hacks_.show_layout) {
            uint32_t objectID = self[0xE1];
            int objectType = MBO(int, self, 0x31c);
            float objectGlow = MBO(float, self, 0x3b4);

            if (objectType == 7) {
                GameObject_setOpacity(self, 0);
                return;
            }
        }

        GameObject_setOpacity(self, opacity);
    }

    void __fastcall GameObject_setGlowColor_H(uint32_t *self, int, _ccColor3B const& color) {
        if (hacks_.show_layout) {
            GameObject_setGlowColor(self, ccc3(255, 255, 255));
            return;
        }

        GameObject_setGlowColor(self, color);
    }

    void __fastcall PlayLayer_updateVisibility_H(void *self, int, void *dt, void *unk, void *unk_2) {
        if (hacks_.show_layout) {
            int objectType = MBO(int, self, 0x384);

            if (objectType == 899 || objectType == 1006 || objectType == 1007 || objectType == 2903) {
                return;
            }
        }

        PlayLayer_updateVisibility(self, dt, unk, unk_2);
    }

    void __fastcall GameObject_setObjectColor_H(uint32_t *self, int, _ccColor3B const& color) {
        if (hacks_.show_layout) {
            int objectType = MBO(int, self, 0x31c);
            if (objectType != 7) {
                GameObject_setObjectColor(self, ccc3(255, 255, 255));
                return;
            }
        }

        GameObject_setObjectColor(self, color);
    }

    void __fastcall PlayLayer_resetLevel_H(PlayLayer *self) {
        PlayLayer_resetLevel(self);
    }

    void __fastcall GJBaseGameLayer_init_H(PlayLayer *self, void *unk) {
        pl = self;
        startPosObjects = {};
        startPosIndex = 0;

        GJBaseGameLayer_init(self);
    }

    bool __fastcall PlayLayer_init_H(PlayLayer *self, int edx, GJGameLevel *m_level, bool unk, bool unk_2) {
        return PlayLayer_init(self, m_level, unk, unk_2);
    }

    void __fastcall StartPosObject_init_H(void *self, void *unk) {
        startPosObjects.push_back((float*)self);
        startPosIndex = startPosObjects.size() - 1;
        StartPosObject_init(self);
    }

    void __fastcall GJBaseGameLayer_update_H(PlayLayer *self, int edx, float dt) {
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
