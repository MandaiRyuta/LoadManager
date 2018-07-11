#pragma once
#include <string>
#include <d3dx9.h>
#include <map>
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
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	//テクスチャ読み込み
	bool load(std::string key);

	//テクスチャを取得する
	LPDIRECT3DTEXTURE9 getResource(std::string key);

	//解放
	bool Release(std::string key);
	//全開放
	bool AllRelease();

private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TexMap;
	LPDIRECT3DDEVICE9 pDevice;
};
typedef enum {
	MODEL_SET,
	MODEL_MAX,
}MODEL_NUM;
struct ModelInfomation
{
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pmeshmaterial;
	LPDIRECT3DTEXTURE9* pmeshtexture;
	DWORD dwmaterial;
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXCOLOR color;
	float rotation;
	bool isscale;
	int index;
	D3DXMATRIX world[MODEL_MAX];
};
class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool load(std::string key);
	ModelInfomation getModelResource(std::string key);
	bool Release(std::string key);
	bool AllRelease(std::string key);
	void SetDevice(LPDIRECT3DDEVICE9 d3ddev);
private:
	std::map<std::string, ModelInfomation*> m_ModelMap;
	LPDIRECT3DDEVICE9 m_d3ddevice;
};