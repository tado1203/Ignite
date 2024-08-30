#include <Windows.h>
#include <iostream>

#include "Game/Offsets.h"
#include "Game/SDK/SDK.h"
#include "Hooks/DirectX/D3D11Hook.h"
#include "Module/ModuleManager.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "Libraries/freetype/freetype.lib")
#pragma comment(lib, "Libraries/minhook/libMinHook.x64.lib")

void Init()
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Ignite");

    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    Offsets::Init();
    SDK::Init();
    D3D11Hook::Init();
    ModuleManager::Init();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, 0);
    }

    return TRUE;
}