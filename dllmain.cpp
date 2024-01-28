#include "Core.hpp"
#include "Classes.hpp"
#include <auth.hpp>
#include <Windows.h>
#include <process.h>

#include "invoker.hpp"
#include <MinHook.h>
#include <functional>
#include <stdint.h>
#include <unordered_set>
#include <Psapi.h>
#include "rage.hpp"
#pragma comment(lib, "ntdll.lib")
#pragma warning(disable : 6031)
#define PI           3.14159265358979323846  /* pi */

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef NTSTATUS(NTAPI* RtlCreateUserThread_t)(HANDLE, PSECURITY_DESCRIPTOR, BOOLEAN, ULONG, SIZE_T, SIZE_T, PTHREAD_START_ROUTINE, PVOID, PHANDLE, PCLIENT_ID);
RtlCreateUserThread_t RtlCreateUserThread = (RtlCreateUserThread_t)GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlCreateUserThread");
float degToRad(float deg)
{
	return deg * (PI / 180);
}

BOOLEAN APIENTRY DllMain(HINSTANCE hk_dll, DWORD hk_reason, LPVOID hk_lpReserved)
{
	UNREFERENCED_PARAMETER(hk_lpReserved);

	if (hk_reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hk_dll);
		if (DEBUG == 0)
		{
			typedef BOOL(__stdcall* AllocConsole_t)();
			AllocConsole_t AllocConsole_o = (AllocConsole_t)SAFE_CALL(GetProcAddress)(SAFE_CALL(GetModuleHandleA)((E("kernel32.dll"))), E("AllocConsole"));

			AllocConsole_o();
			freopen_s((FILE**)stdout, E("CONOUT$"), E("w"), stdout);
		}

		FiveM::ViewPort = Memory::PatternScan(E("48 8B 15 ?? ?? ?? ?? 48 8D 2D ?? ?? ?? ?? 48 8B CD"), NULL, 7);
		FiveM::World = Memory::PatternScan(E("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81"), NULL, 7);
		FiveM::ReplayInterface = Memory::PatternScan(E("48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 48 8B 9C 24"), NULL, 7);
		FiveM::Camera = Memory::PatternScan(E("48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"), NULL, 7);
		FiveM::Waypoint = Memory::PatternScan(E("4C 8D 05 ? ? ? ? 0F B7 C1"), NULL, NULL);
		FiveM::NativeSpoof = Memory::PatternScan(E("FF E3"), NULL, NULL);
		FiveM::pointer_to_handle = reinterpret_cast<FiveM::pizza_to_spaghetti_t>(Memory::PatternScan(E("48 8B F9 48 83 C1 10 33 DB"), NULL, NULL) - 0x15);
	        FiveM::handle_to_pointer = reinterpret_cast<FiveM::spaghetti_to_pizza_t>(Memory::PatternScan(E("83 F9 FF 74 31 4C 8B 0D"), NULL, NULL));



		FiveM::FiveM_2802 = false;
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2802_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2802_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x1098;
			FiveM::Armor = 0x150C; // -0x24
			FiveM::VehiculeManager = 0x0D10;
			FiveM::WeaponManager = 0x10B8;
			FiveM::PlayerInfo = 0x10A8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;

			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
			FiveM::FiveM_2802 = true;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2612_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2612_GTAProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GTAProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GameProcess.exe"))
		{
			FiveM::EntityType = 0x10B8;
			FiveM::Armor = 0x1530;
			FiveM::VehiculeManager = 0x0D30;

			FiveM::WeaponManager = 0x10D8;
			FiveM::PlayerInfo = 0x10C8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;
			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2545_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2545_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x10B8;
			FiveM::Armor = 0x14E0 + 0x50;
			FiveM::VehiculeManager = 0x0D30;

			FiveM::WeaponManager = 0x10D8;
			FiveM::PlayerInfo = 0x10C8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;
			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2372_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2372_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x10B8;
			FiveM::Armor = 0x14E0;
			FiveM::VehiculeManager = 0x0D30;
			FiveM::WeaponManager = 0x10D8;
			FiveM::PlayerInfo = 0x10C8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;
			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2189_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2189_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x10B8;
			FiveM::Armor = 0x14E0;
			FiveM::VehiculeManager = 0x0D30;
			FiveM::WeaponManager = 0x10D8;
			FiveM::PlayerInfo = 0x10C8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::EngineHealth = 0x908;
			FiveM::AmmoExplosiveType = 0x24;
			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_b2060_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2060_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x10B8;
			FiveM::Armor = 0x14E0;
			FiveM::VehiculeManager = 0x0D30;
			FiveM::WeaponManager = 0x10D8;
			FiveM::PlayerInfo = 0x10B8;
			FiveM::Recoil = 0x2F4;
			FiveM::Spread = 0x84;
			FiveM::ReloadMultiplier = 0x134;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;

			FiveM::WeaponName = 0x5F0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)("FiveM_GameProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_GTAProcess.exe"))
		{
			FiveM::EntityType = 0x10A8;
			FiveM::Armor = 0x14B8;
			FiveM::VehiculeManager = 0x0D30;
			FiveM::WeaponManager = 0x10C8;
			FiveM::PlayerInfo = 0x10B8;

			FiveM::Recoil = 0x2E8;
			FiveM::Spread = 0x74;
			FiveM::ReloadMultiplier = 0x12C;
			FiveM::AmmoType = 0x20;
			FiveM::AmmoExplosiveType = 0x24;
			FiveM::WeaponName = 0x5E0;
			FiveM::IsInAVehicule = 0x146B;
			FiveM::Range = 0x25C;
		}

		//RtlCreateUserThread(((HANDLE)(LONG_PTR)-1), 0, 0, 0, 0, 0, (PTHREAD_START_ROUTINE)SetUrThings, 0, 0, 0);
	//    std::cout << "\n Hooked thread !" << std::endl;

		SAFE_CALL(_beginthreadex)(0, 0, (_beginthreadex_proc_type)Core::Init, 0, 0, 0);
	}

	return TRUE;
}