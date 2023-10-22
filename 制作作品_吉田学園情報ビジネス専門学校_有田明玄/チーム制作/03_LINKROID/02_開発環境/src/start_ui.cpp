//=============================================================================
//
// タイマー
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include "start_ui.h"
#include "Application.h"
#include "sound.h"
#include "ObjectList.h"
#include "utility.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CStartUI::CStartUI() : CObject2D(CObjectList::LEVEL_2D_UI)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CStartUI::~CStartUI()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStartUI::Init()
{
	CObject2D::Init();
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSiz(D3DXVECTOR2(924.0f * 0.6f, 378.0f * 0.6f));
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTextureKey("START");
	m_nDisplayTimer = 40;

	return S_OK;
}

//=============================================================================
// 更新
//=============================================================================
void CStartUI::Update()
{
	CObject2D::Update();

	AddCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.01f));
	AddPos(D3DXVECTOR3(FloatRandom(1.0f, -1.0f), FloatRandom(1.0f,-1.0f), 0.0f));
	float sizeMag = FloatRandom(0.0055f, 0.005f);
	AddSiz(D3DXVECTOR2(924.0f * sizeMag, 378.0f * sizeMag));

	m_nDisplayTimer--;

	if (m_nDisplayTimer == 30)
	{
		SetTextureKey("START2");
	}

	if (m_nDisplayTimer == 15)
	{
		SetTextureKey("START3");
	}

	if (m_nDisplayTimer == 5)
	{
		SetTextureKey("START4");
	}

	if (m_nDisplayTimer <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// 背景生成
//=============================================================================
CStartUI * CStartUI::Create()
{
	CStartUI* ui;
	ui = new CStartUI;
	if (ui != nullptr)
	{// ポリゴンの初期化処理
		ui->Init();
	}
	return ui;
}
