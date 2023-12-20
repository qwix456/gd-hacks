#include "utils.hpp"
#include <list>
#include <gd.h>

namespace hooks
{
    extern int m_frame;
    extern bool m_inPractice;

    inline void(__thiscall* update)(gd::PlayLayer* self, float dt);
    void __fastcall update_H(gd::PlayLayer* self, void*, float dt);

    inline bool(__thiscall* releaseButton)(void* self, int state, bool player);
    bool __fastcall releaseButton_H(void* self, uintptr_t, int state, bool player);

    inline bool(__thiscall* pushButton)(void* self, int state, bool player);
    bool __fastcall pushButton_H(void* self, uintptr_t, int state, bool player);

    inline void(__thiscall* togglePractice)(void* self, bool practice);
    void __fastcall togglePractice_H(void* self, int edx, bool practice);
}

namespace GDBot
{
    extern std::list<float> releaseMacro;
    extern std::list<float> pushMacro;
    extern std::vector<std::pair<bool, bool>> frameMacro;
    extern std::vector<std::pair<int, float>> checkpoints;
    extern int mode;
    extern bool ignoreUserInput;
    extern bool buttonPushed;
    extern bool buttonReleased;
}