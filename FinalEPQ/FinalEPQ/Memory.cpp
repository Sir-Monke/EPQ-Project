#include "Memory.h"

template<typename T>
T Read(uintptr_t address)
{
    return *((T*)address);
}

template<typename T>
void Write(uintptr_t address, T value)
{
    *((T*)address) = value;
}

template<typename T>
uintptr_t Protect(uintptr_t address, uintptr_t prot)
{
    DWORD oldProt;
    VirtualProtect((LPVOID)address, sizeof(T), prot, &oldProt);
    return oldProt;
}

namespace Memory {

    void NopBytes(uintptr_t addr, const std::vector<unsigned char>& oriBytes, size_t size, bool restore) {
        DWORD oldProtect;
        if (restore) {
            VirtualProtect((LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
            memset((LPVOID)addr, 0x90, size);
        }
        else {
            if (!oriBytes.empty()) {
                VirtualProtect((LPVOID)addr, oriBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
                memcpy((LPVOID)addr, oriBytes.data(), oriBytes.size());
            }
        }
        VirtualProtect((LPVOID)addr, size, oldProtect, &oldProtect);
    }

    MODULEINFO GetModuleInfo(const char* szModule) {
        MODULEINFO modInfo = { 0 };
        wchar_t wszModule[MAX_PATH];
        MultiByteToWideChar(CP_ACP, 0, szModule, -1, wszModule, MAX_PATH);
        HMODULE hModule = GetModuleHandle(wszModule);
        if (hModule != NULL) {
            GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
        }
        return modInfo;
    }

    uintptr_t FindPattern(const char* pattern, const char* mask) {
        MODULEINFO mInfo = GetModuleInfo("ac_client.exe");
        uintptr_t base = (uintptr_t)GetModuleHandle(L"ac_client.exe");
        uintptr_t size = mInfo.SizeOfImage;
        uintptr_t patternLength = static_cast<uintptr_t>(strlen(mask));
        for (uintptr_t i = 0; i < size - patternLength; i++) {
            bool found = true;
            for (uintptr_t j = 0; j < patternLength; j++) {
                if (mask[j] != '?' && pattern[j] != *reinterpret_cast<char*>(base + i + j)) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return static_cast<uintptr_t>(i);
            }
        }
        return NULL;
    }

    uintptr_t JumpHook(uintptr_t hookAt, uintptr_t newFunc, int size) {
        uintptr_t newOffset = newFunc - hookAt - 5;
        auto oldProtection = Protect<uintptr_t[3]>(hookAt + 1, PAGE_EXECUTE_READWRITE);
        Write<BYTE>(hookAt, 0xE9);
        Write<uintptr_t>(hookAt + 1, newOffset);
        for (unsigned int i = 5; i < size; i++)
            Write<BYTE>(hookAt + i, 0x90);
        Protect<uintptr_t[3]>(hookAt + 1, oldProtection);
        return hookAt + 5;
    }
}