#define _CRT_SECURE_NO_WARNINGS
#include "includes.hpp"
#include "hacks/gd.hpp"
#include "hacks/hacks.hpp"
#include "hacks/bools.hpp"
#include "hacks/rich.hpp"
#include "gui.hpp"

namespace hooks
{
    inline PlayLayer* pl = nullptr;

    inline void(__thiscall* CCScheduler_update)(CCScheduler*, float);
    inline void __fastcall CCScheduler_update_H(CCScheduler* self, int, float dt);

    inline void(__thiscall* GameObject_setVisible)(GameObject*, bool);
    inline void __fastcall GameObject_setVisible_H(GameObject* self, int, bool visible);

    inline void(__thiscall* GameObject_setOpacity)(GameObject*, unsigned char);
    inline void __fastcall GameObject_setOpacity_H(GameObject* self, int, unsigned char opacity);

    inline void(__thiscall* GameObject_setGlowColor)(GameObject*, _ccColor3B const&);
    inline void __fastcall GameObject_setGlowColor_H(GameObject* self, int, _ccColor3B const& color);

    inline void(__thiscall* GameObject_setObjectColor)(GameObject*, _ccColor3B const&);
    inline void __fastcall GameObject_setObjectColor_H(GameObject* self, int, _ccColor3B const& color);

    inline void(__thiscall* PlayLayer_updateVisibility)(PlayLayer*, void*, void*, void*);
    inline void __fastcall PlayLayer_updateVisibility_H(PlayLayer* self, int, void* dt, void* unk, void* unk_2);

    inline void(__thiscall* PlayLayer_resetLevel)(PlayLayer*);
    inline void __fastcall PlayLayer_resetLevel_H(PlayLayer* self);

    inline void(__thiscall* GJBaseGameLayer_init)(PlayLayer*);
    inline void __fastcall GJBaseGameLayer_init_H(PlayLayer* self, void* unk);

    inline bool(__thiscall* PlayLayer_init)(PlayLayer*, GJGameLevel*, bool, bool);
    inline bool __fastcall PlayLayer_init_H(PlayLayer* self, int edx, GJGameLevel* m_level, bool unk, bool unk_2);

    inline void(__thiscall* StartPosObject_init)(void*);
    inline void __fastcall StartPosObject_init_H(void* self, void* unk);

    inline void(__thiscall *GJBaseGameLayer_update)(PlayLayer *self, float dt);
    inline void __fastcall GJBaseGameLayer_update_H(PlayLayer *self, int edx, float dt);

    inline void(__thiscall* PlayLayer_destructor)(PlayLayer*);
    inline void __fastcall PlayLayer_destructor_H(PlayLayer* self, void* unk);

    inline void(__thiscall* GJBaseGameLayer_updateLevelColors)(PlayLayer*);
    inline void __fastcall GJBaseGameLayer_updateLevelColors_H(PlayLayer* self, void* unk);

    inline void(__thiscall* PlayLayer_onQuit)(PlayLayer*);
    inline void __fastcall PlayLayer_onQuit_H(PlayLayer* self);

    inline void(__thiscall* PlayLayer_createCheckpoint)(PlayLayer*);
    inline void __fastcall PlayLayer_createCheckpoint_H(PlayLayer* self);

    inline void(__thiscall* PlayLayer_removeCheckpoint)(PlayLayer*, bool);
    inline void __fastcall PlayLayer_removeCheckpoint_H(PlayLayer* self, void*, bool unk);

    inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
    inline bool __fastcall MenuLayer_init_H(MenuLayer* self, void* unk);

    inline bool(__thiscall* CreatorLayer_init)(CreatorLayer*);
    inline bool __fastcall CreatorLayer_init_H(CreatorLayer* self, void* unk);

    inline bool(__thiscall* LevelInfoLayer_init)(LevelInfoLayer*, GJGameLevel*, bool);
    inline bool __fastcall LevelInfoLayer_init_H(LevelInfoLayer* self, int edx, GJGameLevel* m_level, bool unk);

    inline bool(__thiscall* LevelSelectLayer_init)(void*, int);
    inline bool __fastcall LevelSelectLayer_init_H(void* self, void* unk, int lvl);

    inline bool(__thiscall* GJBaseGameLayer_handleButton)(PlayLayer*, int, int, BOOL);
    inline bool __fastcall GJBaseGameLayer_handleButton_H(PlayLayer* self, uintptr_t, int push, int button, BOOL is_player1);

    inline int(__thiscall* PlayLayer_destroyPlayer)(PlayLayer*, PlayerObject*, GameObject*);
    inline int __fastcall PlayLayer_destroyPlayer_H(PlayLayer* self, void*, PlayerObject* player, GameObject* obj);

    inline void(__thiscall* GJBaseGameLayer_setStartPosObject)(void*, void*) = nullptr;

    void handleKeyPress(int key);
    void switchStartPos(bool dir);

    inline std::vector<float*> startPosObjects;
    inline int startPosIndex = -1;
    inline float tmp[] = {0, 0};
    inline bool altKeys = false;
    inline std::string state;
    inline float target_fps = 60.f;
    inline float interval;
    inline float left_over = 0.f;
    inline bool disable_render = false;

    void setFPS();

    void init();
    
    void console();
    void print(std::string text);
}