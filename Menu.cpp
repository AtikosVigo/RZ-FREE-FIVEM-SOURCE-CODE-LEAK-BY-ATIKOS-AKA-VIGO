#include "Menu.hpp"

#include "includes.hpp"
#include "Settings.hpp"
#include <Fonts.hpp>
#include "imgui_animated.h"
#include <imguinotify.hpp>
#include <ImGui_Anim.hpp>
#include <Lists.hpp>
#define MAX_RGB 255.0
#define HELPMARKER(str) ImGui::SameLine(); ImGui::TextColored(ImColor(220, 190, 0, 255), "(?)"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)


ImVec4 ToVec4(float r, float g, float b, float a)
{
	return ImVec4(r / MAX_RGB, g / MAX_RGB, b / MAX_RGB, a / MAX_RGB);
}

static ImVec4 active = ToVec4(252, 123, 3, 175);
static ImVec4 inactive = ToVec4(125, 125, 125, 85);

void CenterTextEx(const char* text, float width, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();

}
void CenterText(const char* text, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();
}

void Menu::Style(void)
{
    ImGuiStyle* Style = &ImGui::GetStyle();
    ImVec4* Colors = Style->Colors;

    Style->WindowBorderSize = 0;
    Style->ChildRounding = 3;
    Style->FrameRounding = 0;
    Style->ScrollbarRounding = 0;
    Style->GrabRounding = 0;
    Style->PopupRounding = 3;
    Style->WindowRounding = 3;
    Style->ItemSpacing = ImVec2(-30, -30);

    Colors[ImGuiCol_Border] = ImVec4(ImColor(255, 255, 255, 0));
    Colors[ImGuiCol_WindowBg] = ImVec4(ImColor(10, 10, 10, 255));
    Colors[ImGuiCol_ChildBg] = ImVec4(ImColor(20, 20, 20, 175));
    Colors[ImGuiCol_Text] = ImVec4(ImColor(255, 255, 255, 255));
    Colors[ImGuiCol_Separator] = ImVec4(ImColor(45, 45, 45, 135));
    Colors[ImGuiCol_CheckMark] = ImVec4(ImColor(2, 106, 191, 175));
    Colors[ImGuiCol_PopupBg] = ImVec4(ImColor(20, 20, 20, 175));
    Colors[ImGuiCol_Button] = ImVec4(ImColor(33, 33, 33, 255));
    Colors[ImGuiCol_ButtonActive] = ImVec4(ImColor(48, 48, 48, 255));
    Colors[ImGuiCol_ButtonHovered] = ImVec4(ImColor(43, 43, 43, 255));
    //Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    //Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    //Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);

    Colors[ImGuiCol_FrameBg] = ImVec4(ImColor(20, 20, 20, 255));
    Colors[ImGuiCol_FrameBgHovered] = ImVec4(ImColor(33, 32, 32, 255));
    Colors[ImGuiCol_FrameBgActive] = ImVec4(ImColor(28, 28, 28, 255));


    Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

    Colors[ImGuiCol_Separator] = Colors[ImGuiCol_Border];
    Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 0.00f);
    Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0);
    Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0);
    Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0);
    Colors[ImGuiCol_Tab] = ImLerp(Colors[ImGuiCol_Header], Colors[ImGuiCol_TitleBgActive], 0.80f);
    Colors[ImGuiCol_TabHovered] = Colors[ImGuiCol_HeaderHovered];
    Colors[ImGuiCol_TabActive] = ImLerp(Colors[ImGuiCol_HeaderActive], Colors[ImGuiCol_TitleBgActive], 0.60f);
    Colors[ImGuiCol_TabUnfocused] = ImLerp(Colors[ImGuiCol_Tab], Colors[ImGuiCol_TitleBg], 0.80f);
    Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(Colors[ImGuiCol_TabActive], Colors[ImGuiCol_TitleBg], 0.40f);
    Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
    Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
    Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
struct selection_anim
{
    int hovered_anim;
    int active_anim;
};
bool subtab(const char* label, bool selected) {
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImGuiID id = window->GetID(label);

    ImVec2 p = window->DC.CursorPos;
    ImVec2 size({ ImGui::CalcTextSize(label, 0, true).x + 10, window->Size.y });
    ImRect bb(p, { p.x + size.x, p.y + size.y });

    ImGui::ItemSize(bb);
    ImGui::ItemAdd(bb, id);

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    float anim = ImTricks::Animations::FastFloatLerp(std::string(label).append("subtab.anim"), selected, 0.f, 1.f, 0.04f);
    auto col = ImTricks::Animations::FastColorLerp(ImGui::GetColorU32(ImGuiCol_TextDisabled), ImGui::GetColorU32(active), anim);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(active)));
    window->DrawList->AddRectFilled({ bb.Min.x + 4, bb.Max.y - 2 }, ImVec2(bb.Max.x- 4,bb.Max.y), ImGui::GetColorU32(ImGuiCol_Text, anim), 2, ImDrawFlags_RoundCornersTop);
    ImGui::PopStyleColor();
    ImGui::PushStyleColor(ImGuiCol_Text, col.Value);
    ImGui::RenderText(ImVec2(bb.GetCenter().x - ImVec2(ImGui::CalcTextSize(label, 0, true).x / 2, ImGui::CalcTextSize(label, 0, true).y / 2).x, bb.GetCenter().y - ImVec2(ImGui::CalcTextSize(label, 0, true).x / 2, ImGui::CalcTextSize(label, 0, true).y / 2).y), label);
    ImGui::PopStyleColor();

    return pressed;
}

static ImVec2 WindowPos;
void Menu::Drawing(void)
{
    ImGui::SetNextWindowSize(ImVec2(700 * 1.1, 510 * 1.1));

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::SetNextWindowBgAlpha(1.0f);


    if (ImGui::Begin("MENU", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
    {
        ImVec2 CursorPos = ImGui::GetCursorScreenPos();
        WindowPos = CursorPos;
        ImGui::BeginChild("##TopBar", ImVec2(ImGui::GetContentRegionAvail().x, 70), true, ImGuiWindowFlags_NoScrollbar);
        {

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetContentRegionAvail().y / 2.5);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8);
            ImGui::PushFont(BiggestFont);
            ImGui::Text("ATI");
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
            ImGui::Text("KOS");
            ImGui::PopStyleColor();
            if (Menu::Tab == 6)
            {
                ImGui::SameLine();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetContentRegionAvail().y / 2.5);

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15);
                ImGui::BeginChild("subtabs", { ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - 20, 50 }, 1);
                {
                    ImGui::SetCursorPos({ 16, 0 });

                    if (subtab("Player List##subtab", Menu::SubTab == 0))  Menu::SubTab = 0; ImGui::SameLine(0, 20);
                    if (subtab("Vehicle List##subtab", Menu::SubTab == 1))  Menu::SubTab = 1; ImGui::SameLine(0, 20);
                    if (subtab("Object List##subtab", Menu::SubTab == 2))  Menu::SubTab = 2;
                    ImGui::EndChild();

                }

            }
          
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x / 2.25);

            if (Menu::Tab == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("AIM"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("BOT"));
            }
            else if (Menu::Tab == 1)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("VISU"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("ALS"));
            }
            else if (Menu::Tab == 2)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("PLA"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("YER"));
            }
            else if (Menu::Tab == 3)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("VEHI"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("CLE"));
            }
            else if (Menu::Tab == 4)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("WEA"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("PON"));
            }
            else if (Menu::Tab == 5)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active));
                ImGui::Text(E("MI"));
                ImGui::SameLine();
                ImGui::PopStyleColor();

                ImGui::Text(E("SC"));
            }
            ImGui::PopFont();

        }
        ImGui::EndChild();

        ImGui::BeginChild(E("##LeftSide"), ImVec2(75, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 40);

            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 0 ? active : inactive);
            CenterTextEx(ICON_FA_BULLSEYE, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 0;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 1 ? active : inactive);
            CenterTextEx(ICON_FA_STREET_VIEW, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 1;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 2 ? active : inactive);
            CenterTextEx(ICON_FA_USER, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 2;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 3 ? active : inactive);
            CenterTextEx(ICON_FA_CAR, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 3;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 4 ? active : inactive);
            CenterTextEx(ICON_FA_FIGHTER_JET, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 4;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 5 ? active : inactive);
            CenterTextEx(ICON_FA_COGS, 80.3, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 5;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 6 ? active : inactive);
            CenterTextEx(ICON_FA_BARS, 75, 0, 0);
            if (ImGui::IsItemClicked()) Menu::Tab = 6;
    

            ImGui::PopStyleColor(7);
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);

        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(45, 45, 45, 135)));

        /// AIMBOT ///
        if (Menu::Tab == 6)
        {
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(45, 45, 45, 135)));
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
            ImGui::BeginChild(E("##MainBar"), ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
         
                ImGui::EndChild();

            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
        }
        if (Menu::Tab == 0)
        {
            ImGui::BeginChild(E("##MainBar"), ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text(E("Aim assistance"));
                ImGui::PopStyleColor();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Separator();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::PushFont(littleFont);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);
                ImGui::Checkbox(E(" Enable Aimbot"), &Settings::Aimbot::Aimbot);
          
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Draw Fov"), &Settings::Aimbot::Draw_Fov);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Draw Crosshair"), &Settings::Aimbot::crosshair);
                //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                //ImGui::Checkbox(" Preview Target", &Settings::Aimbot::PreviewTarget);
  

                ImGui::PushItemWidth(195);

                ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
            }

            ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

            ImGui::BeginChild(E("##TwoBar"), ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text(E("Aim settings"));
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::PopStyleColor();
                ImGui::Separator();
                ImGui::PushFont(littleFont);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::PushItemWidth(210);
                ImGui::SliderInt(E("Fov"), &Settings::Aimbot::AimbotFov, 1, 600, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt(E("Smooth"), &Settings::Aimbot::AimbotSmooth, 1, 30, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt(E("Distance"), &Settings::Aimbot::DistanceAimbotLimit, 1, 1000, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::Hotkey(E("##aimbot_key"), &Settings::Aimbot::Hotkey);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::Combo(E("Aimbot Target"), &Settings::Aimbot::TypeOfTarget, Settings::Aimbot::AimbotTarget, IM_ARRAYSIZE(Settings::Aimbot::AimbotTarget), ImGuiComboFlags_NoArrowButton);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                if (ImGui::Combo(E("Aimbot Type"), &Settings::Aimbot::AimbotTypes, Settings::Aimbot::AimbotType, IM_ARRAYSIZE(Settings::Aimbot::AimbotType), ImGuiComboFlags_NoArrowButton))
                {
                    if (Settings::Aimbot::AimbotTypes == 3)
                    {
                        Settings::Aimbot::enablemagic = true;
                    }
                    if (Settings::Aimbot::AimbotTypes == 2)
                    {
                        Settings::Aimbot::enablesilent = true;
                    }
                    if (Settings::Aimbot::AimbotTypes == 1)
                    {
                        Settings::Aimbot::enablemouseormemory = true;
                    }
                    if (Settings::Aimbot::AimbotTypes == 0)
                    {
                        Settings::Aimbot::enablemouseormemory = true;
                    }
             

                }

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::Combo(E("Aim Bone"), &Settings::Aimbot::AimbotBone, Settings::Aimbot::AimbotBones, IM_ARRAYSIZE(Settings::Aimbot::AimbotBones), ImGuiComboFlags_NoArrowButton);
    
            }
            ImGui::PopFont(); ImGui::EndChild();
        }

        /// VISUAL ///

        else if (Menu::Tab == 1)
        {

            ImGui::BeginChild(E("##MainBar"), ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text(E("Visuals assistance"));
                ImGui::PopStyleColor();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Separator();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::PushFont(littleFont);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);

                ImGui::Checkbox(E(" Enable ESP"), &Settings::Visuals::enable);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable Box"), &Settings::Visuals::Box);
                if (Settings::Visuals::Box)
                {
                    ImGui::SameLine();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 195.f - ImGui::CalcTextSize(E(" Enable aimbot")).x);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
                    ImGui::ColorEdit4(E("Box Color"), Settings::TempColor::Box, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
                    ImGui::PopStyleVar();
                }
                Settings::Visuals::BoxColor.Value.x = Settings::TempColor::Box[0];
                Settings::Visuals::BoxColor.Value.y = Settings::TempColor::Box[1];
                Settings::Visuals::BoxColor.Value.z = Settings::TempColor::Box[2];
                Settings::Visuals::BoxColor.Value.w = Settings::TempColor::Box[3];
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable Corner Box"), &Settings::Visuals::Corner);
                if (Settings::Visuals::Corner)
                {


                    ImGui::SameLine();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 175.f - ImGui::CalcTextSize(E(" Enable Corner Box")).x);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
                    ImGui::ColorEdit4(E("Corner Color"), Settings::TempColor::Corner, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
                    ImGui::PopStyleVar();
                }
                Settings::Visuals::CornerColor.Value.x = Settings::TempColor::Corner[0];
                Settings::Visuals::CornerColor.Value.y = Settings::TempColor::Corner[1];
                Settings::Visuals::CornerColor.Value.z = Settings::TempColor::Corner[2];
                Settings::Visuals::CornerColor.Value.w = Settings::TempColor::Corner[3];

                if (Settings::Visuals::Box || Settings::Visuals::Corner)
                {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                    ImGui::Checkbox(E(" Fill Box"), &Settings::Visuals::Filled);
     

                }                   
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable Skeleton"), &Settings::Visuals::Skeleton);
                if (Settings::Visuals::Skeleton)
                {
                    ImGui::SameLine();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 175.f - ImGui::CalcTextSize(E(" Enable Skeleton")).x);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
                    ImGui::ColorEdit4(E("Skeleton Color"), Settings::TempColor::Skeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
                    ImGui::PopStyleVar();
                }
                Settings::Visuals::SkelColor.Value.x = Settings::TempColor::Skeleton[0];
                Settings::Visuals::SkelColor.Value.y = Settings::TempColor::Skeleton[1];
                Settings::Visuals::SkelColor.Value.z = Settings::TempColor::Skeleton[2];
                Settings::Visuals::SkelColor.Value.w = Settings::TempColor::Skeleton[3];
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable HealthBar"), &Settings::Visuals::HealthBar);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable ArmorBar"), &Settings::Visuals::ArmorBar);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable snapline"), &Settings::Visuals::Snapline);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable Weapon Name"), &Settings::Visuals::Weapon);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Enable Player Name"), &Settings::Visuals::PlayerName);



                ImGui::PushItemWidth(195);

                ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
            }
            ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

            ImGui::BeginChild(E("##TwoBar"), ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text(E("Visuals settings"));
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::PopStyleColor();
                ImGui::Separator();
                ImGui::PushFont(littleFont);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::PushItemWidth(210);
                ImGui::SliderInt(E("Distance"), &Settings::Visuals::Distance, 1, 1000, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt(E("FillBox Alpha"), &Settings::Visuals::FillBoxAlpha, 1, 255, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Draw dead player"), &Settings::Visuals::Draw_Dead);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Draw localplayer"), &Settings::Visuals::Draw_LocalPlayer);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Draw ped"), &Settings::Visuals::Draw_Ped);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Preview ESP"), &Settings::Visuals::PreviewEsp);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(E(" Static ESP"), &Settings::Visuals::StaticESP);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::Combo(E("HealthBar Style"), &Settings::Visuals::HealthBar_idx, Settings::Visuals::HealthbarStyle, IM_ARRAYSIZE(Settings::Visuals::HealthbarStyle), ImGuiComboFlags_NoArrowButton);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt("Box size :", &Settings::Visuals::BoxSize, 0, 30, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
    

                ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();

            }
        }

        /// PLAYER

        else if (Menu::Tab == 2)
        {

            ImGui::BeginChild("##MainBar", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text("Player assistance");
                ImGui::PopStyleColor();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Separator();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::PushFont(littleFont);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);
                ImGui::Checkbox(" Enable Godmod", &Settings::Player::Godmod);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(" Enable Semi-Godmod", &Settings::Player::Semi_Godmod);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(" Enable Auto Armor", &Settings::Player::Infinite_Armor);
            //    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.5f);
             //   ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
             //   ImGui::Checkbox(" Enable FastRun", &Settings::Player::fastrun);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                ImGui::Checkbox(" Enable Noclip", &Settings::Player::NoClip);

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);

                if (ImGui::Button("Set Armor", ImVec2(ImGui::GetContentRegionAvail().x / 2 - 22.5f, 23)))
                {
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, " :)" });

                    Settings::Player::SetArmor = true;
                }

                ImGui::SameLine();

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22.5f);
                if (ImGui::Button("Set Health", ImVec2(ImGui::GetContentRegionAvail().x - 22.5f, 23)))
                {
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, " :)" });

                    Settings::Player::SetHealth = true;
                }
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
                if (ImGui::Button(" Change Fov", ImVec2(ImGui::GetContentRegionAvail().x - 22.5f, 23)))
                {
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, " can be detected by screenshot :)" });

                    Settings::Player::EnableFovChange = true;
                }


                ImGui::PushItemWidth(195);

                ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
            }

            ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

            ImGui::BeginChild("##TwoBar", ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::Text("Player settings");
                ImGui::PopStyleColor();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt("Armor to set :", &Settings::Player::ArmorToSet, 1, 100, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderInt("Health to set :", &Settings::Player::HealthToSet, 1, 100, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
            //    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            //    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
             //   ImGui::SliderInt("Run Speed Multiplier :", &Settings::Player::RunSpeedToSet, 1, 100, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
                ImGui::SliderFloat("Fov Value :", &Settings::Player::FovValue, 50, 160, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);

                ImGui::Separator();
            }
            ImGui::EndChild();
        }

        /// VEHICLE

        else if (Menu::Tab == 3)
        {

        ImGui::BeginChild("##MainBar", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Vehicle assistance");
            ImGui::PopStyleColor();

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Separator();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::PushFont(littleFont);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);
          //  ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
          //  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable Godmode", &Settings::vehicle::godmode);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            if (ImGui::Button("Repair"))
            {
                Settings::vehicle::setmaxhealth = true;
            }
            ImGui::PushItemWidth(195);

            ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
        }

        ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

        ImGui::BeginChild("##TwoBar", ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Vehicle settings");
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Separator();
        }
        ImGui::EndChild();
        }
    
        /// WEAPON

        else if (Menu::Tab == 4)
        {

        ImGui::BeginChild("##MainBar", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Weapon assistance");
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Separator();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::PushFont(littleFont);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);
            ImGui::Checkbox(" Enable Weapon Option", &Settings::Weapon::enable);

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable No Recoil", &Settings::Weapon::No_Recoil);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable No Spread", &Settings::Weapon::No_Spread);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable Infinite Ammo", &Settings::Weapon::InfiniteAmmo);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable No Reload", &Settings::Weapon::NoReload);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable No Range limit", &Settings::Weapon::NoRangeLimit);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            ImGui::Checkbox(" Enable DoubleTab", &Settings::Weapon::DoubleTap);
         //   ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.5f);
          //  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
          //  ImGui::Checkbox(" Enable Explosive Ammo", &Settings::Weapon::ExplosiveAmmo);

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.5f);
            if (ImGui::Button("Set Ammo", ImVec2(250, 30)))
            {

                if (!Settings::Weapon::enable)
                {
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Please Enable Weapon Option :)" });

                }
                else
                {
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, ":)" });

                }

                Settings::Weapon::SetAmmo = true; 
            }



            ImGui::PushItemWidth(195);

            ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
        }

        ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

        ImGui::BeginChild("##TwoBar", ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Weapon settings");
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SliderInt("Ammo to set :", &Settings::Weapon::AmmoToSet, 1, 999, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SliderInt("Bullet To Shoot :", &Settings::Weapon::BulletToShot, 1, 50, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
            ImGui::Separator();
        }
        ImGui::EndChild();
        }

        /// Misc

        else if (Menu::Tab == 5)
        {

        ImGui::BeginChild("##MainBar", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Misc option");
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Separator();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::PushFont(littleFont);
           ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.5f);
            ImGui::Checkbox(" Enable TP Zombie", &Settings::Visuals::tpped);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Checkbox(" Invisible Zombie", &Settings::Visuals::invisibleped);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Checkbox(" Kill Zombie", &Settings::Visuals::killped);



            ImGui::PushItemWidth(195);

            ImGui::PopItemWidth(); ImGui::PopFont(); ImGui::EndChild();
        }

        ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

        ImGui::BeginChild("##TwoBar", ImVec2(ImGui::GetContentRegionAvail().x - 15, ImGui::GetContentRegionAvail().y - 15), true, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Text("Misc settings");
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::Hotkey("Noclip Forward", &Settings::Player::ForwardHotkey);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 12.f);
            ImGui::Hotkey("Noclip Backward", &Settings::Player::BackwardHotkey);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 12.f);
            ImGui::Hotkey("Noclip Left", &Settings::Player::LeftHotkey);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 12.f);
            ImGui::Hotkey("Noclip Right", &Settings::Player::RightHotkey);
            ImGui::Separator();
        }
        ImGui::EndChild();
        }

        ImGui::GetWindowDrawList()->AddLine(ImVec2(CursorPos.x + 76, CursorPos.y), ImVec2(CursorPos.x + 76, CursorPos.y + ImGui::GetWindowHeight() + 1), ImColor(45, 45, 45, 135), 2.f);
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(CursorPos.x + 77, CursorPos.y), ImVec2(CursorPos.x + 77, CursorPos.y + ImGui::GetWindowHeight() + 4), ImColor(0, 0, 0, 20), 1);
        ImGui::GetWindowDrawList()->AddLine(ImVec2(CursorPos.x + 77, CursorPos.y + 71), ImVec2(CursorPos.x + ImGui::GetWindowWidth(), CursorPos.y + 71), ImColor(45, 45, 45, 135), 2.f);
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(CursorPos.x + 77, CursorPos.y + 73), ImVec2(CursorPos.x + ImGui::GetWindowWidth(), CursorPos.y + 77), ImColor(0, 0, 0, 20), 1);
    }

    ImGui::PopStyleColor();

    ImGui::End();

    ImGui::PopStyleVar(4);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
    ImGui::RenderNotifications();
    ImGui::PopStyleVar(1); // Don't forget to Pop()
    ImGui::PopStyleColor(1);

    if (Settings::Visuals::PreviewEsp)
    {

 
    ImGui::SetNextWindowSize(ImVec2(300, 430));
    ImGui::SetNextWindowPos(ImVec2(WindowPos.x + 810, WindowPos.y + 10));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 11);
    ImGui::SetNextWindowBgAlpha(1.0f);


        if (ImGui::Begin("MENU 2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
        {
            ImVec2 CursorPos = ImGui::GetWindowPos();


            ImVec2 Ped_Location = ImVec2(CursorPos.x + 150, CursorPos.y + 215);
            float Height = 300;
            float Width = (Height / 1.55f);
            float CornerSize = (Width) / 4.f;

            if (Menu::Tab == 1)
            {
   
            if (Settings::Visuals::Corner)
            {
                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), Settings::Visuals::CornerColor, 3);
                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), Settings::Visuals::CornerColor, 3);

                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), Settings::Visuals::CornerColor, 3);
                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), Settings::Visuals::CornerColor, 3);

                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), Settings::Visuals::CornerColor, 3);
                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), Settings::Visuals::CornerColor, 3);

                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), Settings::Visuals::CornerColor, 3);
                ImGui::GetWindowDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), Settings::Visuals::CornerColor, 3);
            }
            if (Settings::Visuals::Box)
            {
                ImGui::GetWindowDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), Settings::Visuals::BoxColor);

            }
           // ImGui::SetCursorPos(ImVec2(Ped_Location.x, Ped_Location.y + Height / 2));
            if (Settings::Visuals::Weapon)
            {
                ImGui::PushFont(littleFont);
                ImGui::GetWindowDrawList()->AddText(ImVec2(Ped_Location.x - 15, Ped_Location.y + Height / 2), ImColor(255, 255, 255, 255), "None");
                ImGui::PopFont();
            }
            }
        /* ImGui::PushFont(littleFont);

            ImGui::SetCursorPos(ImVec2(Ped_Location.x - 15, Ped_Location.y + Height / 2));
            if (Menu::Tab == 5)
            {
                auto Resources = get_resources();

                for (int i = 0; i < Resources.size(); i++)
                {
                    int resourceamount = 0;
                    auto resource = Resources[i];
                    bool selected = (resourceamount == i);

                    if (ImGui::Selectable(resource->m_name.c_str()))
                        selected = i;
                    std::cout << resource->m_name.c_str();
                    

                }
            }
         
            ImGui::PopFont();*/




        }
        ImGui::End();
        ImGui::PopStyleVar(5);

  
    }

}