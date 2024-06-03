#pragma once
#include "includes.h"
#include "math.h"
#include "draw.h"

extern uintptr_t modBase;

//GlEnable

// char *conoutf(char *Format, ...) "\x81\xEC\x08\x01\x00\x00\x8B\x8C\x24\x0C\x01\x00\x00\x56\x57\x8D\x84\x24\x18\x01\x00\x00\x50\x51\x8D\x54\x24\x10\x68\x04\x01\x00\x00\x52\xE8\xCC\xCC\xCC\xCC\x8D\x44\x24\x18\x50\x68\xCC\xCC\xCC\xCC\xC6\x84\x24\x23\x01\x00\x00\x00\xE8\xCC\xCC\xCC\xCC\x83\xC4\x18\x8D\x4C\x24\x08\x51\xE8\xCC\xCC\xCC\xCC\x8B\x15\xCC\xCC\xCC\xCC\xFF\x05\xCC\xCC\xCC\xCC\x52\xE8\xCC\xCC\xCC\xCC\x8D\x44\x24\x0C", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx????xxxxxxxxx????xxxxxxxxx????xx????xx????xx????xxxx"

class Game {
public:
	//Constructor
	Game() {

	}

	//Getter
	int GetPlayerCount() { return *(int*)(uintptr_t*)(modBase + 0x10F500); }
	int GetGameMode() { return *(int*)(modBase + 0x10F49C); }
	int GetMultiPlayerMatch() { return *(int*)(modBase + 0x109D68); }

private:

};

class Entity : public Game {
public:
	//Constructor
	Entity() {
		if (modBase != NULL) {

		} else if (PlayerBase == NULL) {
			PlayerBase = (uintptr_t)GetLocalPlayer();
		}
	}

	//Getter
	uintptr_t GetLocalPlayer() {return *(uintptr_t*)((modBase + 0x10F4F4)); }
	Vector3 GetPos() { return *(Vector3*)(PlayerBase + 0x34); }
	Vector3 GetViewAngles() { return *(Vector3*)(PlayerBase + 0x40); }
	int GetHealth() { return *(int*)(PlayerBase + 0xF8); }
	int GetArmor() { return *(int*)(PlayerBase + 0xFC); }
	int GetAmmo() { return *(int*)(PlayerBase + 0x148); }
	int GetGrenade() { return *(int*)(PlayerBase + 0x158); }
	int GetTeam() { return *(int*)(PlayerBase + 0x32C); }
	int GetPlayerSpeed() { return *(int*)(PlayerBase + 0x80); }
	int GetPlayerState() { return *(int*)(PlayerBase + 0x82); }
	bool GetPlayerDead() { return *(bool*)(PlayerBase + 0x338); }
	bool GetPlayerAttack() { return *(bool*)(PlayerBase + 0x224); }
	float GetFOV() { return *(float*)(modBase + 0x10F1C4); }
	float GetEyeHeight() { return *(float*)(PlayerBase + 0x5C); }
	float GetPlayerHeight() { return (GetEyeHeight() + *(float*)(PlayerBase + 0x64)); } // should always be 5.2f
	char GetUsername() { return *(char*)(PlayerBase + 0x225); }
	Entity* GetEntById(int id) { return (Entity*)*(uintptr_t*)((uintptr_t*)*((uintptr_t*)(modBase + 0x10F4F8)) + id); };

	//Setter
	void SetPos(Vector3 Pos) { *(Vector3*)(PlayerBase + 0x34) = Pos; }
	void SetViewAngles(Vector3 ViewAngles) { *(Vector3*)(PlayerBase + 0x40) = ViewAngles; }
	void SetHealth(int Health) { *(int*)(PlayerBase + 0xF8) = Health; }
	void SetArmor(int Armor) { *(int*)(PlayerBase + 0xFC) = Armor; }
	void SetAmmo(int Ammo) { *(int*)(PlayerBase + 0x148) = Ammo; }
	void SetGrenade(int Grenade) { *(int*)(PlayerBase + 0x158) = Grenade; }
	void SetTeam(int Team) { *(int*)(PlayerBase + 0x32C) = Team; }  // only 1 or 0 
	void SetPlayerSpeed(int Speed) { *(int*)(PlayerBase + 0x80) = Speed; }
	void SetPlayerState(int State) { *(int*)(PlayerBase + 0x82) = State; }  //free walk - 6 noclip - 4 normal - 0 
	void SetFOV(float FOV) { *(float*)(modBase + 0x10F1C4) = FOV; }
	void SetPlayerDead(bool State) { *(bool*)(PlayerBase + 0x338) = State; }
	void SetPlayerAttack(bool Attack) { *(bool*)(PlayerBase + 0x224) = Attack; }
	void SetUsername(char Name) { *(char*)(PlayerBase + 0x225) = Name; }

	//Other 
	Entity* GetClosestEnemy(bool team);

private:
	uintptr_t PlayerBase = NULL;
};

class cWeapon : Entity {
public:
	cWeapon() {
		if (modBase != NULL) {

		} else if (cWeaponObj == NULL && cWeaponInfoObj == NULL) {
			cWeaponObj = (GetLocalPlayer() + 0x374);
			cWeaponInfoObj = (cWeaponObj + 0x10);
		}
	}

	enum Guns { GUN_KNIFE = 0, GUN_PISTOL, GUN_CARBINE, GUN_SHOTGUN, GUN_SUBGUN, GUN_SNIPER, GUN_ASSAULT, GUN_GRENADE, GUN_AKIMBO };

	//Getter
	int GetWeaponId() { return *(int*)(cWeaponObj + 0x4); }
	int GetWeaponBullets() { return *(int*)(cWeaponInfoObj + 0x28); }
	int GetWeaponMag() { return *(int*)(cWeaponInfoObj); }
	int GetTotalShots() { return *(int*)(cWeaponInfoObj + 0x78); }

	//Setter
	void SetWeaponId(int Id) { *(int*)(cWeaponObj + 0x4) = Id; }
	void SetWeaponBullets(int Bullets) { *(int*)(cWeaponInfoObj + 0x28) = Bullets; }
	void SetWeaponMag(int Mag) { *(int*)(cWeaponInfoObj) = Mag; }
	void SetTotalShots(int Shots) { *(int*)(cWeaponInfoObj + 0x78) = Shots; }

private:
	uintptr_t cWeaponObj = NULL;
	uintptr_t cWeaponInfoObj = NULL;
};