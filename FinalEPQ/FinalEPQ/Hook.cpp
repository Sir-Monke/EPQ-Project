#include "hook.h"

void Hooks::wglSwapBuffersInit() {

}

void Hooks::wglSwapBuffersKill() {
	std::vector<unsigned char> oriBytes = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC }; // ori bytes
}
