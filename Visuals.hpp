#pragma once
#include "includes.hpp"

#include "Classes.hpp"
#include <sstream>



namespace Visuals
{

	

	
	void Hook(void)
	{


		if (Settings::Visuals::enable)
		{
			/*
			if (!FiveM::IsOnFiveM)
			{
				return;
			}
			*/
			hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(FiveM::ReplayInterface);
			if (!ReplayInterface)
				return;

			hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
			if (!PedInterface)
				return;

			for (int index = 0; index < PedInterface->PedMaximum(); index++)
			{
	            hk_Ped* Peds = PedInterface->PedList()->Ped(index);
                if (!Peds)
                    continue;

                if (LocalPlayer->GetHealth() <= 100) continue;

                if (!Settings::Visuals::Draw_Dead)
                {
                    if (Peds->GetHealth() <= 0) continue;
                }


                bool IsPed = false;
                auto ped_type = Peds->GetPedType();

                if (!ped_type)
                {
                    continue;
                }

                ped_type = ped_type << 11 >> 25;

                if (ped_type != 2) {
                    IsPed = true;
                }

                if (!Settings::Visuals::Draw_Ped) {

                    if (IsPed)
                    {
                        continue;
                    }

                }

                if (!Settings::Visuals::Draw_LocalPlayer) {

                    if (Peds == LocalPlayer)
                        continue;

                }

				ImVec2 Ped_Location = FiveM::WorldToScreen(Peds->GetCoordinate());
				if (!IsOnScreen(Ped_Location)) continue;

				ImVec2 LocalPlayer_Location = FiveM::WorldToScreen(LocalPlayer->GetCoordinate());

	

				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());

				double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

				if (Distance < Settings::Visuals::Distance)
				{
					ImVec2 Head = FiveM::GetBonePosMatrixW2S(reinterpret_cast<uint64_t>(Peds), 0);
					if (!IsOnScreen(Head)) continue;

					ImVec2 Left_Foot = FiveM::GetBonePosMatrixW2S(reinterpret_cast<uint64_t>(Peds), 3);
					if (!IsOnScreen(Left_Foot)) continue;

					ImVec2 Right_Foot = FiveM::GetBonePosMatrixW2S(reinterpret_cast<uint64_t>(Peds), 4);
					if (!IsOnScreen(Right_Foot)) continue;





					float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
					float Height = abs(Head.y - Foot_Middle) * 1.35f;
					float Width = (Height / (1.80f + Settings::Visuals::BoxSize / 100));


					if (Settings::Visuals::StaticESP)
					{
						Vector3 mins = Peds->PedModelInfo()->GetMin();
						Vector3 maxs = Peds->PedModelInfo()->GetMax();

						Vector3 min = (Peds->GetCoordinate() + mins);
						Vector3 max = (Peds->GetCoordinate() + maxs);
						Vector3 points[] = {
								Vector3(min.x, min.y, min.z),
								Vector3(min.x, max.y, min.z),
								Vector3(max.x, max.y, min.z),
								Vector3(max.x, min.y, min.z),
								Vector3(max.x, max.y, max.z),
								Vector3(min.x, max.y, max.z),
								Vector3(min.x, min.y, max.z),
								Vector3(max.x, min.y, max.z)
						};

						ImVec2 w2s_points[8];
						auto index = 0;
						for (Vector3 point : points) {
							w2s_points[index] = FiveM::WorldToScreen(point);
							if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
								continue;
							index++;
						}

						float x = w2s_points[0].x;
						float y = w2s_points[0].y;
						float width = w2s_points[0].x;
						float height = w2s_points[0].y;
						for (auto point : w2s_points) {
							if (x > point.x)
								x = point.x;
							if (width < point.x)
								width = point.x;
							if (y > point.y)
								y = point.y;
							if (height < point.y)
								height = point.y;
						}

						int out_x = x;
						int out_y = y;
						int out_w = width - x;
						int out_h = height - y;
						Height = out_h / 1.05;
						Width = out_w;

						Width = (Height / (1.80f  + Settings::Visuals::BoxSize/ 100));
						if (((Ped_Location.x + Width / 2) - (Ped_Location.x - Width / 2)) > 600)
							continue;
						
					}
					ImColor ColorCorner = Settings::Visuals::CornerColor;
		

					if (Settings::Visuals::Snapline)

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(FiveM::WindowSize.x / 2, 0), Ped_Location, ImColor(255, 255, 255, 255), 1.f);

					if (Settings::Visuals::Box)
					{
						ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), Settings::Visuals::BoxColor);

					}
					if (Settings::Visuals::Corner)
					{
						float CornerSize = (Width) / 4.f;
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), ColorCorner, 1);





					}
					if (Settings::Visuals::Box || Settings::Visuals::Corner)
					{


						if (Settings::Visuals::Filled)
						{
							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImColor(0, 0, 0, Settings::Visuals::FillBoxAlpha));
						}
					}



					if (Settings::Visuals::Skeleton)
					{

				                   	int bone_positions[][2] = {
		                    { 0, 7 },
	                        { 7, 6 },
                            { 7, 5 },
		                    { 7, 8 },
		                    { 8, 3 },
		                    { 8, 4 }
	                        };
                            uint64_t PedInt = reinterpret_cast<uint64_t>(Peds);

                            for (int i = 0; i < 6; ++i) {
                                auto Bone_1 = FiveM::GetBoneArrayW2SPos(PedInt,bone_positions[i][0]);
                                auto Bone_2 = FiveM::GetBoneArrayW2SPos(PedInt,bone_positions[i][1]);
                                ImGui::GetBackgroundDrawList()->AddLine(Bone_1,Bone_2, Settings::Visuals::SkelColor, 1.0f);

                            }
                         
					}

					if (Settings::Visuals::HealthBar && !IsPed)
					{
						//if (!IsPed)
						//{


							float HealthPercentage = Height / 100 * (Peds->GetHealth() - 100);
							float HealthPercentagee = Height / 100 * 100;

							float fixedhealth = Peds->GetHealth() / 2;
							float fixedhealthh = 100;

							ImColor	col = ImColor(81, 252, 141, 255);
							ImColor coll = ImColor(242, 0, 0, 255);

							float  caca = (Width) / 8.f;
							if (Distance < 20)
							{
								caca = (Width) / 12.f;
							}
							if (fixedhealth != 0)

							DrawHealthBar(ImVec2((Ped_Location.x + Width / 2), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) , Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

						//}
					}
					if (Settings::Visuals::ArmorBar && !IsPed)
					{
					
							float HealthPercentage = Height / 100 * (Peds->GetArmor());
							float HealthPercentagee = Height / 100 * 100;

							float fixedhealth = Peds->GetArmor();
							float fixedhealthh = 100;

							ImColor col = ImColor(10, 145, 255, 255);
							ImColor coll = ImColor(242, 0, 0, 255);

							float  caca = (Width) / 8.f;
							if (Distance < 20)
							{
								caca = (Width) / 12.f;
							}
							if(fixedhealth != 0)
							DrawHealthBar(ImVec2((Ped_Location.x - Width / 2), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) , Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);


					}
				
					if (Settings::Visuals::Weapon)
					{
						float font_size = 13.5;
						hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
						if (!PedsWeaponManager) continue;
						hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
						if (!PedsWeaponInfo) continue;
						uint64_t Hash = PedsWeaponInfo->GetHash();

						if (Distance <= 25)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 14.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 50 && Distance > 25)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 12.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 75 && Distance > 50)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 10.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 100 && Distance > 75)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 8.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 125 && Distance > 100)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 6.0f, ImColor(255, 255, 255), true);
						}
					}

				
			

					
					if (Settings::Visuals::tpped  || Settings::Visuals::killped || Settings::Visuals::invisibleped)
					{
						if (IsPed && Peds != LocalPlayer)
						{
							if (Settings::Visuals::tpped)
							{
								Peds->SetVelocity();
								DWORD64 addr = FiveM::GetCamera();
								if (addr)
								{
									Vector3 ActualPos = LocalPlayer->GetCoordinate();

									Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
									Vector3 newpos = ActualPos;
									newpos.x -= (TPSangles.x * 1);
									newpos.y -= (TPSangles.y * 1);
									newpos.z -= (TPSangles.z * 1);
									Peds->SetCoordinate(newpos);
								}
							}
							if (Settings::Visuals::invisibleped)
							{
								Peds->SetInvisible(0X37);
							}
							if (Settings::Visuals::killped)
							{
								Peds->SetHealth(0);
							
							}

						}

					}



					
				

						

					
					
				}
			}
			/*
			if (Settings::Player::SuperJump)
			{
				int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
				NativeInvoke::Invoke<0x57FFF03E423A4C0B, int>(player);
			}
			*/
		}
	}
}