#include "includes.h"

class Hooks {
public:
	Hooks() {
		if (SwapBuffersAddr == NULL) {
			SwapBuffersAddr = (uintptr_t)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
		}
	}

	//Init
	void wglSwapBuffersInit();

	//Kill
	void wglSwapBuffersKill();

private:
	uintptr_t SwapBuffersAddr = NULL;
};