#pragma once

#include "includes.hpp"

static const auto base = (uintptr_t)(GetModuleHandleA(0));

template <class R, class T>
R& from(T base, intptr_t offset) {
	return *reinterpret_cast<R*>(reinterpret_cast<uintptr_t>(base) + offset);
}

class GameObject : public cocos2d::CCSprite
{
public:
};

class PlayerObject : public cocos2d::CCSprite
{
public:
    auto m_gravity() {
        return from<float>(this, 0x934);
    }
};

class GJGameLevel : public cocos2d::CCNode
{
public:
    auto m_levelID1() {
        return from<int>(this, 0x10c);
    }

    auto m_levelID2() {
        return from<int>(this, 0x110);
    }

    auto m_totalAtt1() {
        return from<int>(this, 0x268);
    }

    auto m_totalAtt2() {
        return from<int>(this, 0x26c);
    }

    auto m_totalJumps1() {
        return from<int>(this, 0x274);
    }

    auto m_totalJumps2() {
        return from<int>(this, 0x278);
    }

    auto m_totalObjects1() {
        return from<int>(this, 0x224);
    }

    auto m_totalObjects2() {
        return from<int>(this, 0x228);
    }

    auto m_totalObjects() {
        return m_totalObjects1() - m_totalObjects2();
    }

    auto m_totalJumps() {
        return m_totalJumps1() - m_totalJumps2();
    }

    auto m_totalAtt() {
        return m_totalAtt1() - m_totalAtt2();
    }

    auto m_levelID() {
        return m_levelID1() - m_levelID2();
    }

    auto m_practiceP() {
        return from<int>(this, 0x2C4);
    }

    auto m_normal1() {
        return from<int>(this, 0x2A8);
    }

    auto m_normal2() {
        return from<int>(this, 0x2A4);
    }

    auto m_normal() {
        return m_normal1() - m_normal2();
    }
};

class PlayLayer : public cocos2d::CCLayer
{
public:
    auto typeTrigger() {
        return from<int>(this, 0x384);
    }

    auto m_pPlayer1() {
        return from<PlayerObject*>(this, 0x878);
    }

    auto m_pPlayer2() {
        return from<PlayerObject*>(this, 0x87C);
    }

    auto m_level() {
        return from<GJGameLevel*>(this, 0x5E0);
    }

    auto m_time() {
        return from<double>(this, 0x2EF0);
    }

    auto m_dualMode() {
        return from<bool>(this, 0x36E);
    }

    auto m_idk() {
        return from<double>(this, 0x330);
    }

    // auto m_ground() {
    //     return from<CCSprite*>(this, 0x9D0);
    // }
};

class FLAlertLayerProtocol
{
public:

};

class FLAlertLayer : public cocos2d::CCLayerColor
{
public:
    static FLAlertLayer* create(FLAlertLayerProtocol* target, const char* idk, std::string caption, const char* idk2, const char* idk3) {
        auto pRet = reinterpret_cast<FLAlertLayer* (__fastcall*)(FLAlertLayerProtocol*, const char*, std::string, const char*, const char*)>(
            base + 0x30DA0
        )(target, idk, caption, idk2, idk3);
        __asm add esp, 0x20
        return pRet;
    }

    virtual void show() {
        return reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
            base + 0x31CD0
        )(this);
    }
};

class GameManager
{
public:
    auto m_pPlayLayer() {
        return from<PlayLayer*>(this, 0x198);
    }

    static GameManager* sharedState() {
        return reinterpret_cast<GameManager* (__stdcall*)()>(
            base + 0x121540
        )();
    }

    bool getGameVariable(const char* key) {
		return reinterpret_cast<bool(__thiscall*)(GameManager*, const char*)>(
			base + 0x128730
		)(this, key);
	}
	void setGameVariable(const char* key, bool value) {
		return reinterpret_cast<void(__thiscall*)(GameManager*, const char*, bool)>(
			base + 0x1284E0
		)(this, key, value);
	}
};