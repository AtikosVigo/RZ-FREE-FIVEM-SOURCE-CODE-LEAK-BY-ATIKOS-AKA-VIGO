#pragma once

#include <Windows.h>
#include <iostream>
#include <d3d11.h>

#include <vector>
#include <string>

#include <filesystem>
#include <fstream>

#include <mutex>
#include <map>
#include <unordered_map>

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "EncryptString.hpp"
#include "EncryptFuncs.hpp"
#include "Memory.hpp"

#define M_PI 3.14159265358979323846

#pragma warning(disable: 4005)

#define DEBUG 1

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

