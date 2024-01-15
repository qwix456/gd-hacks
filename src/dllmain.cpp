#include "includes.hpp"
#include "hacks.hpp"
#include "hooks.hpp"
#include "bools.hpp"
#include "saving.hpp"
#include "font.h"
#include "rich.hpp"
#include <filesystem>

static bool g_visible = false;
struct settings hacks_;
HWND g_hWnd = FindWindow(nullptr, "Geometry Dash");

__declspec(dllexport) void HACKS() {
    return;
}

void SetColors() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromMemoryTTF(font, 14, 15.0f);

    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.31f, 0.31f, 0.54f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.40f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.61f, 0.61f, 0.61f, 0.67f);
    style->Colors[ImGuiCol_TitleBg] = style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.35f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    style->FrameRounding = 4.00f;
    style->WindowRounding = 4.00f;
}

void RenderInfo() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
    ImGui::Begin("Info", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
    
    if (CheatHooks::pl != nullptr) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 200).Value);

        if (hacks_.author)
            ImGui::Text("Author %s", CheatHooks::pl->m_level()->m_levelAuthor().c_str());
        if (hacks_.level_id)
            ImGui::Text("LevelID %i", CheatHooks::pl->m_level()->m_levelID());
        if (hacks_.total_attempts)
            ImGui::Text("Attempt %i", CheatHooks::pl->m_level()->m_totalAtt());
        if (hacks_.total_jumps)
            ImGui::Text("Jumps %i", CheatHooks::pl->m_level()->m_totalJumps());
        if (hacks_.normal_percent)
            ImGui::Text("Normal %i", CheatHooks::pl->m_level()->m_normal());
        if (hacks_.practice_percent)
            ImGui::Text("Practice %i", CheatHooks::pl->m_level()->m_practiceP());

        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void RenderLevel() {
    if (ImGui::Begin("Level", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Checkbox("Show Layout", &hacks_.show_layout))
            hacks::layout_mode(hacks_.show_layout);
        ImGui::Checkbox("StartPos Switcher", &hacks_.startpos_switcher);
        ImGui::Checkbox("Use A/D for StartPos Switcher", &hacks_.alt_keys);
        ImGui::DragFloat("##speed", &hacks_.speed, 0.01f, 0, FLT_MAX, "Speed %.2f");
    }

    ImGui::End();
}

void RenderPlayer() {
    if (ImGui::Begin("Player", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Checkbox("NoClip", &hacks_.noclip))
            hacks::noclip(hacks_.noclip);
        if (ImGui::Checkbox("Unlock All", &hacks_.unlock_all))
            hacks::unlock_all(hacks_.unlock_all);
        if (ImGui::Checkbox("No Transition", &hacks_.no_transition))
            hacks::no_transition(hacks_.no_transition);
        if (ImGui::Checkbox("No Shaders", &hacks_.no_shaders))
            hacks::no_shaders(hacks_.no_shaders);
    }

    ImGui::End();
}

void RenderLabel() {
    if (ImGui::Begin("Labels", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Checkbox("Author", &hacks_.author);
        ImGui::Checkbox("LevelID", &hacks_.level_id);
        ImGui::Checkbox("Attempts", &hacks_.total_attempts);
        ImGui::Checkbox("Jumps", &hacks_.total_jumps);
        ImGui::Checkbox("Normal Percent", &hacks_.normal_percent);
        ImGui::Checkbox("Practice Percent", &hacks_.practice_percent);
    }

    ImGui::End();
}

void RenderCreator() {
    if (ImGui::Begin("Creator", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Checkbox("Copy Hack", &hacks_.copy_hack))
            hacks::copy_hack(hacks_.copy_hack);
        if (ImGui::Checkbox("Verify Hack", &hacks_.verify_hack))
            hacks::verify_hack(hacks_.verify_hack);
        if (ImGui::Checkbox("Custom Object Bypass", &hacks_.custom_object_bypass))
            hacks::custom_object_bypass(hacks_.custom_object_bypass);
    }

    ImGui::End();
}

void RenderBypass() {
    if (ImGui::Begin("Bypass", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Checkbox("Text Bypass", &hacks_.text_bypass))
            hacks::text_bypass(hacks_.text_bypass);
        if (ImGui::Checkbox("Treasure Room Bypass", &hacks_.treasure_room_bypass))
            hacks::treasure_room_bypass(hacks_.treasure_room_bypass);
        if (ImGui::Checkbox("Scratch Bypass", &hacks_.scratch_bypass))
            hacks::scratch_bypass(hacks_.scratch_bypass);
        if (ImGui::Checkbox("Potbor Bypass", &hacks_.potbor_bypass))
            hacks::potbor_bypass(hacks_.potbor_bypass);
        if (ImGui::Checkbox("The Mechanic Bypass", &hacks_.the_mechanic_bypass))
            hacks::the_mechanic_bypass(hacks_.the_mechanic_bypass);
        if (ImGui::Checkbox("Diamond Shopkeeper Bypass", &hacks_.diamond_shopkeeper_bypass))
            hacks::diamond_shopkeeper_bypass(hacks_.diamond_shopkeeper_bypass);
    }

    ImGui::End();
}

void RenderUtils() {
    if (ImGui::Begin("Utils", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Button("Inject DLL")) {
            const char* dllPath = OpenDialogDLL(g_hWnd);
            if (dllPath != nullptr) {
                InjectDLL(GetCurrentProcessId(), dllPath);
            }
        }
        if (ImGui::Button("Uncomplete Level"))
        {
            if (CheatHooks::pl)
            {
                CheatHooks::pl->m_level()->setZeroJumps();
                CheatHooks::pl->m_level()->setZeroAtt();
                CheatHooks::pl->m_level()->setZeroNormal();
                CheatHooks::pl->m_level()->setPractice();
                CheatHooks::pl->m_level()->setZeroLead();
            }
        }

        ImGui::Checkbox("Discord RPC", &hacks_.discord_rpc);

        ImGui::Text("DLLs loaded: %d", loadedDlls);
    }

    ImGui::End();
}

void RenderUI()
{
    RenderInfo();
    if (g_visible)
    {
        RenderLevel();
        RenderLabel();
        RenderPlayer();
        RenderCreator();
        RenderBypass();
        RenderUtils();
    }
}

DWORD WINAPI MainThread(void* lpParam) {
    MH_Initialize();

    std::filesystem::create_directory("gd-hacks");
    std::filesystem::create_directory("gd-hacks/dlls");

    LoadDll();
    saving::Load();
    ImGuiHook::setRenderFunction(RenderUI);
    ImGuiHook::setInitFunction(SetColors);
    ImGuiHook::setKeyPressHandler([](int key) {
        if (key == VK_TAB)
            g_visible = !g_visible;
        CheatHooks::handleKeyPress(key);
    });
    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });
    CheatHooks::init();

    MH_EnableHook(MH_ALL_HOOKS);
    return S_OK;
}

DWORD WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, MainThread, 0, 0, 0);
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        for (HMODULE module : Dlls) {
            FreeLibrary(module);
        }
        saving::Save();
    }

	return TRUE;
}