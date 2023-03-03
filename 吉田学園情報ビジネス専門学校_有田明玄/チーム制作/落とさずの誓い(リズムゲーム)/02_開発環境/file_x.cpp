//**************************************************
// 
// file_x.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "file_x.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CFileX* CFileX::Create(const string& str)
{
	CFileX* pFileX = new CFileX;

	if (pFileX == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pFileX->Init();

	// 読み込み
	pFileX->Load(str);

	return pFileX;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CFileX::CFileX() :
	m_pTexture(nullptr),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CFileX::~CFileX()
{
	assert(m_pBuffMat == nullptr);
	assert(m_pMesh == nullptr);
	assert(m_pTexture == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CFileX::Init()
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_numMat = 0;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	m_vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CFileX::Uninit()
{
	if (m_pBuffMat != nullptr)
	{// マテリアル情報の破棄
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	if (m_pMesh != nullptr)
	{// メッシュ情報の破棄
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pTexture != nullptr)
	{// nullチェック
		for (int i = 0; i < (int)m_numMat; i++)
		{
			if (m_pTexture[i] != nullptr)
			{// テクスチャの破棄
				m_pTexture[i]->Release();
				m_pTexture[i] = nullptr;
			}
		}

		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//--------------------------------------------------
// テクスチャの取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9* CFileX::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// メッシュ情報の取得
//--------------------------------------------------
LPD3DXMESH CFileX::GetMesh()
{
	return m_pMesh;
}

//--------------------------------------------------
// マテリアル情報の取得
//--------------------------------------------------
LPD3DXBUFFER CFileX::GetBuffMat()
{
	return m_pBuffMat;
}

//--------------------------------------------------
// マテリアル情報の数の取得
//--------------------------------------------------
DWORD CFileX::GetNumMat()
{
	return m_numMat;
}

//--------------------------------------------------
// サイズの取得
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// 最小値の取得
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetVtxMin() const
{
	return m_vtxMin;
}

//--------------------------------------------------
// 最大値の取得
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetVtxMax() const
{
	return m_vtxMax;
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CFileX::Load(const string& str)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		str.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// メッシュに使用されているテクスチャ用の配列を用意する
	m_pTexture = new LPDIRECT3DTEXTURE9[m_numMat];

	// 各メッシュのマテリアル情報を取得する
	for (int i = 0; i < (int)m_numMat; i++)
	{
		if (pMat[i].pTextureFilename != nullptr)
		{// マテリアルで設定されているテクスチャの読み込み
			D3DXCreateTextureFromFileA(pDevice,
				pMat[i].pTextureFilename,
				&m_pTexture[i]);
		}
		else
		{// テクスチャなし
			m_pTexture[i] = nullptr;
		}
	}
}
