#pragma once

#include "../includes.hpp"

using namespace cocos2d;

static auto base = (uintptr_t)(GetModuleHandleA(0));
static auto cocos_base = (uintptr_t)(GetModuleHandleA("libcocos2d.dll"));

#define OFFSET(type, address) *(reinterpret_cast<type*>(address));

template <class R, class T>
R& from(T base, intptr_t offset) {
	return *reinterpret_cast<R*>(reinterpret_cast<uintptr_t>(base) + offset);
}

class CCSpritePlus : public CCSprite {
public:

};

class GameObject : public CCSpritePlus
{
public:
    auto m_glow() {
        return from<CCSprite*>(this, 0x2B00);
    }

    auto m_objectType() {
        return from<int>(this, 0x31c);
    }
};

class AnimatedSpriteDelegate
{
public:
};

class HardStreak : cocos2d::CCDrawNode
{
public:

};

class PlayerObject : public GameObject, public AnimatedSpriteDelegate
{
public:
    auto m_gravity() {
        return from<float>(this, 0x934);
    }

    auto m_isHolding() {
        return from<bool>(this, 0x775);
    }

    auto m_isIdk() {
        return from<float>(this, 0x874);
    }

    auto m_playerSize() {
        return from<float>(this, 0x7E0);
    }

    auto m_idk() {
        return from<bool>(this, 0x81A);
    }

    auto Setm_isHolding(bool hold) {
        return from<bool>(this, 0x775) = hold;
    }

    auto m_isSliding() {
        return from<bool>(this, 0x7FC);
    }

    auto Setm_isSliding(bool sliding) {
        return from<bool>(this, 0x7FC) = sliding;
    }

    auto m_playerSpeed() {
        return from<float>(this, 0x7E4);
    }

    auto Setm_playerSpeed(float speed) {
        return from<float>(this, 0x7E4) = speed;
    }

    auto m_yAccel() {
        return from<double>(this, 0x790);
    }

    auto m_xAccel() {
        return from<double>(this, 0x630);
    }

    auto Setm_yAccel(double accel) {
        return from<double>(this, 0x790) = accel;
    }

    auto Setm_xAccel(double accel) {
        return from<double>(this, 0x630) = accel;
    }

    auto m_position() {
        return from<CCPoint>(this, 0x64);
    }

    auto m_wave() {
        return from<CCMotionStreak*>(this, 0x620);
    }

    auto m_waveTrail() {
        return from<HardStreak*>(this, 0x628);
    }

    void setSecondColor(_ccColor3B const& color) {
        reinterpret_cast<void(__thiscall*)(PlayerObject*, _ccColor3B const&)>(base + 0x2D65A0)(this, color);
    }
};

class MenuLayer : public cocos2d::CCLayer
{
public:
};

class CreatorLayer : public cocos2d::CCLayer
{
public:
};

class LevelInfoLayer : public cocos2d::CCLayer
{
public:
};

enum GJDifficulty {
    kGJDifficultyAuto = 0,
    kGJDifficultyEasy = 1,
    kGJDifficultyNormal = 2,
    kGJDifficultyHard = 3,
    kGJDifficultyHarder = 4,
    kGJDifficultyInsane = 5,
    kGJDifficultyDemon = 6,
    kGJDifficultyDemonEasy = 7,
    kGJDifficultyDemonMedium = 8,
    kGJDifficultyDemonInsane = 9,
    kGJDifficultyDemonExtreme = 10
};

// https://github.com/TechStudent10/DiscordRPC/blob/master/src/main.cpp#L67C1-L82C1 <3
inline std::string convertGJDifficultyDemonToAssetKey(int difficulty) {
	switch (difficulty) {
		case 3:
			return "easy_demon";
		case 4:
			return "medium_demon";
		case 0:
			return "hard_demon";
		case 5:
			return "insane_demon";
		case 6:
			return "extreme_demon";
	}
	return "na";
}

// https://github.com/TechStudent10/DiscordRPC/blob/master/src/main.cpp#L83C1-L101C2 <3
inline std::string convertGJDifficultyToAssetKey(GJDifficulty difficulty) {
	switch (static_cast<int>(difficulty)) {
		case -1:
			return "auto";
		case 0:
			return "na";
		case static_cast<int>(GJDifficulty::kGJDifficultyEasy):
			return "easy";
		case static_cast<int>(GJDifficulty::kGJDifficultyNormal):
			return "normal";
		case static_cast<int>(GJDifficulty::kGJDifficultyHard):
			return "hard";
		case static_cast<int>(GJDifficulty::kGJDifficultyHarder):
			return "harder";
		case static_cast<int>(GJDifficulty::kGJDifficultyInsane):
			return "insane";
	}
	return "na";
}

// https://github.com/TechStudent10/DiscordRPC/blob/master/src/main.cpp#L103C1-L154C2 <3
inline std::string convertRobTopLevelToAssetKey(int lvlID) {
	switch (lvlID) {
		case 1:
			return "easy"; // Stereo Madness
		case 2:
			return "easy"; // Back On Track
		case 3:
			return "normal"; // Polargeist
		case 4:
			return "normal"; // Dry Out
		case 5:
			return "hard"; // Base After Base
		case 6:
			return "hard"; // Can't Let Go
		case 7:
			return "harder"; // Jumper
		case 8:
			return "harder"; // Time Machine
		case 9:
			return "harder"; // Cycles
		case 10:
			return "insane"; // xStep
		case 11:
			return "insane"; // Clutterfunk
		case 12:
			return "insane"; // Theory of Everything
		case 13:
			return "insane"; // Electroman Adventures
		case 14:
			return "hard_demon"; // Clubstep
		case 15:
			return "insane"; // Electrodynamix
		case 16:
			return "insane"; // Hexagon Force
		case 17:
			return "harder"; // Blast Processing
		case 18:
			return "hard_demon"; // TOE 2
		case 19:
			return "harder"; // Geometrical Dominator
		case 20:
			return "hard_demon"; // Deadlocked
		case 21:
			return "insane"; // Fingerdash
		case 22:
			return "insane"; // Dash
        case 5001:
            return "hard"; // The Tower
        case 5002:
            return "harder"; // The Sewers
        case 5003:
            return "harder"; // The Cellar
        case 5004:
            return "harder"; // The Secret Hollow
		case 3001:
			return "hard"; // The Challenge
	}
    return "na";
}

class GJGameLevel : public cocos2d::CCNode
{
public:
    auto m_levelAuthor() {
        return from<std::string>(this, 0x160);
    }

    auto m_lvlLength() {
        return from<int>(this, 0x2D0);
    }

    bool isPlatformer() {
        return m_lvlLength() == 5;
    }

    auto m_levelName() {
        return from<std::string>(this, 0x118);
    }

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

    auto setLead1() {
        return from<int>(this, 0x2B8) = 0;
    }

    auto setLead2() {
        return from<int>(this, 0x2BC) = 0;
    }

    auto setZeroLead() {
        return setLead1() - setLead2();
    }

    auto m_totalObjects2() {
        return from<int>(this, 0x228);
    }

    auto m_totalObjects() {
        return m_totalObjects1() - m_totalObjects2();
    }

    auto setJumps() {
        return from<int>(this, 0x274) = 0;
    }

    auto setJumps1() {
        return from<int>(this, 0x278) = 0;
    }

    auto setAttempt() {
        return from<int>(this, 0x268) = 0;
    }

    auto setAttempt1() {
        return from<int>(this, 0x26c) = 0;
    }

    auto m_totalJumps() {
        return m_totalJumps1() - m_totalJumps2();
    }

    auto setZeroJumps() {
        return setJumps() - setJumps1();
    }

    auto setZeroAtt() {
        return setAttempt() - setAttempt1();
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

    auto setNormal() {
        return from<int>(this, 0x2A8) = 0;
    }

    auto setNormal1() {
        return from<int>(this, 0x2A4) = 0;
    }

    auto setZeroNormal() {
        return setNormal() - setNormal1();
    }

    auto setPractice() {
        return from<int>(this, 0x2C4) = 0;
    }

    auto m_stars1() {
        return from<int>(this, 0x300);
    }

    auto m_stars2() {
        return from<int>(this, 0x304);
    }

    auto m_stars() {
        return m_stars1() - m_stars2();
    }

    auto m_demonDiff() {
        return from<int>(this, 0x2FC);
    }

    int m_levelType() {
        return from<int>(this, 0x218);
    }

    auto m_coins1() {
        return from<int>(this, 0x314);
    }

    auto m_coins2() {
        return from<int>(this, 0x318);
    }

    auto m_coins() {
        return m_coins1() - m_coins2();
    }

    auto m_songID() {
        return from<int>(this, 0x218);
    }

    GJDifficulty getAverageDifficulty() {
        return reinterpret_cast<GJDifficulty(__thiscall*)(
            GJGameLevel*
        )>(
            base + 0x114180
        )(this);
    }

    std::string getAudioFileName() {
        std::string ret;

        reinterpret_cast<void(__thiscall*)(
            GJGameLevel*, std::string*
        )>(
            base + 0x114440
        )(
            this, &ret
        );
        return ret;
    }
};

inline std::string getAssetKey(GJGameLevel* m_level) {
    int stars = m_level->m_stars();
    GJDifficulty diff = m_level->getAverageDifficulty();
    if (stars == 0) {
        return convertGJDifficultyToAssetKey(diff);
    }
    if (stars == 10) {
        return convertGJDifficultyDemonToAssetKey(m_level->m_demonDiff());   
    }
    if (m_level->m_levelID() < 5004 && m_level->m_levelID() > 0) {
        return convertRobTopLevelToAssetKey(m_level->m_levelID());
    }

    switch (stars) {
        case 1:
            return "auto";
        case 2:
            return "easy";
        case 3:
            return "normal";
        case 4:
            return "hard";
        case 5:
            return "hard";
        case 6:
            return "harder";
        case 7:
            return "harder";
        case 8:
            return "insane";
        case 9:
            return "insane";
    }
    return "na";
}

class GameStatsManager : public cocos2d::CCNode
{
public:
    static GameStatsManager* sharedState() {
        return reinterpret_cast<GameStatsManager* (__stdcall*)()>(
            base + 0x167D90
        )();
    }

    void uncompleteLevel(GJGameLevel* lvl) {
        reinterpret_cast<void(__thiscall*)(
            GameStatsManager*, GJGameLevel*
        )>(
            base + 0x170400
        )(
            this, lvl
        );
    }
};

class PlayLayer : public cocos2d::CCLayer
{
public:
    auto m_nDrawNode() {
        return from<cocos2d::CCDrawNode*>(this, 0x2D70);
    }

    auto m_background() {
        return from<cocos2d::CCSprite*>(this, 0x9C4);
    }

    auto m_ground() {
        return from<cocos2d::CCSprite*>(this, 0x0F8);
    }

     auto m_object() {
        return from<GameObject*>(this, 0x2AEC);
    }

    auto m_isPracticeMode() {
        return from<bool>(this, 0x2A7C);
    }

    auto m_jumps() {
        return from<int>(this, 0x2EA4);
    }

    auto m_attempts() {
        return from<int>(this, 0x29AC);
    }

    auto m_isAlive() {
        return from<bool>(this, 0x2DA0);
    }

    auto m_isDead() {
        return from<bool>(this, 0x2AC0);
    }

    auto m_isDeadFalse() {
        return from<bool>(this, 0x2AC0) = false;
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

    auto m_idk1() {
        return from<int>(this, 0x238);
    }

    auto m_toggleDraw() {
        return from<bool>(this, 0x2D78);
    }

    auto m_time() {
        return from<double>(this, 0x2EF0);
    }

    auto m_dualMode() {
        return from<bool>(this, 0x36E);
    }

    auto typeTrigger() {
        return from<int>(this, 0x384);
    }

    auto m_hasComplete() {
        return from<bool>(this, 0x2C28);
    }
};

class FLAlertLayerProtocol
{
public:

};

class LevelEditorLayer : public PlayLayer
{
public:

};

class FLAlertLayer : public cocos2d::CCLayerColor
{
public:
    static FLAlertLayer* create(FLAlertLayerProtocol* target, const char* idk, std::string caption, const char* idk2, const char* idk3) {
        auto pRet = reinterpret_cast<FLAlertLayer* (__fastcall*)(FLAlertLayerProtocol*, const char*, std::string, const char*, const char*)>(
            base + 0x30c40
        )(target, idk, caption, idk2, idk3);
        return pRet;
    }

    virtual void show() {
        return reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
            base + 0x31ca0
        )(this);
    }
};

class GJAccountManager : public cocos2d::CCNode
{
public:
    static GJAccountManager* sharedState() {
        return reinterpret_cast<GJAccountManager*(__stdcall*)()>(
            base + 0x18A510
        )();
    }

    auto m_nPlayerName() {
        return from<std::string>(this, 0x10C);
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

    auto m_nPlayerName() {
        return from<std::string>(this, 0x1D0);
    }

    auto bgVolume() {
        return from<float>(this, 0x168);
    }

    auto sfxVolume() {
        return from<float>(this, 0x16C);
    }

    auto lvlTime() {
        return from<int>(this, 0x320);
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