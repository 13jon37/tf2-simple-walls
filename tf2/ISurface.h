#pragma once
#include "m.h"
#include <algorithm>
#include <cstdarg>
#include <stringapiset.h>

struct Color {
	int r, g, b, a;
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,		// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP = 0x800,		// compiled bitmap font - no fallbacks
};

namespace font {
	DWORD Arial = 0;
	DWORD Verdana = 0;
	DWORD Tahoma = 0;
}

class ISurface {
public:

	DWORD CreateFont() {
		using CreateFont = DWORD(__thiscall*)(void*);
		return method<CreateFont>(66, this)(this);
	}

	void SetFontGlyphSet(DWORD font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) noexcept {
		using SetFontGlyphSet = void(__thiscall*)(void*, DWORD, const char*, int, int, int, int, int, int, int);
		return method<SetFontGlyphSet>(67, this)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, NULL, NULL);
	}

	void DrawSetTextFont(DWORD font) {
		using DrawSetTextFont = void(__thiscall*)(void*, DWORD);
		return method<DrawSetTextFont>(17, this)(this, font);
	}

	void DrawSetTextColor(Color color) {
		using DrawSetTextColor = void(__thiscall*)(void*, Color);
		return method<DrawSetTextColor>(19, this)(this, color);
	}

	void DrawSetTextPos(int x, int y) {
		using DrawSetTextPos = void(__thiscall*)(void*, int, int);
		return method<DrawSetTextPos>(20, this)(this, x, y);
	}

	void DrawPrintText(const wchar_t* text, int textLen) {
		using DrawPrintText = void(__thiscall*)(void*, const wchar_t*, int, int);
		return method<DrawPrintText>(22, this)(this, text, textLen, 0);
	}

	void DrawString(unsigned long font, int x, int y, Color color, const char* text, ...) {
		if (text == 0) return;

		va_list va_alist;
		char szBuffer[1024] = { '\0' };
		wchar_t szString[1024] = { '\0' };

		va_start(va_alist, text);
		vsprintf_s(szBuffer, sizeof(szBuffer), text, va_alist);
		va_end(va_alist);

		wsprintfW(szString, L"%S", szBuffer);
		//MultiByteToWideChar(CP_UTF8, 0, szBuffer, -1, szString, 32);

		DrawSetTextColor(color);
		DrawSetTextFont(font);
		DrawSetTextPos(x, y);
		DrawPrintText(szString, wcslen(szString));
	}

};
