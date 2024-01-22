#include "hooks.hpp"
#include "gui.hpp"
#include "other/reader.hpp"
#include <filesystem>

DWORD WINAPI MainThread(LPVOID lpParam) {
    if (!std::filesystem::exists("gdhacks"))
        std::filesystem::create_directory("gdhacks");
    if (!std::filesystem::exists("gdhacks/dlls"))
        std::filesystem::create_directory("gdhacks/dlls");
    if (!std::filesystem::exists("gdhacks/macros"))
        std::filesystem::create_directory("gdhacks/macros");

    utils::LoadDll();
    if (MH_Initialize() == MH_OK) {
        L_SUCCESS("MinHook initialization successful");
        ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
            MH_CreateHook(target, hook, trampoline);
        });
        hooks::init();
        hooks::console();
        reader::load();

        ImGuiHook::setRenderFunction(gui::RenderUI);
        ImGuiHook::setInitFunction(gui::ApplyColor);
        ImGuiHook::setKeyPressHandler([](int key) {
                if (key == VK_TAB) {
                    gui::ShowUI();
                }
                hooks::handleKeyPress(key);
            });
        MH_EnableHook(MH_ALL_HOOKS);
    } else {
        L_ERROR("MinHook initialization failed");
        return 0;
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
    }

	return TRUE;
}