//=============================================================================
//
// 体力
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Lifegauge.h"
#include"renderer.h"
#include"Application.h"
#include"Player.h"
#include"Score.h"
#include"Game.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CLife::m_apTexture[LIFE_TEX] = {};
CObject2D*CLife::m_apObject2D[LIFE_POLYGON] = {};
CObject2D*CLife::m_aLifeUI=nullptr;
int CLife::m_NumLife = 0;
//=============================================================================
// コンストラクタ
//=============================================================================
CLife::CLife() :CObject(OBJTYPE_UI)
{
	SetObjType(OBJTYPE_UI);
}

//=============================================================================
// デストラクタ
//=============================================================================
CLife::~CLife()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CLife::Init(float Width, float Height)
{
	for (int i = 0; i <LIFE_POLYGON; i++)
	{//体力の描画
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->Init(Width, Height);
		m_apObject2D[i]->BindTexture(m_apTexture[0]);	//テクスチャの設定
	}
	m_NumLife = 3;
	m_apObject2D[3]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_apObject2D[4]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_aLifeUI = new CObject2D(OBJTYPE_UI);
	m_aLifeUI->Init(LIFEUI_SIZ_X, LIFEUI_SIZ_Y);
	m_aLifeUI->BindTexture(m_apTexture[1]);	//テクスチャの設定

	SetPos();

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CLife::Uninit()
{
	for (int i = 0; i < m_NumLife - 1; i++)
	{
		if (m_apObject2D[i] != nullptr)
		{
			m_apObject2D[i] = nullptr;
		}
	}
	CObject::Release();
}

//=============================================================================
// 更新
//=============================================================================
void CLife::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void CLife::Draw()
{
	
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CLife::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LIFE.png",
		&m_apTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LIFElogo.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CLife::Unload()
{
	for (int i = 0; i <LIFE_TEX; i++)
	{
		if (m_apTexture != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 体力生成
//=============================================================================
CLife * CLife::Create()
{
	CLife*pLIFE;
	pLIFE = new CLife;
	if (pLIFE != nullptr)
	{// ポリゴンの初期化処理
		pLIFE->Init(LIFE_SIZ, LIFE_SIZ);
	}
	return pLIFE;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CLife::SetPos()
{
	for (int i = 0; i < LIFE_POLYGON; i++)
	{
		m_apObject2D[i]->SetPos(D3DXVECTOR3(LIFE_POS_X +((LIFE_SIZ+ LIFE_INTERVAL)*i) , LIFE_POS_Y, 0.0f));
	}
	m_aLifeUI->SetPos(D3DXVECTOR3(LIFELOGO_POS_X, LIFELOGO_POS_Y, 0.0f));
}

//=============================================================================
//体力回復
//=============================================================================
void CLife::LifeRecovery()
{
	if (m_NumLife < LIFE_POLYGON)
	{
		m_apObject2D[m_NumLife]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); 
		m_NumLife++;
	}
	else
	{
		CGame::GetScore()->AddScore(5000);
	}
}

//=============================================================================
//体力減少
//=============================================================================
void CLife::LifeDecrease()
{
	if (m_NumLife >= 0)
	{
		m_apObject2D[m_NumLife - 1]->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		m_NumLife--;
	}

}

