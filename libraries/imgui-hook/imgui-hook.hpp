#include <Windows.h>
#include <gl/GL.h>
#include <functional>
#include <imgui.h>

typedef BOOL(WINAPI* SwapBuffersType)(HDC hdc);

namespace ImGuiHook {
    void Load(std::function<void(void*, void*, void**)> hookFunc);
    void Unload();
    void setRenderFunction(std::function<void()> func);
    void setToggleFunction(std::function<void()> func);
}