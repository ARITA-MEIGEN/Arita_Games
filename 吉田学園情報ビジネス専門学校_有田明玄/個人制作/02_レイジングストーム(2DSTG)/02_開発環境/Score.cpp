//=============================================================================
//
// スコア
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Score.h"
#include"renderer.h"
#include"Application.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CScore::m_apTexture;
//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore() :CObject(OBJTYPE_UI)
{
	SetObjType (OBJTYPE_UI);
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CScore::Init(float Width, float Height)
{
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->Init(Width, Height);
		m_apObject2D[i]->BindTexture(m_apTexture);	//テクスチャの設定
	}
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CScore::Uninit()
{
	CObject::Release();
}

//=============================================================================
// 更新
//=============================================================================
void CScore::Update()
{
	D3DXVECTOR3 dpos=m_pos;
	for (int i = 0; i < NUM_SCORE; i++)
	{//全体の位置を設定
		m_apObject2D[i]->SetPos(dpos);
		m_apObject2D[i]->SetSiz(m_siz);
		dpos.x += m_siz.x;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CScore::Draw()
{

}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CScore::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&m_apTexture);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CScore::Unload()
{
	for (int i = 0; i <NUM_SCORE; i++)
	{
		if (m_apTexture != nullptr)
		{//テクスチャの破棄
			m_apTexture->Release();
			m_apTexture = nullptr;
		}
	}
}

//=============================================================================
// 背景生成
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos)
{
	CScore*pScore;
	pScore = new CScore;
	if (pScore != nullptr)
	{// ポリゴンの初期化処理
		pScore->Init(SCORE_WIDTH, SCORE_HEIGHT);
		pScore->SetPos(pos, D3DXVECTOR2(SCORE_WIDTH,SCORE_HEIGHT));
	}
	return pScore;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CScore::SetPos(D3DXVECTOR3 pos, D3DXVECTOR2 siz)
{
	m_pos = pos;
	m_siz = siz;
}

//=============================================================================
// 設定
//=============================================================================
void CScore::SetScore(int nScore)
{
	int aPosTexU[NUM_SCORE];	//各桁の数字を格納

	m_Score = nScore;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

	//テクスチャ座標の設定
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetUV(0.1f*(aPosTexU[i]), 0.1f*(aPosTexU[i] + 1), 0.0f, 1.0f);
	}
}

//=============================================================================
// 加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	int aPosTexU[NUM_SCORE];	//各桁の数字を格納

	m_Score += nValue;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

	//テクスチャ座標の設定
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetUV(0.1f*(aPosTexU[i]), 0.1f*(aPosTexU[i] + 1), 0.0f, 1.0f);
	}
}

//=============================================================================
// 取得
//=============================================================================
int CScore::GetScore()
{
	return m_Score;
}

//=============================================================================
// 色の設定
//=============================================================================
void CScore::SetCol(D3DXCOLOR col)
{
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetCol(col);
	}
}

