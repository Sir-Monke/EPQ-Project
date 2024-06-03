#include "includes.h"
#include "ThePlug.h"

uintptr_t modBase = NULL;

DWORD WINAPI MainThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    if (modBase == NULL) {
        modBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    }

    Hacks hacks;
    Game game;
    bool bTemp = false;

   if (game.GetMultiPlayerMatch() == 0) {
        while (true) {
            if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
                bTemp = !bTemp;
                hacks.HealthHack(bTemp);
            }
            if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
                hacks.Kill();
                break;
            }
        }
   } else {
        std::cout << "Exit MultiPlayer." << endl;
   }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, NULL);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hMod, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hMod, 0, NULL);
        break;
    default:
        break;
    }
	return true;
}