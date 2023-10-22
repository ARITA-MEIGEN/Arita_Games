//======================================================
//
//skill_gage.cpp
//Author:髙野馨將
//
//======================================================
#include "SkillGauge.h"
#include "texture.h"
#include "game.h"
#include "Player.h"

//======================================================
// 定義
//======================================================
const D3DXVECTOR2 CGauge::GAUGE_SIZE = D3DXVECTOR2(CGauge::MAX_SIZE / MAX_GAUGE, 50.0f);	//ゲージ一つ分の大きさ
const float CGauge::MAX_SIZE = 250.0f;														//ゲージの最大値
const float CGauge::SPACE_SIZE = (SCREEN_WIDTH - (MAX_SIZE * 4.0f)) / 5.0f;					//ゲージ同士の間隔の大きさ

//======================================================
//コンストラクタ
//======================================================
CGauge::CGauge(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CGauge::~CGauge()
{//何も書かない
}

//======================================================
//初期化処理
//======================================================
HRESULT CGauge::Init(void)
{
	//初期化処理
	CObject2D::Init();

	//テクスチャの設定
	CObject2D::SetTextureKey("SKILL_GAUGE");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CGauge::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//======================================================
//更新処理
//======================================================
void CGauge::Update()
{
	//プレイヤーの情報の取得
	CPlayer * pPlayer = CGame::GetPlayer(m_nSkillNumber);

	//大きさの設定
	SetSiz(GAUGE_SIZE);

	//更新処理
	CObject2D::Update();

	if (pPlayer != nullptr)
	{//プレイヤーのスキルゲージ分足す

		SetSkillPos(pPlayer->GetSkillGauge());
		float gaugeRatio =  pPlayer->GetSkillGauge() / MAX_GAUGE;
		SetUV(0.0f, gaugeRatio,0.0f, 1.0f);
	}
}

//======================================================
//描画処理
//======================================================
void CGauge::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//======================================================
//生成処理
//======================================================
CGauge *CGauge::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int number)
{
	//動的確保
	CGauge *pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		//初期化
		pGauge->Init();
		pGauge->SetPos(pos);
		pGauge->SetSiz(size);
		pGauge->SetCol(col);
		pGauge->m_nSkillNumber = number;
	}

	return pGauge;
}