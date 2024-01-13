#include "imgui-hook.hpp"
#include <windows.h>

using namespace cocos2d;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ImGuiHook {

	void _stub() {}

	std::function<void()> g_drawFunc = _stub;
	std::function<void()> g_initFunc = _stub;
	std::function<void(int)> g_keyPressCallback = nullptr;

	size_t g_keybind = VK_TAB;
	bool g_inited = false;

	void (__thiscall* CCEGLView_swapBuffers)(CCEGLView*) = nullptr;

	void __fastcall CCEGLView_swapBuffers_H(CCEGLView* self) {
		auto window = self->getWindow();

		if (!g_inited) {
			g_inited = true;
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::GetIO();
            auto hwnd = WindowFromDC(*reinterpret_cast<HDC*>(reinterpret_cast<uintptr_t>(window) + 0x244));
            ImGui_ImplWin32_Init(hwnd);
            ImGui_ImplOpenGL3_Init();
            g_initFunc();
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		g_drawFunc();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glFlush();

		CCEGLView_swapBuffers(self);
	}

	void(__thiscall* CCEGLView_pollEvents)(CCEGLView*) = nullptr;

	void __fastcall CCEGLView_pollEvents_H(CCEGLView* self) {
		if (g_inited) {
			auto& io = ImGui::GetIO();

			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (ImGui_ImplWin32_WndProcHandler(msg.hwnd, msg.message, msg.wParam, msg.lParam))
					continue;

				if (msg.message == WM_SETFOCUS || msg.message == WM_KILLFOCUS)
					continue;
				
				bool blockInput = io.WantCaptureMouse || io.WantCaptureKeyboard;

            	if (!blockInput && msg.message == WM_KEYDOWN && g_keyPressCallback) {
                	g_keyPressCallback(msg.wParam);
           	 	}
				
				}
			}

			CCEGLView_pollEvents(self);
		}

	void(__thiscall* CCEGLView_toggleFullScreen)(CCEGLView*, bool) = nullptr;

    void __fastcall CCEGLView_toggleFullScreen_H(CCEGLView* self, void*, bool toggle) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        g_inited = false;

        CCEGLView_toggleFullScreen(self, toggle);
    }

    void(__thiscall* AppDelegate_applicationWillEnterForeground)(void*) = nullptr;

    void __fastcall AppDelegate_applicationWillEnterForeground_H(void* self) {
        AppDelegate_applicationWillEnterForeground(self);
        ImGui::GetIO().ClearInputKeys();
    }

	void setupHooks(std::function<void(void*, void*, void**)> hookFunc) {
        auto cocosBase = GetModuleHandleA("libcocos2d.dll");
        hookFunc(GetProcAddress(cocosBase, "?swapBuffers@CCEGLView@cocos2d@@UAEXXZ"), CCEGLView_swapBuffers_H,
                 reinterpret_cast<void**>(&CCEGLView_swapBuffers));
        hookFunc(GetProcAddress(cocosBase, "?pollEvents@CCEGLView@cocos2d@@QAEXXZ"), CCEGLView_pollEvents_H,
                 reinterpret_cast<void**>(&CCEGLView_pollEvents));
        hookFunc(GetProcAddress(cocosBase, "?toggleFullScreen@CCEGLView@cocos2d@@QAEX_N@Z"), CCEGLView_toggleFullScreen_H,
                 reinterpret_cast<void**>(&CCEGLView_toggleFullScreen));
        hookFunc(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(GetModuleHandleA(0)) + 0x3d130),
                 reinterpret_cast<void*>(&AppDelegate_applicationWillEnterForeground_H),
                 reinterpret_cast<void**>(&AppDelegate_applicationWillEnterForeground));
    }

    void setRenderFunction(std::function<void()> func) {
		g_drawFunc = func;
    }

    void setInitFunction(std::function<void()> func) {
		g_initFunc = func;
	}

	void setKeybind(size_t key) {
		g_keybind = key;
    }

    void setKeyPressHandler(std::function<void(int)> func) {
		g_keyPressCallback = func;
    }
} // namespace ImGuiHook