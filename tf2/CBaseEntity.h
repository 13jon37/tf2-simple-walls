#pragma once

#include <Windows.h>
#include "structs.h"

enum lifeStates {
	LIFE_ALIVE = 0,
	LIFE_DEAD = 2
};

enum EntityFlags
{
	FL_ONGROUND = (1 << 0), 	// At rest / on the ground
	FL_DUCKING = (1 << 1),		// Player flag -- Player is fully crouched
	FL_WATERJUMP = (1 << 2),	// player jumping out of water
	FL_ONTRAIN = (1 << 3),		// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
	FL_INRAIN = (1 << 4),		// Indicates the entity is standing in rain
	FL_FROZEN = (1 << 5),		// Player is frozen for 3rd person camera
	FL_ATCONTROLS = (1 << 6),	// Player can't move, but keeps key inputs for controlling another entity
	FL_CLIENT = (1 << 7),		// Is a player
	FL_FAKECLIENT = (1 << 8),	// Fake client, simulated server side; don't send network messages to them
	FL_INWATER = (1 << 10),		// In water
};

class CBaseEntity {
public:
	bool IsAlive() {
		return GetHealth() > 0 && GetLifeState() == LIFE_ALIVE;
	}

	//m_iHealth
	int GetHealth() {
		return *reinterpret_cast<int*>((DWORD)this + 0xA8);
	}

	//m_vecOrigin
	Vector GetPosition() {
		return *reinterpret_cast<Vector*>((DWORD)this + 0x364);
	}

	//m_liftState
	BYTE GetLifeState() {
		return *reinterpret_cast<BYTE*>((DWORD)this + 0xA5);
	}

	int m_iTeamNum() {
		return *reinterpret_cast<int*>((DWORD)this + 0xB0);
	}

	bool m_bDormant() {
		return *reinterpret_cast<bool*>((DWORD)this + 0x1AA);
	}
};
