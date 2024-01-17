#include "includes.hpp"
#include "hooks.hpp"
#include "saving.hpp"
#include "hacks.hpp"
#include "font.h"
#include <filesystem>

static bool g_visible = false;
struct settings hacks_;

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
    
    if (hooks::pl != nullptr) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 200).Value);
        bool isRobTopLvl = hooks::pl->m_level()->m_levelID() < 5004 && hooks::pl->m_level()->m_levelID() > 0;

        if (hacks_.level_name)
            ImGui::Text("Name %s", hooks::pl->m_level()->m_levelName().c_str());
        if (hacks_.author && isRobTopLvl)
            ImGui::Text("Author RobTop");
        else if (hacks_.author && !isRobTopLvl)
            ImGui::Text("Author %s", hooks::pl->m_level()->m_levelAuthor().c_str());
        if (hacks_.level_id)
            ImGui::Text("LevelID %i", hooks::pl->m_level()->m_levelID());
        if (hacks_.total_attempts)
            ImGui::Text("Attempt %i", hooks::pl->m_level()->m_totalAtt());
        if (hacks_.total_jumps)
            ImGui::Text("Jumps %i", hooks::pl->m_level()->m_totalJumps());
        if (hacks_.normal_percent)
            ImGui::Text("Normal %i", hooks::pl->m_level()->m_normal());
        if (hacks_.practice_percent)
            ImGui::Text("Practice %i", hooks::pl->m_level()->m_practiceP());

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
        if (ImGui::Checkbox("Unlock All Levels", &hacks_.unlock_all_levels))
            hacks::unlock_all_levels(hacks_.unlock_all_levels);
        if (ImGui::Checkbox("No Transition", &hacks_.no_transition))
            hacks::no_transition(hacks_.no_transition);
        if (ImGui::Checkbox("No Shaders", &hacks_.no_shaders))
            hacks::no_shaders(hacks_.no_shaders);
        if (ImGui::Checkbox("No Death Effect", &hacks_.no_death_effect))
            hacks::no_death_effect(hacks_.no_death_effect);
        if (ImGui::Checkbox("No Trail", &hacks_.no_trail))
            hacks::no_trail(hacks_.no_trail);
        if (ImGui::Checkbox("No Wave Trail", &hacks_.no_wave_trail))
            hacks::no_wave_trail(hacks_.no_wave_trail);
        if (ImGui::Checkbox("No Camera Move", &hacks_.no_camera_move))
            hacks::no_camera_move(hacks_.no_camera_move);
        if (ImGui::Checkbox("No Camera Zoom", &hacks_.no_camera_zoom))
            hacks::no_camera_zoom(hacks_.no_camera_zoom);
        ImGui::Checkbox("Rainbow Icons", &hacks_.rainbow_icons);
        ImGui::SameLine();
        if (ImGui::ArrowButton("rainbow", ImGuiDir_Right))
            ImGui::OpenPopup("Rainbow Icons Settings");
        if (ImGui::BeginPopupModal("Rainbow Icons Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Checkbox("Rainbow Color 1", &hacks_.rainbow_color_1);
            ImGui::Checkbox("Rainbow Color 2", &hacks_.rainbow_color_2);
            ImGui::Checkbox("Rainbow Wave Trail", &hacks_.rainbow_wave_trail);
            ImGui::PushItemWidth(100);
            ImGui::InputFloat("Rainbow Speed Interval", &hacks_.rainbow_speed);
            if (ImGui::InputFloat("Rainbow Pastel Amount", &hacks_.pastel)) {
                hacks_.pastel = hacks_.pastel <= 0.1f ? 0.1f : hacks_.pastel > 1.0f ? 1.0f : hacks_.pastel;
            }
            ImGui::PopItemWidth();
            if (ImGui::Button("Close")) {
                ImGui::CloseCurrentPopup();
            }
        }
    }

    ImGui::End();
}

void RenderLabel() {
    if (ImGui::Begin("Labels", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Checkbox("Level Name", &hacks_.level_name);
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
        if (ImGui::Checkbox("Text Bypass", &hacks_.text))
            hacks::text_bypass(hacks_.text);
        if (ImGui::Checkbox("Treasure Room", &hacks_.treasure))
            hacks::treasure_room_bypass(hacks_.treasure);
        if (ImGui::Checkbox("Scratch", &hacks_.scratch))
            hacks::scratch_bypass(hacks_.scratch);
        if (ImGui::Checkbox("Potbor", &hacks_.potbor))
            hacks::potbor_bypass(hacks_.potbor);
        if (ImGui::Checkbox("The Mechanic", &hacks_.the_mechanic))
            hacks::the_mechanic_bypass(hacks_.the_mechanic);
        if (ImGui::Checkbox("Diamond Shopkeeper", &hacks_.diamond_shopkeeper))
            hacks::diamond_shopkeeper_bypass(hacks_.diamond_shopkeeper);
        if (ImGui::Checkbox("Vault of Secrets", &hacks_.vault_of_secrets))
            hacks::vault_of_secrets(hacks_.vault_of_secrets);
        if (ImGui::Checkbox("Free Shops", &hacks_.free_shops))
            hacks::free_shops(hacks_.free_shops);
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
            if (hooks::pl)
            {
                hooks::pl->m_level()->setZeroJumps();
                hooks::pl->m_level()->setZeroAtt();
                hooks::pl->m_level()->setZeroNormal();
                hooks::pl->m_level()->setPractice();
                hooks::pl->m_level()->setZeroLead();
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

DWORD WINAPI MainThread(LPVOID lpParam) {
    MH_Initialize();
    std::filesystem::create_directory("gdhacks");
    std::filesystem::create_directory("gdhacks/dlls");

    saving::Load();
    ImGuiHook::setRenderFunction(RenderUI);
    ImGuiHook::setInitFunction(SetColors);
    ImGuiHook::setKeyPressHandler([](int key) {
        if (key == VK_TAB) {
            g_visible = !g_visible;
        }
        hooks::handleKeyPress(key);
    });
    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });
    hooks::init();
    hooks::console();
    LoadDll();
    MH_EnableHook(MH_ALL_HOOKS);
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
        saving::Save();
    }

	return TRUE;
}