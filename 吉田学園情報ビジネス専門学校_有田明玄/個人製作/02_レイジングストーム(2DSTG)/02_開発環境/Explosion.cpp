//=============================================================================
//
// 爆発
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include "Explosion.h"
#include"Application.h"
#include"renderer.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CExplosion::m_apTexture[EXPLOSION_TEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion() :CObject2D(8)
{
	SetObjType(OBJTYPE_EXPLOSION);
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{
	m_nAnimTimer = 0;
	m_nPtnAnim = 0;
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CExplosion::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	CObject2D::BindTexture(m_apTexture[0]);	//テクスチャの設定
	SetUV((1.0f / EXPLOSION_PTN)*m_nPtnAnim, (1.0f / EXPLOSION_PTN)*(m_nPtnAnim + 1), 0.0f, 1.0f);
		
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CExplosion::Update()
{
	SetUV((1.0f / EXPLOSION_PTN)*m_nPtnAnim, (1.0f / EXPLOSION_PTN)*(m_nPtnAnim + 1), 0.0f, 1.0f);
	CObject2D::Update();

	m_nAnimTimer++;					//カウンター加算
	if ((m_nAnimTimer % EXPLOSION_TIME) == 0)
	{
		m_nPtnAnim++;
		//パターン数を超えた場合
		if (m_nPtnAnim >= EXPLOSION_PTN)
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void  CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CExplosion::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CExplosion::Unload()
{
	for (int i = 0; i < EXPLOSION_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 爆発エフェクト生成
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz)
{
	CExplosion*pBullet = nullptr;
	pBullet = new CExplosion;
	pBullet->SetPos(pos);			//位置設定
	pBullet->Init(siz.x, siz.y);
	pBullet->SetSiz(siz);
	return pBullet;
}