#pragma once

#include "includes.hpp"
#include "hacks/hacks.hpp"

extern struct settings hacks_;

namespace gui
{
    static bool m_visibleGui;
    void ApplyColor();
    void RenderInfo();
    void RenderLevel();
    void RenderPlayer();
    void RenderCreator();
    void RenderBypass();
    void RenderUtils();
    void RenderGDBot();
    void RenderVisuals();
    void RenderUI();
    void ShowUI();
} // namespace gui