//================================================
//
//背景 [Bg.cpp]
//Author : Kishimoto Eiji
//
//================================================
#include "Bg.h"
#include "Object2D.h"
#include "Application.h"
#include "texture.h"

//***************************
//定数の定義
//***************************
namespace
{
const D3DXVECTOR2 SIZEUP_SPEED = D3DXVECTOR2(4.0f, 4.0f);	//サイズ増加のスピード
const D3DXVECTOR2 CIRCLE_SIZE = D3DXVECTOR2(30.0f, 30.0f);	//サークルのサイズ
const float ALPHA_SPEED = 0.01f;	//α値減少のスピード
}

//======================================================
//生成
//======================================================
CBg *CBg::Create()
{
	CBg* pBg = nullptr;	//ポインタ

	if (pBg != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pBg = new CBg;	//動的確保

	pBg->Init();	//初期化

	return pBg;
}

//======================================================
//コンストラクタ
//======================================================
CBg::CBg(int nPriority) : CObject(nPriority),
m_pBg(nullptr),
m_pCircle(nullptr),
m_bPop(false)
{
}

//======================================================
//デストラクタ
//======================================================
CBg::~CBg()
{
}

//======================================================
//初期化
//======================================================
HRESULT CBg::Init()
{
	{//背景
		//生成に必要な要素
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR2 size = D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

		//生成
		m_pBg = CObject2D::Create(pos, size, 4);

		//テクスチャの設定
		m_pBg->SetTextureKey("SKILL_SELECT_BG");
	}

	{//サークル
		//生成に必要な要素
		D3DXVECTOR3 pos = D3DXVECTOR3(
			(float)SCREEN_WIDTH * 0.5f,
			(float)SCREEN_HEIGHT * 0.5f,
			0.0f);

		//生成
		m_pCircle = CObject2D::Create(pos, CIRCLE_SIZE, 4);

		//テクスチャの設定
		m_pCircle->SetTextureKey("CIRCLE");
	}

	//メンバ変数の初期化
	m_bPop = true;

	return S_OK;
}

//======================================================
//終了
//======================================================
void CBg::Uninit()
{
	//背景
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	//サークル
	if (m_pCircle != nullptr)
	{
		m_pCircle->Uninit();
		m_pCircle = nullptr;
	}
}

//======================================================
//更新
//======================================================
void CBg::Update()
{
	m_pBg->Update();	//背景

	if (m_bPop)
	{
		Circle_Pop();	//出現中のサークル
	}
	else
	{
		Circle_Move();	//移動中のサークル
	}

	m_pCircle->Update();	//サークル
}

//======================================================
//描画
//======================================================
void CBg::Draw()
{
	m_pBg->Draw();	//背景

	m_pCircle->Draw();	//サークル
}

//======================================================
//出現中のサークル
//======================================================
void CBg::Circle_Pop()
{
	//現在のサイズを取得
	D3DXVECTOR2 size = m_pCircle->GetSiz();

	//サイズを大きくする
	size += SIZEUP_SPEED;

	//サイズの設定
	m_pCircle->SetSiz(size);

	//現在の色を取得
	D3DXCOLOR col = m_pCircle->GetCol();

	if (col.a <= 0.0f)
	{
		//α値を0.0fにする
		col.a = 0.0f;

		//色の設定
		m_pCircle->SetCol(col);

		m_bPop = false;	//消える
		return;
	}

	/* α値が0.0f以下ではない場合 */

	//徐々に透明にする
	col.a -= ALPHA_SPEED;

	//色の設定
	m_pCircle->SetCol(col);
}

//======================================================
//移動中のサークル
//======================================================
void CBg::Circle_Move()
{
	//ランダム
	int nRandX = rand() % 7 + 3;
	int nRandY = rand() % 7 + 3;

	//位置
	D3DXVECTOR3 pos = D3DXVECTOR3(
		SCREEN_WIDTH * (0.1f * nRandX),
		SCREEN_HEIGHT * (0.1f * nRandY),
		0.0f);

	//位置を設定
	m_pCircle->SetPos(pos);

	//サイズを設定(0にする)
	m_pCircle->SetSiz(D3DXVECTOR2(0.0f, 0.0f));

	//色を設定(α値を1,0fにする)
	m_pCircle->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//出現する
	m_bPop = true;
}