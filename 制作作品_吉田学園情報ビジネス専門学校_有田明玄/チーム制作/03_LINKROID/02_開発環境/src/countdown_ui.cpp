//=============================================================================
//
// タイマー
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include "countdown_ui.h"
#include "Application.h"
#include "sound.h"
#include "ObjectList.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCountDownUI::CCountDownUI() : CObject2D(CObjectList::LEVEL_2D_UI)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCountDownUI::~CCountDownUI()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCountDownUI::Init()
{
	CObject2D::Init();
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSiz(D3DXVECTOR2(120.0f, 240.0f));
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTextureKey("NUMBER");
	SetUV(0.1f * (m_nTimer % 10), 0.1f * ((m_nTimer % 10) + 1), 0.0f, 1.0f);

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CCountDownUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CCountDownUI::Update()
{
	CObject2D::Update();

	ScaleMoveDecoration();

	m_nCreateTimer++;
	if (m_nCreateTimer % 60 == 0)
	{
		m_nTimer--;
		if (m_nTimer < 0)
		{
			m_nTimer++;
		}
		SetUV(0.1f * (m_nTimer % 10), 0.1f * ((m_nTimer % 10) + 1), 0.0f, 1.0f);
	}
}

//=============================================================================
// 背景生成
//=============================================================================
CCountDownUI * CCountDownUI::Create(const int inTimer)
{
	CCountDownUI* pTimer;
	pTimer = new CCountDownUI;
	if (pTimer != nullptr)
	{// ポリゴンの初期化処理
		pTimer->m_nTimer = inTimer;
		pTimer->Init();
	}
	return pTimer;
}

void CCountDownUI::ScaleMoveDecoration()
{
	D3DXVECTOR2 size =  GetSiz();

	size.x += cosf(m_nCreateTimer % 60 * 0.1f) * 2.0f;
	size.y += cosf(m_nCreateTimer % 60 * 0.1f) * 2.0f;

	AddPos(D3DXVECTOR3(0.0f,(cosf(m_nCreateTimer % 60 * 0.1f)) * -1.0f,0.0f));

	SetSiz(size);
}
