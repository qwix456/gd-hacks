#pragma once

#include <Windows.h>
#include <vector>
#include <commdlg.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

static std::vector<HMODULE> Dlls;
static int loadedDlls;
static bool loadDll = false;

namespace utils
{
    void WriteBytes(uintptr_t address, std::vector<uint8_t> bytes);
    bool WriteByte(uintptr_t address, std::string bytes);
    std::string OpenDialogDLL();
    void LoadDll();
} // namespace utils