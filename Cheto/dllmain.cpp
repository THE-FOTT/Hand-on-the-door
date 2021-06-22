#include "pch.h"
#include <thread>

void AddMessage(const char* text, unsigned int time, unsigned short flag, bool bPreviousBrief)
{
    ((void(__cdecl*)(const char*, unsigned int, unsigned short, bool))0x69F1E0)(text, time, flag, bPreviousBrief);
}

void InitializeAndLoad() {
    while (*reinterpret_cast<unsigned char*>(0xC8D4C0) != 9) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100u));
    }
    AddMessage("~g~~h~~h~~h~By FooOoott", 3000, 0, false);
    unsigned char patch[]{ 0xE9, 0x36, 0x01, 0x00, 0x00, 0x90 };
    memset(reinterpret_cast<void*>(0x642E93), 0x90, 0x06);
    memset(reinterpret_cast<void*>(0x642EEE), 0x90, 0x02);
    memset(reinterpret_cast<void*>(0x642AF4), 0x90, 0x06);
    memmove(reinterpret_cast<void*>(0x642BF5), patch, 0x06);
    memset(reinterpret_cast<void*>(0x642BE2), 0x90, 0x06);
    
    
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        std::thread(InitializeAndLoad).detach();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}