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
        ImGui::Begin("ModMenu");
        if (ImGui::BeginTabBar("##tabbar"))
        {
            if (ImGui::BeginTabItem("Global"))
            {
                if (ImGui::Checkbox("NoClip", &hacks_.noclip))
                    hacks::noclip(hacks_.noclip);
                if (ImGui::Checkbox("Practice Music Hack", &hacks_.practice_music_hack))
                    hacks::practice(hacks_.practice_music_hack);
                if (ImGui::Checkbox("Copy Hack", &hacks_.copy_hack))
                    hacks::copy_hack(hacks_.copy_hack);
                if (ImGui::Checkbox("Verify Hack", &hacks_.verify_hack))
                    hacks::verify_hack(hacks_.verify_hack);
                if (ImGui::Checkbox("Unlock All", &hacks_.unlock_all))
                    hacks::unlock_all(hacks_.unlock_all);
                if (ImGui::Checkbox("Unlock All Levels", &hacks_.unlock_all_levels))
                    hacks::unlock_all_levels(hacks_.unlock_all_levels);
                if (ImGui::Checkbox("No Wave Trail", &hacks_.no_wave_trail))
                    hacks::no_wave_trail(hacks_.no_wave_trail);
                if (ImGui::Checkbox("No Death Texture", &hacks_.no_death_texture))
                    hacks::no_death_texture(hacks_.no_death_texture);
                if (ImGui::Checkbox("No Death Effect", &hacks_.no_death_parcticle))
                    hacks::no_death_parcticle(hacks_.no_death_parcticle);
                if (ImGui::Checkbox("Ignore Pause ESC", &hacks_.ignore_pause_esc))
                    hacks::ignore_pause_esc(hacks_.ignore_pause_esc);
                if (ImGui::Checkbox("Ignore ESC", &hacks_.ignore_esc))
                    hacks::ignore_esc(hacks_.ignore_esc);

                ImGui::PushItemWidth(150);
                ImGui::DragFloat("Speed", &speed, 0.01f, 0, FLT_MAX, "%.2f");
                ImGui::PopItemWidth();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Bypass"))
            {
                if (ImGui::Checkbox("Slider Bypass", &hacks_.slider_bypass))
                    hacks::slider_bypass(hacks_.slider_bypass);
                if (ImGui::Checkbox("Buy Item Bypass", &hacks_.buy_item_bypass))
                    hacks::buy_item_bypass(hacks_.buy_item_bypass);
                if (ImGui::Checkbox("Keymaster Bypass", &hacks_.keymaster_bypass))
                    hacks::keymaster_bypass(hacks_.keymaster_bypass);
                if (ImGui::Checkbox("Scratch Bypass", &hacks_.scratch_bypass))
                    hacks::scratch_bypass(hacks_.scratch_bypass);
                if (ImGui::Checkbox("Potbor Bypass", &hacks_.potbor_bypass))
                    hacks::potbor_bypass(hacks_.potbor_bypass);
                if (ImGui::Checkbox("The Mechanic Bypass", &hacks_.the_mechanic_bypass))
                    hacks::the_mechanic_bypass(hacks_.the_mechanic_bypass);
                if (ImGui::Checkbox("Diamond Shopkeeper Bypass", &hacks_.diamond_shopkeeper_bypass))
                    hacks::diamond_shopkeeper(hacks_.diamond_shopkeeper_bypass);
                if (ImGui::Checkbox("Treasure Room Bypass", &hacks_.treasure_room_bypass))
                    hacks::treasure_room_bypass(hacks_.treasure_room_bypass);
                if (ImGui::Checkbox("Custom Object Bypass", &hacks_.custom_object_bypass))
                    hacks::custom_object_bypass(hacks_.custom_object_bypass);

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    MH_Initialize();

    ImGuiHook::setRenderFunction(RenderUI);

    ImGuiHook::setToggleFunction([]() {
        g_visible = !g_visible;
    });

    ImGuiHook::Load([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });

    MH_CreateHook(GetProcAddress(hacks::cocos_base, "?update@CCScheduler@cocos2d@@UAEXM@Z"), CCScheduler_update_H, (void**)&CCScheduler_update);

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