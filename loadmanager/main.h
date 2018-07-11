#pragma once

#include <Windows.h>
#include <time.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <string>

//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#ifndef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#endif
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XAudio2.lib")

namespace windows_rect
{
	constexpr int D3D_SCREEN_WIDTH = 1800;
	constexpr int D3D_SCREEN_HEIGHT = 1300;
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
}

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

namespace TEXTURERS
{
	const std::string texture = "concrete1.bmp";
	//	const std::string NUMBER = "resource/texture/NumberSet.png";
}

namespace XMODELFILEPASS
{
	const std::string MAP = "resource/xmodel/Island.x";
	const std::string SKYDOME = "resource/xmodel/sky_dome_29.X";
	const std::string BOX = "resource/xmodel/box.x";
	const std::string THREE = "resource/xmodel/tree.x";
	const std::string LEAF = "resource/xmodel/leaf.x";
}

LPDIRECT3DDEVICE9 GetD3DDevice(void);