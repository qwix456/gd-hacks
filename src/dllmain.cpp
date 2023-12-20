#include "includes.hpp"
#include "hacks.hpp"

static bool g_visible;
static bool noclip;
static bool practice_music_hack;
static bool unlock_all;
static bool copy_hack;
static bool verify_hack;
static bool keymaster_bypass;

void InitUI()
{
    ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.f);
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(26/255.0f, 26/255.0f, 26/255.0f, 1.0f);
    colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(15/255.0f, 15/255.0f, 15/255.0f, 1.0f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowTitleAlign                  = ImVec2(0.5f,0.5f);
}

void RenderUI()
{
    if (g_visible)
    {
        ImGui::Begin("Global", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::Checkbox("Noclip", &noclip))
            hacks::noclip(noclip);
        if (ImGui::Checkbox("Practice Music Hack", &practice_music_hack))
            hacks::practice(practice_music_hack);
        if (ImGui::Checkbox("Copy hack", &copy_hack))
            hacks::copy_hack(copy_hack);
        if (ImGui::Checkbox("Verify hack", &verify_hack))
            hacks::verify_hack(verify_hack);
        if (ImGui::Checkbox("Keymaster bypass", &keymaster_bypass))
            hacks::keymaster_bypass(keymaster_bypass);
        if (ImGui::Checkbox("Unlock all", &unlock_all))
            hacks::unlock_all(unlock_all);
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