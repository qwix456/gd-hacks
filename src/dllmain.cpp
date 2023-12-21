#include "includes.hpp"
#include "hacks.hpp"

static bool g_visible;

static struct
{
    bool noclip;
    bool practice_music_hack;
    bool unlock_all;
    bool copy_hack;
    bool verify_hack;
    //bool keymaster_bypass;
    bool slider_bypass;
} settings;

void InitUI()
{
    ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.f);
}

void RenderUI()
{
    if (g_visible)
    {
        ImGui::Begin("Hacks");
        if (ImGui::Checkbox("Noclip", &settings.noclip))
            hacks::noclip(settings.noclip);
        if (ImGui::Checkbox("Practice Music Hack", &settings.practice_music_hack))
            hacks::practice(settings.practice_music_hack);
        if (ImGui::Checkbox("Copy hack", &settings.copy_hack))
            hacks::copy_hack(settings.copy_hack);
        if (ImGui::Checkbox("Verify hack", &settings.verify_hack))
            hacks::verify_hack(settings.verify_hack);
        if (ImGui::Checkbox("Unlock all", &settings.unlock_all))
            hacks::unlock_all(settings.unlock_all);
        if (ImGui::Checkbox("Slider bypass", &settings.slider_bypass))
            hacks::slider_bypass(settings.slider_bypass);
        ImGui::End();
    }
}

DWORD MainThread(LPVOID lpParam)
{
    MH_Initialize();

    ImGuiHook::setInitFunction(InitUI);
    ImGuiHook::setRenderFunction(RenderUI);

    ImGuiHook::setToggleCallback([]() {
        g_visible = !g_visible;
    });

    ImGuiHook::setToggleKey(VK_TAB);


    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });

    //MH_CreateHook(reinterpret_cast<void*>(hacks::base + 0x1B1C80), hooks::pushButton, reinterpret_cast<void**>(&hooks::pushButton_H));
    MH_EnableHook(MH_ALL_HOOKS);

    return S_OK;
}

DWORD __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
		break;
    case DLL_PROCESS_DETACH:
        break;
	default:
		break;
	}

	return TRUE;
}