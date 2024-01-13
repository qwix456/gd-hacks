#ifndef IMGUI_HOOK_HPP
#define IMGUI_HOOK_HPP

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3.h>
#include <functional>
#include <cocos2d.h>

namespace ImGuiHook {
    void _stub();

    void setupHooks(std::function<void(void*, void*, void**)> hookFunc);
    void setRenderFunction(std::function<void()> func);
    void setInitFunction(std::function<void()> func);
    void setKeybind(size_t key);
    void setKeyPressHandler(std::function<void(int)> func);
} // namespace ImGuiHook

#endif // IMGUI_HOOK_HPP