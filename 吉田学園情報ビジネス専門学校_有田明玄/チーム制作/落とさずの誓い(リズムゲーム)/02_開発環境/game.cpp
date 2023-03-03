//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "game.h"
#include "input.h"
#include "effect.h"
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "object3D.h"
#include "obstacle.h"
#include "mesh_field.h"
#include "obstacle_manager.h"
#include "message.h"
#include "player.h"
#include "shield.h"
#include "Score.h"
#include "ranking_ui.h"
#include "domino.h"
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//==================================================
// 静的メンバ変数
//==================================================
CScore* CGame::m_pScore=nullptr;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CGame::CGame() :
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	m_time = -1;

	//メッセージの表示
	{
		D3DXVECTOR3 pos(640.0f, 250.0f, 0.0f);
		CMessage::Create(pos, 1200.0f, 300.0f);
	}

	{// 背景
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(26000.0f, 0.0f, 1800.0f);

		pObj->SetPos(D3DXVECTOR3(320.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(size);

		// テクスチャの設定
		pObj->SetTexture(CTexture::LAVEL_TATAMI);
	}

	//メッシュフィールドの生成
	//CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	// 障害物の生成
	CObstacleManager::Create();	// プレイヤーの生成

	CPlayer::CreateAll();

	//盾の生成
	CShield::CreateAll();

	CDomino::SetCount(0);

	//回数カウント(文言)
	CObject2D* pCount = CObject2D::Create();
	pCount->SetPos(D3DXVECTOR3(1000.0f, 60.0f, 0.0f));
	pCount->SetSize(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
	pCount->SetTexture(CTexture::LAVEL_Count);

	//スコア
	m_pScore = CScore::Create(pCount->GetPos() + D3DXVECTOR3(150.0f, 0.0f, 0.0f));
	m_pScore->SetScore(0);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	{//操作説明(アイコン)
		CObject2D* pIcon = CObject2D::Create();

		//位置を設定
		pIcon->SetPos(D3DXVECTOR3(270.0f, 480.0f, 0.0f));

		//サイズを設定
		pIcon->SetSize(D3DXVECTOR3(550.0f, 150.0f, 0.0f));

		//テクスチャの設定
		pIcon->SetTexture(CTexture::LABEL_Explanation_Icon);

		pos = pIcon->GetPos();	//位置を取得
	}

	{//操作説明(文言)
		CObject2D* pTutorial = CObject2D::Create();

		//位置を設定
		pTutorial->SetPos(pos + D3DXVECTOR3(0.0f, 150.0f, 0.0f));

		//サイズを設定
		pTutorial->SetSize(D3DXVECTOR3(450.0f, 125.0f, 0.0f));

		//テクスチャの設定
		pTutorial->SetTexture(CTexture::LABEL_Explanation);
	}

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	if (m_time >= 0)
	{
		m_time++;

		if (m_time >= 60)
		{
			if (CDomino::GetCount() == 0)
			{
				CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RANKING);
			}
			else
			{
				CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RESULT);
			}
		}
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
		CRankingUI::SetCurrentScore(m_pScore->GetScore());
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	m_pScore->Draw();
}

//--------------------------------------------------
// ゲーム終了
//--------------------------------------------------
void CGame::EndGame()
{
	m_time = 0;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CGame::GetTime()
{
	return m_time;
}