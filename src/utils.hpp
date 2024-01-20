#pragma once

#include <Windows.h>
#include <vector>
#include <commdlg.h>
#include <fstream>
#include <filesystem>
#include <string>

static std::vector<HMODULE> Dlls;
static int loadedDlls;
static bool loadDll = false;

namespace utils
{
    void WriteBytes(uintptr_t address, std::vector<uint8_t> bytes);
    std::string OpenDialogDLL();
    void LoadDll();
} // namespace utils