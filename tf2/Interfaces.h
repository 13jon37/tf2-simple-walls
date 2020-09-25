#pragma once
#include <Windows.h>
#include "IPanel.h"
#include "ISurface.h"
#include "IEngine.h"
#include "IEntityList.h"
#include "IClient.h"

void* CaptureInterface(const char* module_name, const char* interface_name)
{
    auto create_interface_fn = reinterpret_cast<void* (*)(const char* pName, int* pReturnCode)>(GetProcAddress(GetModuleHandleA(module_name), "CreateInterface"));
    return create_interface_fn(interface_name, nullptr);
}

namespace Interfaces {
    IClient* client = reinterpret_cast<IClient*>(CaptureInterface("client.dll", "VClient017"));
    IPanel* panel = reinterpret_cast<IPanel*>(CaptureInterface("vgui2.dll", "VGUI_Panel009"));
    ISurface* surface = reinterpret_cast<ISurface*>(CaptureInterface("vguimatsurface.dll", "VGUI_Surface030"));
    IEngine* engine = reinterpret_cast<IEngine*>(CaptureInterface("engine.dll", "VEngineClient014"));
    IEntityList* entitylist = reinterpret_cast<IEntityList*>(CaptureInterface("client.dll", "VClientEntityList003"));
};
