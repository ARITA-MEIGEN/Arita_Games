//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Effect.h"
#include"renderer.h"
#include"Application.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[EFFECT_TEX] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect() :CObject2D(OBJTYPE_EFFECT)
{
	SetObjType(OBJTYPE_EFFECT);
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CEffect::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	CObject2D::BindTexture(m_apTexture[0]);	//テクスチャの設定
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CEffect::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CEffect::Update()
{
	CObject2D::Update();

	//大きさを変化させる
	D3DXVECTOR2 Siz = GetSiz();
	D3DXCOLOR col = GetCol();

	Siz -= {0.1f, 0.1f};
	m_Life--;
	col.a -= 0.1f;

	//色(アルファ値を変化させる)
	if (col.a <= 0.0f || Siz.x <= 0.0f || Siz.y <= 0.0f || m_Life <= 0)
	{//アルファ値が0以下の場合強制終了
		Uninit();
		return;
	}
	else
	{
		SetSiz(Siz);
		SetCol(col);
	}
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;
	SetPos(pos);
}

//=============================================================================
// 描画
//=============================================================================
void  CEffect::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 生成
//=============================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz, float lot, D3DXVECTOR3 move, int nLife,D3DXCOLOR col)
{
	CEffect*pEffect;
	pEffect = new CEffect;
 	if (pEffect != nullptr)
	{// ポリゴンの初期化処理
 		pEffect->SetPos(pos);
		pEffect->SetRot(lot);
		pEffect->m_Life=nLife;
		pEffect->SetCol(col);
		pEffect->m_move = move;
		pEffect->Init(siz.x/2,siz.y/2);
	}
	return pEffect;
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CEffect::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_apTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_WHITE001.png",
		&m_apTexture[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOW001.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CEffect::Unload()
{
	for (int i = 0; i < EFFECT_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}
