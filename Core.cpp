#include "Core.hpp"

#include "d3d_Hook.hpp"
#include "Menu.hpp"
#include "Classes.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include "Weapons.hpp"
#include "NoClip.hpp"
#include "Visuals.hpp"

#include "vehicule.hpp"
#include "auth.hpp"
#include "Fonts.hpp"
#include <imguinotify.hpp>
#include "Aimbot.hpp"
#include "icon_font.h"
#include "spoof_call.h"

using namespace KeyAuth;

std::string name = "LoaderGui"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "jhWi7xRUCS"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "3aac3c34d8c41913e169a20efd7fbf7bad278e095e85d88e7466ec05aab7ac3f"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting
std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
/*
	Video on what ownerid and secret are https://youtu.be/uJ0Umy_C6Fg
	Video on how to add KeyAuth to your own application https://youtu.be/GB4XW_TsHqA
	Video to use Web Loader (control loader from customer panel) https://youtu.be/9-qgmsUUCK4
*/
#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rdx[] = { 0xFF, 0x27 };
api KeyAuthApp(name, ownerid, secret, version, url,sslPin);

//#include "Snow.hpp"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// you need those for snowflake
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080
bool IsValid = false;

void Kouloumbou()
{
	std::exit(-1);
}
void InitImGui()
{
	using namespace DirectX;

	ImGui::CreateContext();

	ImGuiIO* io = &ImGui::GetIO();
	io->ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io->IniFilename = nullptr;
	io->LogFilename = nullptr;

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;

	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;

	ImFontConfig rubik;
	rubik.FontDataOwnedByAtlas = false;


	io->Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(Rubik), sizeof(Rubik), 15.5f, &rubik);
	io->Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 25.f, &icons_config, icons_ranges);
	io->Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 25.f, &icons_config, icons_ranges);
	Menu::BiggestIcon = io->Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 40.f, NULL, icons_ranges);
	Menu::BiggestFont = io->Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(Rubik), sizeof(Rubik), 21.f, &rubik);
	Menu::littleFont = io->Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(Rubik), sizeof(Rubik), 17.5f, &rubik);

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	
	//Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.f/*minimum size*/, 25.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, WINDOW_WIDTH, WINDOW_HEIGHT, Snowflake::vec3(0.f, 0.005f)/*gravity*/, IM_COL32(255,255, 255, 100)/*color*/);

}


LRESULT __stdcall WindowHandler(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Menu::Open)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return SAFE_CALL(CallWindowProcA)(DirectX::WindowEx, hWnd, uMsg, wParam, lParam);
}


bool BindD3DInfo(IDXGISwapChain* pSwapChain)
{
	if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX::pDevice)))
	{
		DirectX::pDevice->GetImmediateContext(&DirectX::pContext);
		DXGI_SWAP_CHAIN_DESC sd;

		pSwapChain->GetDesc(&sd);
		DirectX::Window = sd.OutputWindow;
		
	
		ID3D11Texture2D* pBackBuffer;

		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		DirectX::pDevice->CreateRenderTargetView(pBackBuffer, 0, &DirectX::renderTargetView);
		pBackBuffer->Release();

		DirectX::WindowEx = (WNDPROC)LI_FN(SetWindowLongPtrA).safe_cached()(DirectX::Window, GWLP_WNDPROC, (LONG_PTR)WindowHandler);

		InitImGui();

		Menu::FirstTime = false;

		Menu::Style();

		return true;
	}

	return false;
}
bool AuthConnected = false;

char Licence[50] = "";
char UserName[20] = "";
char RgPassWord[20] = "";
char RgUserName[20] = "";
static char PassWord[256] = "";
static int Tabs = 2;
static int Checks = 0;

bool LoginNow()
{
	KeyAuthApp.license(PassWord);


	if (KeyAuthApp.data.success)
	{
		std::string i2;
		i2 = PassWord;
		int caca = 1;

		IsValid = true;
		AuthConnected = true;
		caca = 2;
		return true;
	}


}
HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (Menu::FirstTime)
	{
		KeyAuthApp.init();
		if (!BindD3DInfo(pSwapChain))
			return DirectX::OriginalPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (SAFE_CALL(GetAsyncKeyState)(VK_HOME) & 1)
	{

		Menu::Open = !Menu::Open;
	}
	
	ImGui::GetIO().MouseDrawCursor = Menu::Open;
	ImGui::GetIO().WantCaptureKeyboard = Menu::Open;
	if (AuthConnected)
	{
		//std::thread(Aimbot::Hook).detach();

		Visuals::Hook();
		Players::Hook();
	    Aimbot::Hook();				
		Weapons::Hook();
		NoClip::Hook();
		Vehicule::Hook();

		if (Settings::Aimbot::Draw_Fov)
		{

			//	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(1920 / 2, 1080 / 2), Option::AimbotFov, IM_COL32(255, 255, 255, 255), 40.f,1.f);
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), Settings::Aimbot::AimbotFov, IM_COL32(0, 0, 0, 140), 40.F);
		}

		if (Settings::Aimbot::crosshair)
		{
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(955, 540), ImVec2(965, 540), ImColor(255, 255, 255, 255), 1);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(960, 535), ImVec2(960, 545), ImColor(255, 255, 255, 255), 1);

		}
		POINT mouse;
		RECT rc = { 0 };
		GetWindowRect(DirectX::Window, &rc);

		if (Menu::Open)
		{
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImColor(0, 0, 0, 100));
			Menu::Drawing();


		}
	}
	else
	{
		if (Menu::Open)
		{

			ImGui::SetNextWindowSize(ImVec2(550, 350));

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12);

			ImGui::SetNextWindowBgAlpha(1.0f);


			if (ImGui::Begin(E("Auth"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
			{

				auto pos = ImGui::GetWindowPos();
				auto draw = ImGui::GetWindowDrawList();

				draw->AddRectFilled(ImVec2(pos.x + ImVec2{ -1.f, 0.f }.x, pos.y + ImVec2{ -1.f, 0.f }.y), ImVec2(pos.x + ImVec2{ 71.f, 359.f }.x,pos.y + ImVec2{ 71.f, 359.f }.y), ImColor(0.05f, 0.05f, 0.05f, 1.00f), 0.f, 256);
				draw->AddCircleFilled(ImVec2(pos.x + ImVec2{ 36.f, 28.f }.x,pos.y +  ImVec2{ 36.f, 28.f }.y), 16, ImColor(1.00f, 1.00f, 1.00f, 1.00f), 32.f);
				draw->AddLine(ImVec2(pos.x + ImVec2{ 71.f, 1.f }.x , pos.y + ImVec2{ 71.f, 1.f }.y) , ImVec2(pos.x + ImVec2{ 71.f, 350.f }.x , pos.y + ImVec2{ 71.f, 350.f }.y), ImColor(1.00f, 1.00f, 1.00f, 1.00f), 1.f);
				ImGui::SetCursorPosY(22);
				ImGui::SetCursorPosX(86);

				ImGui::Text("Welcome to Vigos Project | Please enter your key ");
				ImGui::SetCursorPosX(150);

				ImGui::SetCursorPosY(42);

		
			
				if (Tabs == 1)
				{


				
				}

				if (Tabs == 2)
				{
					
					std::string i2;
					i2 = PassWord;
					int caca = 1;

					//IsValid = true;
					//AuthConnected = true;
				//	caca = 2;
					ImGui::Spacing();

					ImGui::Separator();

					ImGui::SetCursorPosX( 155.5f);
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 80.5f);
					ImGui::PushItemWidth(245);
					ImGui::InputText(E("Key##rg"), PassWord, IM_ARRAYSIZE(PassWord), ImGuiInputTextFlags_Password);
					ImGui::SetCursorPosX(170.5f);
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 25.5f);
					ImGui::PopItemWidth();
					if (ImGui::Button(E("Login##Log"), ImVec2(220, 30)))
					{

						ImGui::InsertNotification({ ImGuiToastType_Success, 3000, E("Connecting.. :)") });	
						if (!LoginNow())					
							abort();			

					}
				}
				ImGui::PopStyleVar(5);
				ImGui::End();
			}

		}
	}

	ImGui::Render();

	DirectX::pContext->OMSetRenderTargets(1, &DirectX::renderTargetView, 0);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return return_spoofer::spoof_call(jmp_rdx,DirectX::OriginalPresent, pSwapChain, SyncInterval, Flags);
}

bool Core::Init()
{
	std::this_thread::sleep_for(std::chrono::seconds(15)); // paste from hx 

	while (!DirectX::OverlayHooked)
	{
		if (Hook::Init())
		{
			DirectX::OverlayHooked = Hook::Present((void**)&DirectX::OriginalPresent, PresentHook);
		}
	}

	return true;
}
