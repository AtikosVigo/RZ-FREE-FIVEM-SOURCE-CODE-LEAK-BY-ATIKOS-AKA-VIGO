#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include "Settings.hpp"

namespace Vehicule
{
	void Hook(void)
	{
		
		hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
		if (!World)
			return;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return;
	
			hk_Vehicle* Vehicle = LocalPlayer->VehicleManager();;
			if (!Vehicle)
				return;
			if (Vehicle->GetCoordinate().x == 0)
				return;

			if (Settings::vehicle::godmode)
			{
				Vehicle->Godmode(true);
			}
			

			if (Settings::vehicle::setmaxhealth)
			{
				Vehicle->SetEngineHealth(1000);
				Vehicle->SetBodyHealth(1000);
				Vehicle->SetHealth(Vehicle->GetMaxHealth());
				Settings::vehicle::setmaxhealth = false;
			}
			if (Settings::vehicle::Acceleration)
			{
				Vehicle->VehicleHandlingInfo()->SetAcceleration(Settings::vehicle::AccelerationSpeed);
			}


		
		
	}
}