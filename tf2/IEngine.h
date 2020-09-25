#pragma once

#include "m.h"
#include "structs.h"

struct player_info_t {
    char            name[32];
    int             userId;
    char            szSteamID[20];
    char            pad_0x00A8[0x10];
    unsigned long   iSteamID;
    char            szFriendsName[128];
    bool            FakePlayer;
    bool            IsHLTV;
    unsigned int    CustomFiles[4];
    unsigned char   FilesDownloaded;
};


class IEngine {
public:
    int GetLocalPlayer() {
        using GetLocalPlayer = int(__thiscall*)(void*);
        return method<GetLocalPlayer>(12, this)(this);
    }

    void GetPlayerInfo(int id, player_info_t* info) {
        using GetPlayerInfo = void(__thiscall*)(void*, int, player_info_t*);
        return method<GetPlayerInfo>(8, this)(this, id, info);
    }

    void GetScreenSize(int& x, int& y) {
        using GetScreenSize = void(__thiscall*)(void*, int&, int&);
        return method<GetScreenSize>(5, this)(this, x, y);
    }

    int GetMaxClients() noexcept {
        using GetMaxClients = int(__thiscall*)(void*);
        return method<GetMaxClients>(21, this)(this);
    }

    const matrix3x4_t& WorldToScreenMatrix() {
        using WorldToScreenMatrix = const matrix3x4_t & (__thiscall*)(void*);
        return method<WorldToScreenMatrix>(36, this)(this);
    }

    bool IsInGame() {
        using IsInGame = bool(__thiscall*)(void*);
        return method<IsInGame>(26, this)(this);
    }

};
