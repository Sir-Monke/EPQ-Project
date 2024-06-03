#pragma once
#include "includes.h"

namespace Memory {
    void NopBytes(uintptr_t addr, const std::vector<unsigned char>& oriBytes, size_t size, bool restore);

    MODULEINFO GetModuleInfo(const char* szModule);

    uintptr_t FindPattern(const char* pattern, const char* mask);

    uintptr_t JumpHook(uintptr_t hookAt, uintptr_t newFunc, int size);
}