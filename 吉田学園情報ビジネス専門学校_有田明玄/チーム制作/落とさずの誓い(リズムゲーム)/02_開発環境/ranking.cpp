//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "ranking.h"
#include "menu.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"
#include "ranking_ui.h"
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRanking::CRanking() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRanking::Init()
{
	{// 背景
		CObject2D* pObj = CObject2D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT*0.5f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_RankingBG002);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.78f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(450.0f, 100.0f, 0.0f);

		// 生成
		m_pMenu = CMenu::Create(pos, size, 2, 50.0f);

		// カーソルの設定
		m_pMenu->SetCursor(D3DXVECTOR3(100.0f, 50.0f, 0.0f), 20.0f);

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_Restart);
		m_pMenu->SetTexture(1, CTexture::LABEL_ReturnToTitle);
	}
	m_pRanking= CRankingUI::Create();

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu = nullptr;
	}
	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		m_pRanking = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRanking::Update()
{
	// 入力
	Input();

	m_pRanking->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRanking::Draw()
{
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CRanking::Input()
{
	int select = m_pMenu->Select();

	if (select == -1)
	{// 入力されていない
		return;
	}

	if (select == 0)
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}
	else
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
	}
	
}
