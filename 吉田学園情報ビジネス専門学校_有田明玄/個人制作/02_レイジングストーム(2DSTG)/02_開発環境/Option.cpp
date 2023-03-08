//=============================================================================
//
// オプション
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Option.h"
#include"renderer.h"
#include"Application.h"
#include"Bullet.h"
#include"Explosion.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 COption::m_apTexture[OPTION_TEX] = {};
D3DXVECTOR3 COption::m_PlayerPosOld[OPTION_MEMPOS];
int COption::m_nNumOption = 0;
//=============================================================================
// コンストラクタ
//=============================================================================
COption::COption():CObject2D(OBJTYPE_OPTION)
{
	SetObjType(OBJTYPE_OPTION);
	m_nId = m_nNumOption;
	m_nNumOption++;
}

//=============================================================================
// デストラクタ
//=============================================================================
COption::~COption()
{
	SetObjType(OBJTYPE_INVALID);
	m_nNumOption--;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  COption::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	CObject2D::BindTexture(m_apTexture[m_nId]);	//テクスチャの設定
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  COption::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  COption::Update()
{
	SetPos(m_PlayerPosOld[10*(m_nId+1)]);
	CObject2D::Update();
}

//=============================================================================
// 描画
//=============================================================================
void  COption::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// オプション生成
//=============================================================================
COption* COption::Create(D3DXVECTOR3 pos)
{
	COption*pOption;
	pOption = new COption;
	if (pOption != nullptr)
	{// ポリゴンの初期化処理
		pOption->Init(OPTION_WIDTH, OPTION_HEIGHT);
	}
	return pOption;
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT COption::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_WHITE001.png",
		&m_apTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOW001.png",
		&m_apTexture[1]);


	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void COption::Unload()
{
	for (int i = 0; i < OPTION_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 位置情報の記憶
//=============================================================================
void COption::MemPos(D3DXVECTOR3 posold)
{
	if (posold != m_PlayerPosOld[0])
	{//プレイヤーが移動している場合
		D3DXVECTOR3 mempos[2];	//入れ替え用

		mempos[0] = m_PlayerPosOld[0];
		m_PlayerPosOld[0] = posold;
		for (int i = 0; i < OPTION_MEMPOS-1; i++)
		{//座標を保存
			mempos[(i+1)%2] = m_PlayerPosOld[i+1];
			m_PlayerPosOld[i+1] = mempos[i%2];
		}
	}
}

//=============================================================================
// 位置情報のリセット
//=============================================================================
void COption::ResetPos(D3DXVECTOR3 posold)
{
	for (int i = 0; i < OPTION_MEMPOS; i++)
	{//座標を保存
		m_PlayerPosOld[i] = posold;
	}
}

