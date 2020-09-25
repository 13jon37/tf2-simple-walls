// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <cstdio>
#include <thread>

#include "m.h"
#include "Interfaces.h"
#include "ISurface.h"
#include "CBaseEntity.h"
#include "IEntityList.h"
#include "structs.h"

#include "minihook/include/MinHook.h"
#include "utils.h"

#pragma comment(lib, "libMinHook.x86.lib")

Color Red{ 255,0,0,255 };
Color White{ 255,255,255,255 };
Color Yellow{ 252, 252, 111, 255 };
Color Green{ 10, 252, 30, 255 };
Color Blue{ 10, 98, 252, 255 };
Color Orange{ 232, 142, 6, 255 };

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

using reT = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
reT ohkPaintTraverse = nullptr;

bool esp = false;
bool menu = true;

void nameEsp() {
    if (Interfaces::engine->IsInGame()) {
        for (size_t i = 1; i <= Interfaces::engine->GetMaxClients(); i++) {

            CBaseEntity* entity = (CBaseEntity*)Interfaces::entitylist->GetClientEntity(i);
            CBaseEntity* local = (CBaseEntity*)Interfaces::entitylist->GetClientEntity(Interfaces::engine->GetLocalPlayer());

            if (entity && !entity->m_bDormant() && entity->IsAlive()) {
                if (entity == local) continue;

                Vector head, feet;
                Vector posFeet = entity->GetPosition();
                Vector posHead = posFeet;
                posHead.z += 72.f;

                if (utils::WorldToScreen(posFeet, feet) && utils::WorldToScreen(posHead, head)) {

                    float width = abs(head.y - feet.y) * .3f;

                    player_info_t info;
                    Interfaces::engine->GetPlayerInfo(i, &info);

                    if (entity->m_iTeamNum() != local->m_iTeamNum()) {
                        Interfaces::surface->DrawString(font::Arial, feet.x - 30, feet.y, Red, "%s", info.name);
                    }
                    else {
                        Interfaces::surface->DrawString(font::Arial, feet.x - 30, feet.y, Green, "%s", info.name);
                    }

                    Interfaces::surface->DrawString(font::Arial, feet.x, feet.y + 15, White, "%i", entity->GetHealth());
                }
            }
        }
    }
}

void __stdcall hkPaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce)
{
    ohkPaintTraverse(Interfaces::panel, panel, forceRepaint, allowForce);
    
    static unsigned int OverlayPanel;
    if (OverlayPanel == NULL)
    {
        const char* szName = Interfaces::panel->GetName(panel);
       // printf("% s\n", szName);
        if (!strcmp(szName, "FocusOverlayPanel")) {
            font::Arial = Interfaces::surface->CreateFontW();
            Interfaces::surface->SetFontGlyphSet(font::Arial, "Arial", 12, 600, 0, 0, FONTFLAG_OUTLINE);
            font::Verdana = Interfaces::surface->CreateFontW();
            Interfaces::surface->SetFontGlyphSet(font::Verdana, "Verdana", 16, 600, 0, 0, FONTFLAG_OUTLINE);

            OverlayPanel = panel;
        }
    }
    if (panel == OverlayPanel) {
        Interfaces::panel->SetTopmostPopup(OverlayPanel, true);

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            menu = !menu;
        }

        if (menu) {
            player_info_t info;

            Interfaces::surface->DrawString(font::Verdana, 50, 65, White, "x66Cheats.com");
            Interfaces::surface->DrawString(font::Verdana, 50, 80, White, "Hello");

            if (Interfaces::engine->IsInGame()) {
                Interfaces::engine->GetPlayerInfo(Interfaces::engine->GetLocalPlayer(), &info);
                char* playerName = info.name;

                Interfaces::surface->DrawString(font::Verdana, 90, 80, Yellow, "%s", playerName);
            }
            else {
                Interfaces::surface->DrawString(font::Verdana, 90, 80, Yellow, "User");
            }
            
            if (Interfaces::engine->IsInGame()) {
                Interfaces::surface->DrawString(font::Verdana, 50, 95, White, "[F1] Esp: ");

                if (GetAsyncKeyState(VK_F1) & 1) {
                    esp = !esp;
                }

                if (esp) {
                    Interfaces::surface->DrawString(font::Verdana, 125, 95, Blue, "On");
                    nameEsp();
                }
                else {
                    Interfaces::surface->DrawString(font::Verdana, 125, 95, Red, "Off");
                }
            }
        } 
    }
}

DWORD WINAPI Init(HMODULE hModule)
{
   // AllocConsole();
   // SetConsoleTitle(L"Team Fortress 2");
   // FILE* fp;
    //freopen_s(&fp, "CONOUT$", "w", stdout);

    MH_Initialize();

    MH_CreateHook((void*)get_virtual(Interfaces::panel, 41), &hkPaintTraverse, (void**)&ohkPaintTraverse);
    MH_EnableHook(MH_ALL_HOOKS);

    while (!GetAsyncKeyState(VK_F8)){
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    
    MH_Uninitialize();
  
   // fclose(fp);
   // FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

