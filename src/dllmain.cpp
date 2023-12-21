#include "includes.hpp"
#include "hacks.hpp"

static bool g_visible;
struct settings hacks_;

void InitUI()
{
    ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.f);
}

void RenderUI()
{
    if (g_visible)
    {
        ImGui::Begin("Hacks");
        if (ImGui::Checkbox("Noclip", &hacks_.noclip))
            hacks::noclip(hacks_.noclip);
        if (ImGui::Checkbox("Practice Music Hack", &hacks_.practice_music_hack))
            hacks::practice(hacks_.practice_music_hack);
        if (ImGui::Checkbox("Copy hack", &hacks_.copy_hack))
            hacks::copy_hack(hacks_.copy_hack);
        if (ImGui::Checkbox("Verify hack", &hacks_.verify_hack))
            hacks::verify_hack(hacks_.verify_hack);
        if (ImGui::Checkbox("Unlock all", &hacks_.unlock_all))
            hacks::unlock_all(hacks_.unlock_all);
        if (ImGui::Checkbox("No wave trail", &hacks_.no_wave_trail))
            hacks::no_wave_trail(hacks_.no_wave_trail);
        if (ImGui::Checkbox("Slider bypass", &hacks_.slider_bypass))
            hacks::slider_bypass(hacks_.slider_bypass);
        if (ImGui::Checkbox("Buy item bypass", &hacks_.buy_item_bypass))
            hacks::buy_item_bypass(hacks_.buy_item_bypass);
        if (ImGui::Checkbox("Keymaster bypass", &hacks_.keymaster_bypass))
            hacks::keymaster_bypass(hacks_.keymaster_bypass);
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