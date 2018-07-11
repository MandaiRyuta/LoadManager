#include "ResourceManager.h"
#include "main.h"
typedef std::map<std::string, LPDIRECT3DTEXTURE9> TexTable;
typedef std::map<std::string, ModelInfomation*> ModelTable;

TextureManager::TextureManager()
{
	this->pDevice = GetD3DDevice();
}

TextureManager::~TextureManager()
{
}

bool TextureManager::load(std::string key)
{
	//テクスチャ検索
	TexTable::const_iterator it = m_TexMap.find(key);
	if (it == m_TexMap.end())
	{
		HRESULT hr;
		LPDIRECT3DTEXTURE9 texture;
		//LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		hr = D3DXCreateTextureFromFile(
			pDevice,
			key.c_str(),
			&texture
		);
		if (FAILED(hr)) {
			MessageBox(NULL, key.c_str(), "Load Error!", MB_OK);
			return false;
		}

		//マップへ挿入する
		m_TexMap.insert(TexTable::value_type(key, texture));
	}
	return true;
}

LPDIRECT3DTEXTURE9 TextureManager::getResource(std::string key)
{
	// テクスチャを検索
	TexTable::const_iterator it = m_TexMap.find(key);
	if (it != m_TexMap.end()) {       // 見つかった場合
									  // テクスチャを返す
		return it->second;
	}
	else {                            // 見つからなかった場合
									  // 検索した文字列をキーとして
									  // 新しくマップにテクスチャを追加する
		HRESULT hr;
		LPDIRECT3DTEXTURE9 texture;
		//LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		hr = D3DXCreateTextureFromFile(pDevice,
			key.c_str(),
			&texture);
		if (FAILED(hr)) {
			// 生成できなかった場合はNULLポインタを返す
			MessageBox(NULL, key.c_str(), "LOAD ERROR!", MB_OK);
			return NULL;
		}

		// マップへ挿入する
		m_TexMap.insert(TexTable::value_type(key, texture));

		return texture;
	}
}

bool TextureManager::Release(std::string key)
{
	TexTable::const_iterator it = this->m_TexMap.find(key);
	if (it == this->m_TexMap.end())
	{
		it->second->Release();
	}
	return true;
}

bool TextureManager::AllRelease()
{
	m_TexMap.clear();
	return true;
}


ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

bool ModelManager::load(std::string key)
{
	ModelTable::const_iterator it = this->m_ModelMap.find(key);
	
	if (it == m_ModelMap.end())
	{
		HRESULT hr = NULL;
		ModelInfomation* model = nullptr;
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		if (FAILED(D3DXLoadMeshFromX(key.c_str(), D3DXMESH_SYSTEMMEM, this->m_d3ddevice, NULL, &pD3DXMtrlBuffer, NULL, &it->second->dwmaterial, &it->second->pMesh)))
		{
			//MessageBox(NULL, "XFile")
		}
		if (FAILED(hr)) {
			MessageBox(NULL, "ModelLoader", "Load Error!", MB_OK);
			return false;
		}
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		model->pmeshmaterial = new D3DMATERIAL9[model->dwmaterial];
		model->pmeshtexture = new LPDIRECT3DTEXTURE9[model->dwmaterial];

		for (DWORD i = 0; i < model->dwmaterial; i++)
		{
			model->pmeshmaterial[i] = d3dxMaterials[i].MatD3D;
			model->pmeshmaterial[i].Ambient = model->pmeshmaterial->Diffuse;
			model->pmeshtexture[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&strlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice, d3dxMaterials[i].pTextureFilename, &model->pmeshtexture[i])))
				{
					MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
					PostQuitMessage(0);
				}
			}
		}
		//マップへ挿入する
		m_ModelMap.insert(ModelTable::value_type(key, model));
	}
	return true;
}

ModelInfomation ModelManager::getModelResource(std::string key)
{
	return ModelInfomation();
}

bool ModelManager::Release(std::string key)
{
	return false;
}

bool ModelManager::AllRelease(std::string key)
{
	return false;
}

void ModelManager::SetDevice(LPDIRECT3DDEVICE9 d3ddev)
{
}
