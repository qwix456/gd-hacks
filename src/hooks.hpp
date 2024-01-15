#include "includes.hpp"
#include "gd.hpp"
#include <xkeycheck.h>

#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

namespace CheatHooks
{
    inline void* lvlEditor = nullptr;
    inline PlayLayer* pl = nullptr;

    inline void(__thiscall* CCScheduler_update)(void*, float);
    inline void __fastcall CCScheduler_update_H(void* self, int, float dt);

    inline void(__thiscall* GameObject_setVisible)(uint32_t*, bool);
    inline void __fastcall GameObject_setVisible_H(uint32_t* self, int, bool visible);

    inline void(__thiscall* GameObject_setOpacity)(uint32_t*, unsigned char);
    inline void __fastcall GameObject_setOpacity_H(uint32_t* self, int, unsigned char opacity);

    inline void(__thiscall* GameObject_setGlowColor)(uint32_t*, _ccColor3B const&);
    inline void __fastcall GameObject_setGlowColor_H(uint32_t* self, int, _ccColor3B const& color);

    inline void(__thiscall* GameObject_setObjectColor)(uint32_t*, _ccColor3B const&);
    inline void __fastcall GameObject_setObjectColor_H(uint32_t* self, int, _ccColor3B const& color);

    inline void(__thiscall* PlayLayer_updateVisibility)(void*, void*, void*, void*);
    inline void __fastcall PlayLayer_updateVisibility_H(void* self, int, void* dt, void* unk, void* unk_2);

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

    inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
    inline bool __fastcall MenuLayer_init_H(MenuLayer* self, void* unk);

    inline bool(__thiscall* CreatorLayer_init)(CreatorLayer*);
    inline bool __fastcall CreatorLayer_init_H(CreatorLayer* self, void* unk);

    inline bool(__thiscall* LevelInfoLayer_init)(LevelInfoLayer*, GJGameLevel*, bool);
    inline bool __fastcall LevelInfoLayer_init_H(LevelInfoLayer* self, int edx, GJGameLevel* m_level, bool unk);

    inline void(__thiscall* GJBaseGameLayer_setStartPosObject)(void*, void*) = nullptr;

    void UpdatePositions(int index);

    void handleKeyPress(int key);
    void switchStartPos(bool dir);
    void setAlternateKeys(bool alt);

    inline std::vector<float*> startPosObjects;
    inline int startPosIndex = -1;
    inline float tmp[] = {0, 0};
    inline bool altKeys = false;
    inline std::string state;

    void init();
    void console();
    void print(std::string text);
}