#include "ThePlug.h"

bool Hacks::Init() {

    return false;
}

void Hacks::Kill() {
    RadarHack(false);
    NoRecoil(false);
    AmmoHack(false);
    HealthHack(false);
    ESP(false);
}

void Hacks::RadarHack(bool toggle) {
    std::vector<unsigned char> oriBytes1 = { 0x0F, 0x85, 0x4A, 0x01, 0x00, 0x00 };
    std::vector<unsigned char> oriBytes2 = { 0x74, 0x36, 0x83, 0xFB, 0x04, 0x74, 0x31, 0x83, 0xFB, 0x05, 0x74, 0x2C, 0x83, 0xFB, 0x07, 0x74, 0x27, 0x83, 0xFB, 0x0B, 0x74, 0x22, 0x83, 0xFB, 0x0D, 0x74, 0x1D, 0x83, 0xFB, 0x0E, 0x74, 0x18, 0x83, 0xFB, 0x10, 0x74, 0x13, 0x83, 0xFB, 0x11, 0x74, 0x0E, 0x83, 0xFB, 0x14, 0x74, 0x09, 0x83, 0xFB, 0x15, 0x0F, 0x85, 0x5C, 0x01, 0x00, 0x00 };
    Memory::NopBytes((uintptr_t)(modBase + 0x9FB3), oriBytes1, 6, toggle);
    Memory::NopBytes((uintptr_t)(modBase + 0x9F6F), oriBytes2, 56, toggle);
}

void Hacks::NoRecoil(bool toggle) {
    // Implementation needed
}

void Hacks::AmmoHack(bool toggle) {
    std::vector<unsigned char> oriBytes = { 0x29, 0x08 };
    Memory::NopBytes((uintptr_t)(modBase + 0x61E44), oriBytes, 2, toggle);
    if (toggle) {
        if (Weapon.GetWeaponId() != Weapon.GUN_KNIFE && Weapon.GetWeaponMag() <= 10) {
            Weapon.SetWeaponMag(10);
        }
    }
    std::cout << toggle << endl;
}

void Hacks::HealthHack(bool toggle) {
    if (toggle) {
        lPlayer.SetHealth(500);
    }
}

void Hacks::FovHack(float slider) {
    lPlayer.SetFOV(slider);
}

void Hacks::ESP(bool toggle) {

}