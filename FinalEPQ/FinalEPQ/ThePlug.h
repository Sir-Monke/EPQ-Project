#pragma once
#include "includes.h"
#include "Helper.h"
#include "Memory.h"

extern uintptr_t modBase;

class Hacks {
public:
    void RadarHack(bool toggle);
    void NoRecoil(bool toggle);
    void AmmoHack(bool toggle);
    void HealthHack(bool toggle);
    void ESP(bool toggle);
    void FovHack(float slider);

    bool Init();
    void Kill();

private:
    cWeapon Weapon;
    Entity lPlayer;
};