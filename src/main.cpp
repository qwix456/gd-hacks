#include "hooks.hpp"
#include "config.hpp"
#include "gui.hpp"
#include <filesystem>

DWORD WINAPI MainThread(LPVOID lpParam) {
    if (!std::filesystem::exists("gdhacks"))
        std::filesystem::create_directory("gdhacks");
    if (!std::filesystem::exists("gdhacks/dlls"))
        std::filesystem::create_directory("gdhacks/dlls");
    if (!std::filesystem::exists("gdhacks/macros"))
        std::filesystem::create_directory("gdhacks/macros");

    config::load();
    LoadDll();
    ImGuiHook::setRenderFunction(gui::RenderUI);
    ImGuiHook::setInitFunction(gui::ApplyColor);
    ImGuiHook::setKeyPressHandler([](int key) {
            if (key == VK_TAB) {
                gui::ShowUI();
            }
            hooks::handleKeyPress(key);
        });
    if (MH_Initialize() == MH_OK) {
        ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
            MH_CreateHook(target, hook, trampoline);
        });
        hooks::init();
        MH_EnableHook(MH_ALL_HOOKS);
    }
    return S_OK;
}

__declspec(dllexport) void GDHACKS() {
    return;
}

DWORD WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, &MainThread, 0, 0, 0);
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        for (HMODULE module : Dlls) {
            FreeLibrary(module);
        }
        config::save();
    }

	return TRUE;
}