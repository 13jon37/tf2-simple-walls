#pragma once
#include "m.h"

class IPanel {
public:
	const char* GetName(unsigned int id) {
		using GetName = const char* (__thiscall*)(void*, unsigned int);
		return method<GetName>(36, this)(this, id);
	}

	void SetTopmostPopup(unsigned int id, bool state) {
		using SetTopmostPopup = void(__thiscall*)(void*, unsigned int, bool);
		return method<SetTopmostPopup>(59, this)(this, id, state);
	}
};
