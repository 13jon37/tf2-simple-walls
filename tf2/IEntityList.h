#pragma once

#include "m.h"

class IEntityList {
public:
	void* GetClientEntity(int id) {
		using GetClientEntity = void* (__thiscall*)(void*, int);
		return method<GetClientEntity>(3, this)(this, id);
	}

	void* GetClientEntityFromHandle(int handle) {
		using GetClientEntityFromHandle = void* (__thiscall*)(void*, int);
		return method<GetClientEntityFromHandle>(4, this)(this, handle);
	}

	int GetHighestEntityIndex() {
		using GetHighestEntityIndex = int(__thiscall*)(void*);
		return method<GetHighestEntityIndex>(8, this)(this);
	}
};
