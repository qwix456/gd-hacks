#include "gui.hpp"
#include "hooks.hpp"
#include "hacks/font.h"
#include "other/bot.hpp"
#include "other/reader.hpp"

namespace gui
{
    void ApplyColor()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromMemoryTTF(font, 18, 17.0f);

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding                     = ImVec2(8.00f, 8.00f);
        style.FramePadding                      = ImVec2(5.00f, 2.00f);
        style.GrabMinSize                       = 10;
        style.WindowBorderSize                  = 1;
        style.ChildBorderSize                   = 1;
        style.PopupBorderSize                   = 1;
        style.TabBorderSize                     = 1;
        style.WindowRounding                    = 7;
        style.ChildRounding                     = 4;
        style.FrameRounding                     = 3;
        style.PopupRounding                     = 4;
        style.ScrollbarRounding                 = 9;
        style.GrabRounding                      = 3;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 4;
        style.WindowTitleAlign                  = ImVec2(0.5f,0.5f);
    }

    void layout_mode(bool active)
    {
        if (active) {
            utils::WriteBytes(base + 0x13EFA1, {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
        }
        else {
            utils::WriteBytes(base + 0x13EFA1, {0x88, 0x87, 0x62, 0x04, 0x00, 0x00});
        }
    }

    void RenderInfo()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
        ImGui::Begin("Info", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        
        if (hooks::pl) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 200).Value);
            bool isRobTopLvl = hooks::pl->m_level()->m_levelID() < 5004 && hooks::pl->m_level()->m_levelID() > 0;

            if (hacks_.labels) {
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
            }

            ImGui::PopStyleColor();
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void render() {
        if (!m_visibleGui)
            return;

        if (reader::data.empty()) {
            hooks::print("No items in data.");
            return;
        }

        for (auto& item : reader::data.items()) {
            ImGui::Begin(item.key().c_str());

            json& hack = item.value();
            for (size_t i = 0; i < hack.size(); i++) {
                json& item_hack = hack[i];
                bool enabled = item_hack["enabled"];

                if (ImGui::Checkbox(item_hack["name"].get<std::string>().c_str(), &enabled)) {
                    item_hack["enabled"] = enabled;

                    json opcodes = item_hack["opcodes"];
                    for (auto& opcode : opcodes) {
                        std::string address_str = opcode["address"];
                        std::string byte_str = enabled ? opcode["on"] : opcode["off"];

                        uintptr_t address;
                        sscanf_s(address_str.c_str(), "%x", &address);

                        DWORD base2 = (DWORD)GetModuleHandleA(0);
                        if (!opcode["lib"].is_null()) {
                            base2 = (DWORD)GetModuleHandleA(std::string(opcode["lib"]).c_str());
                        }

                        utils::WriteByte(base2 + address, byte_str);
                    }

                    std::ofstream out("gdhacks/hacks.json");
                    out << reader::data.dump(4);
                    out.close();
                }
            }

            if (item.key() == "Bypass") {
                ImGui::DragFloat("##fpsvalue", &hacks_.fps, 0.01f, 0, FLT_MAX, "FPS %.2f");
                ImGui::SameLine();
                ImGui::Checkbox("Bypass", &hacks_.fps_bypass);
            }

            if (item.key() == "GDBot") {
                  ImGui::Combo("Mode", &bot::m_mode, "Disabled\0Record\0Playback");
                ImGui::PushItemWidth(120);
                ImGui::InputText("Replay Name", hacks_.replay_name, ImGuiInputTextFlags_EnterReturnsTrue);
                ImGui::PopItemWidth();
                ImGui::Separator();
                ImGui::Text("Frame: %i", bot::get_frame(GameManager::sharedState()->m_pPlayLayer()));
                ImGui::Text("Actions: %i", bot::replay.size());
                ImGui::Separator();
                ImGui::Checkbox("Checkpoint Fix", &hacks_.checkpoint_fix);
                ImGui::Checkbox("Ignore input on playback", &hacks_.ignore_user_input);
                ImGui::Separator();
                if (ImGui::Button("Save")) {
                    bot::save_replay(hacks_.replay_name);
                }
                ImGui::SameLine();
                if (ImGui::Button("Load")) {
                    bot::load_replay(hacks_.replay_name);
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear")) {
                    bot::replay.clear();
                }
            }

            if (item.key() == "Visuals") {
                ImGui::Checkbox("Rainbow Icons", &hacks_.rainbow_icons);
                ImGui::SameLine();
                if (ImGui::ArrowButton("rainbow", ImGuiDir_Right))
                    ImGui::OpenPopup("Rainbow Icons Settings");
                if (ImGui::BeginPopupModal("Rainbow Icons Settings", NULL)) {
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
                    ImGui::EndPopup();
                }

                ImGui::Checkbox("Labels", &hacks_.labels);
                ImGui::SameLine();
                if (ImGui::ArrowButton("labels", ImGuiDir_Right))
                    ImGui::OpenPopup("Labels Settings");
                if (ImGui::BeginPopupModal("Labels Settings", NULL)) {
                    ImGui::Checkbox("Level Name", &hacks_.level_name);
                    ImGui::Checkbox("Creator", &hacks_.author);
                    ImGui::Checkbox("LevelID", &hacks_.level_id);
                    ImGui::Checkbox("Attempts", &hacks_.total_attempts);
                    ImGui::Checkbox("Jumps", &hacks_.total_jumps);
                    ImGui::Checkbox("Normal Percent", &hacks_.normal_percent);
                    ImGui::Checkbox("Practice Percent", &hacks_.practice_percent);
                    if (ImGui::Button("Close")) {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();  
                }
            }

            if (item.key() == "Utils") {
                if (ImGui::Button("Inject DLL")) {
                    std::string dllPath = utils::OpenDialogDLL();
                    if (dllPath != "false") {
                        LoadLibraryA(dllPath.c_str());
                        loadedDlls++;
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

            if (item.key() == "Level") {
                if (ImGui::Checkbox("Show Layout", &hacks_.show_layout))
                    layout_mode(hacks_.show_layout);
                ImGui::Checkbox("StartPos Switcher", &hacks_.startpos_switcher);
                ImGui::Checkbox("Use A/D for StartPos Switcher", &hacks_.alt_keys);
                ImGui::DragFloat("##speed", &hacks_.speed, 0.01f, 0, FLT_MAX, "Speed %.2f");
                ImGui::SameLine();
                ImGui::Checkbox("Speedhack", &hacks_.speedhack);
            }

            ImGui::End();
        }
    }



    void RenderUI()
    {
        RenderInfo();
        if (m_visibleGui)
            render(); // dont ask
    }

    void ShowUI()
    {
        m_visibleGui = !m_visibleGui;
    }
}