#include "hooks.hpp"

int hooks::m_frame = 0;
bool hooks::m_inPractice = false;

int GDBot::mode;
bool GDBot::ignoreUserInput;
std::list<float> GDBot::pushMacro;
std::list<float> GDBot::releaseMacro;
std::vector<std::pair<bool, bool>> GDBot::frameMacro;
bool GDBot::buttonPushed;
bool GDBot::buttonReleased;

void __fastcall hooks::update_H(gd::PlayLayer *self, void *, float dt)
{
    m_frame++;

    if (GDBot::mode == 2)
    {
        if (std::find(GDBot::pushMacro.begin(), GDBot::pushMacro.end(), m_frame) != GDBot::pushMacro.end()) {
			hooks::pushButton(self, 0, true);
		}

		if (std::find(GDBot::releaseMacro.begin(), GDBot::releaseMacro.end(), m_frame) != GDBot::releaseMacro.end()) {
			hooks::releaseButton(self, 0, true);
		}
    }

    if (m_inPractice)
    {
        while (GDBot::pushMacro.back() >= m_frame)
        {
            GDBot::pushMacro.pop_back();
        }
        while (GDBot::releaseMacro.back() >= m_frame)
        {
            GDBot::releaseMacro.pop_back();
        }
    }

    return update(self, dt);
}