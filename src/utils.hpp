#pragma once

#include <Windows.h>
#include <vector>
#include <commdlg.h>
#include <filesystem>

static std::vector<HMODULE> Dlls;
static int loadedDlls;
static bool loadDll = false;

static void WriteBytes(uintptr_t address, std::vector<uint8_t> bytes)
{
	DWORD old_prot;
	VirtualProtect((void*)(address), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy((void*)(address), bytes.data(), bytes.size());
	VirtualProtect((void*)(address), bytes.size(), old_prot, &old_prot);
}

static void InjectDLL(DWORD id, const char* path) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
    if (hProcess == NULL)
        return;

    LPVOID dllAddr = VirtualAllocEx(hProcess, NULL, strlen(path) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (dllAddr == NULL) {
        CloseHandle(hProcess);
        return;
    }

    WriteProcessMemory(hProcess, dllAddr, path, strlen(path) + 1, NULL);

    LPVOID loadLibAddr = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (loadLibAddr == NULL) {
        VirtualFreeEx(hProcess, dllAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibAddr, dllAddr, 0, NULL);
    if (hThread == NULL) {
        VirtualFreeEx(hProcess, dllAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, dllAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
}

static const char* OpenDialogDLL(HWND hwnd) {
    OPENFILENAME ofn;
    CHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Dynamic Link Libraries\0*.dll\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrTitle = "Select the DLL to inject";
    ofn.Flags = OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
        return szFile;
    else
        return nullptr;
}

static void LoadDll() {
    std::string dllDirectory = "gd-hacks/dlls";
    for (auto& entry : std::filesystem::directory_iterator(dllDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dll") {
            std::string dllPath = entry.path().generic_string();
            HMODULE module = LoadLibraryA(dllPath.c_str());
            if (module != nullptr) {
                Dlls.push_back(module);
                loadedDlls++;
            }
        }
    }
}
