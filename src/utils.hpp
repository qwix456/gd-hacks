#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>

bool writeBytes(std::uintptr_t const address, std::vector<uint8_t> const& bytes)
{
        return WriteProcessMemory(
        GetCurrentProcess(),
        reinterpret_cast<LPVOID>(address),
        bytes.data(),
        bytes.size(),
        nullptr);
}