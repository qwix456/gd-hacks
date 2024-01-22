#include "utils.hpp"

namespace utils
{
    void WriteBytes(uintptr_t address, std::vector<uint8_t> bytes)
    {
        DWORD old_prot;
        VirtualProtect((void*)(address), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
        memcpy((void*)(address), bytes.data(), bytes.size());
        VirtualProtect((void*)(address), bytes.size(), old_prot, &old_prot);
    }

    bool WriteByte(uintptr_t address, std::string bytes)
    {
        std::vector<unsigned char> byteVec;
        std::stringstream byteStream(bytes);
        std::string byteStr;

        while (getline(byteStream, byteStr, ' '))
        {
            unsigned int byte = std::stoul(byteStr, nullptr, 16);
            byteVec.push_back(static_cast<unsigned char>(byte));
        }

        DWORD oldProtect;
        if (VirtualProtect(reinterpret_cast<void *>(address), byteVec.size(), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            memcpy(reinterpret_cast<void *>(address), byteVec.data(), byteVec.size());
            VirtualProtect(reinterpret_cast<void *>(address), byteVec.size(), oldProtect, &oldProtect);
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string OpenDialogDLL()
    {
        OPENFILENAME ofn;
        CHAR szFile[MAX_PATH] = { 0 };

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = "Dynamic Link Libraries\0*.dll\0";
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrTitle = "Select the DLL to inject";
        ofn.Flags = OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn)) {
            return szFile;
        }
        else {
            return "false";
        }
    }

    void LoadDll()
    {
        for (auto& entry : std::filesystem::directory_iterator("gdhacks/dlls")) {
            if (entry.is_regular_file() && entry.path().extension() == ".dll") {
                HMODULE module = LoadLibraryA(entry.path().generic_string().c_str());
                if (module != nullptr) {
                    Dlls.push_back(module);
                    loadedDlls++;
                }
            }
        }
    }
}