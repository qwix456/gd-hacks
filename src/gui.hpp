#pragma once

#include "includes.hpp"

extern struct settings hacks_;

namespace gui
{
    static bool m_visibleGui;
    void ApplyColor();
    void RenderInfo();
    void render();
    void RenderUI();
    void ShowUI();
} // namespace gui