//=============================================================================
//
// 必殺技ゲージ
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Special.h"
#include"renderer.h"
#include"Application.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CSpecial::m_apTexture[NUM_TEX_SP] = {};
float   CSpecial::m_nSpecial = 0.0f;
CObject2D*CSpecial::m_apObject2D[NUM_TEX_SP];

//=============================================================================
// コンストラクタ
//=============================================================================
CSpecial::CSpecial() :CObject(OBJTYPE_UI)
{
	SetObjType(OBJTYPE_UI);
	m_nSpecial = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSpecial::~CSpecial()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSpecial::Init(float Width, float Height)
{
	for (int i = 0; i < NUM_TEX_SP; i++)
	{
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->BindTexture(m_apTexture[i]);	//テクスチャの設定
	}
		m_apObject2D[0]->Init(0.0f, Height);
		m_apObject2D[1]->Init(Width, Height);


	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CSpecial::Uninit()
{
	CObject::Release();
}

//=============================================================================
// 更新
//=============================================================================
void CSpecial::Update()
{
	m_nSpecial += RECOVERY_QUANTITY;
	if (m_nSpecial>MAX_SPECIAL)
	{
		m_nSpecial = MAX_SPECIAL;
	}

	//ゲージの伸縮
	m_apObject2D[0]->SetPosR((float)m_nSpecial *( SPECIAL_WIDTH/MAX_SPECIAL));
}

//=============================================================================
// 描画
//=============================================================================
void CSpecial::Draw()
{

}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CSpecial::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SPGauge001.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SPgauge002.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CSpecial::Unload()
{
	for (int i = 0; i < NUM_TEX_SP; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 背景生成
//=============================================================================
CSpecial * CSpecial::Create(D3DXVECTOR3 pos)
{
	CSpecial*pSpecial;
	pSpecial = new CSpecial;
	if (pSpecial != nullptr)
	{//ポリゴンの初期化処理
		pSpecial->Init(SPECIAL_WIDTH, SPECIAL_HEIGHT);
		for (int i = 0; i < NUM_TEX_SP; i++)
		{
			pSpecial->m_apObject2D[i]->SetPos(pos);
		}
		pSpecial->m_apObject2D[0]->SetPos(D3DXVECTOR3(pos.x- SPECIAL_WIDTH/2,pos.y,pos.z));

	}
	return pSpecial;
}

//=============================================================================
// 加算
//=============================================================================
void CSpecial::AddSpecial(float Special)
{
	m_nSpecial += Special;
}

//=============================================================================
// 取得
//=============================================================================
float CSpecial::GetSpecial()
{
	return m_nSpecial;
}
