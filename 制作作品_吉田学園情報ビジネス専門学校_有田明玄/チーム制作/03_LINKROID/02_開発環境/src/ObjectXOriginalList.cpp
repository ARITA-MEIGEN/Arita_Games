//=============================================================================
//
// オブジェクトXを読み込んで保存する処理 [objectX_group.cpp]
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "application.h"
#include "renderer.h"
#include "ObjectXOriginalList.h"
#include "file.h"

#include <assert.h>

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
const wchar_t* CObjectXOriginalList::filePath = L"Data/FILE/model.json";

//-----------------------------------------------------------------------------
// 静的変数
//-----------------------------------------------------------------------------
CObjectXOriginalList* CObjectXOriginalList::m_originalList = nullptr;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectXOriginalList::CObjectXOriginalList()
{
}

//=============================================================================
// インスタンスの取得
//=============================================================================
CObjectXOriginalList * CObjectXOriginalList::GetInstance()
{
	if (m_originalList == nullptr)
	{
		m_originalList = new CObjectXOriginalList;
	}
	return m_originalList;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectXOriginalList::~CObjectXOriginalList()
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CObjectXOriginalList::Uninit()
{
	if (m_originalList != nullptr)
	{
		delete m_originalList;
		m_originalList = nullptr;
	}
}

//=============================================================================
// 全ての読み込み
//=============================================================================
void CObjectXOriginalList::LoadAll()
{
	nlohmann::json list = LoadJson(filePath);

	int size = (int)list["MODEL"].size();

	std::string test = list["MODEL"][0][0];
	for (int i = 0; i < size; ++i)
	{
		Load(list["MODEL"].at(i));
	}
}

//=============================================================================
// 読み込み
//=============================================================================
CObjectXOriginalList::SModelData CObjectXOriginalList::Load(std::string inKey, std::string inFileName)
{
	SModelData model = {};
	std::string fileName = inFileName;

	if (m_fileName[inKey] == inFileName)
	{
		return m_model[inKey];
	}

	// モデル情報の初期化
	model.pBuffMat = nullptr;
	model.numMat = 0;
	model.pMesh = nullptr;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(&fileName.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.pBuffMat,
		NULL,
		&model.numMat,
		&model.pMesh);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = model.pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(model.pMesh->GetFVF());

	//頂点バッファのロック
	model.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// モデルの端を格納する変数のリセット
	model.minVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	model.maxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < model.minVtx.x)
		{//最小値
			model.minVtx.x = vtx.x;
		}
		if (vtx.x > model.maxVtx.x)
		{//最大値
			model.maxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < model.minVtx.y)
		{//最小値
			model.minVtx.y = vtx.y;
		}
		if (vtx.y > model.maxVtx.y)
		{//最大値
			model.maxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < model.minVtx.z)
		{//最小値
			model.minVtx.z = vtx.z;
		}
		if (vtx.z > model.maxVtx.z)
		{//最大値
			model.maxVtx.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタ進める
		pVtxBuff += sizeFVF;
	}

	// サイズ設定
	model.size = model.maxVtx - model.minVtx;

	//頂点バッファのアンロック
	model.pMesh->UnlockVertexBuffer();

	if (!ExistsKey(inKey))
	{
		m_model[inKey] = model;
		m_fileName[inKey] = fileName;
		m_tagList.push_back(inKey);
	}
	else
	{
		m_model[inKey] = model;
	}

	return model;
}

//=============================================================================
// 全ての解放
//=============================================================================
void CObjectXOriginalList::UnloadAll()
{
	m_model.clear();
}

//=============================================================================
// 解放
//=============================================================================
void CObjectXOriginalList::Unload(std::string inKey)
{
	m_model.erase(inKey);
}

//=============================================================================
// メッシュの取得
//=============================================================================
LPD3DXMESH CObjectXOriginalList::GetMesh(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return nullptr;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].pMesh;
}

//=============================================================================
// バッファの取得
//=============================================================================
LPD3DXBUFFER CObjectXOriginalList::GetBuffMat(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return nullptr;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].pBuffMat;
}

//=============================================================================
// マテリアル数の取得
//=============================================================================
DWORD CObjectXOriginalList::GetNumMat(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return 0;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].numMat;
}

//=============================================================================
// マテリアル数の取得
//=============================================================================
D3DXVECTOR3 CObjectXOriginalList::GetMinVtx(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].minVtx;
}

//=============================================================================
// 一番値が大きい頂点バッファの取得
//=============================================================================
D3DXVECTOR3 CObjectXOriginalList::GetMaxVtx(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].maxVtx;
}

//=============================================================================
// 一番値が小さい頂点バッファの取得
//=============================================================================
D3DXVECTOR3 CObjectXOriginalList::GetSize(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].size;
}

std::string CObjectXOriginalList::GetTag(int index)
{
	if (0 > index)
	{
		return m_tagList[0];
	}
	else if ((int)m_tagList.size() <= index)
	{
		return m_tagList[(int)m_tagList.size() - 1];
	}
	else
	{
		return m_tagList[index];
	}
}
