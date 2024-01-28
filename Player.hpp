#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include "invoker.hpp"
namespace Players
{
	void Hook(void)
	{
	
			hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
			if (!LocalPlayer)
				return;


			if (Settings::Player::Semi_Godmod)
			{
				if (LocalPlayer->GetHealth() < 200)
					LocalPlayer->SetMaxHealth();
			}
			if (Settings::Player::Infinite_Armor)
			{
				LocalPlayer->SetArmor(Settings::Player::ArmorToSet);

			}

			if (Settings::Player::Godmod)
			{
				*(bool*)(LocalPlayer + 0x189) = true;
			}
			if (Settings::Player::fastrun)
			{
				LocalPlayer->PlayerInfo()->SetSpeed(Settings::Player::RunSpeedToSet);
			}
			if (Settings::Player::SuperJump)
			{
				LocalPlayer->PlayerInfo()->SetSuperJump(true);
			}
			if (Settings::Player::SetArmor)
			{
			//	PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(),100);
				Settings::Player::SetArmor = false;
			}
			if (Settings::Player::SetHealth)
			{
				LocalPlayer->SetHealth(100 + Settings::Player::HealthToSet);

				Settings::Player::SetHealth = false;
			}
			/*
			if (Settings::Player::NoRagDoll)
			{
				LocalPlayer->Set_Ragdoll(true);
			}
			else 
			{
				LocalPlayer->Set_Ragdoll(false);
			}*/

				
		
			if (Settings::Player::EnableFovChange)
			{
				DWORD64 addr = FiveM::GetCamera();
				uintptr_t CameraData = *(uintptr_t*)(addr + 0x10);
				*(float*)(CameraData + 0x30) = Settings::Player::FovValue;
				Settings::Player::EnableFovChange = false;
			//	std::cout << *(float*)(CameraData + 0x30);

			//	FiveM::SetFOVZoom(Settings::Player::FovValue);
			}



		


		
	}
}