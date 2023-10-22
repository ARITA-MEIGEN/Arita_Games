//**************************************************
// 
// obstacle_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "obstacle_manager.h"
#include "obstacle.h"
#include "application.h"
#include "mode.h"
#include "game.h"

//==================================================
// 定義
//==================================================
namespace
{
const int MIN_INTERVAL = 30;	// 間隔の最小値
const int MAX_INTERVAL = 120;	// 間隔の最大値
const int POP_INTERVAL = 4;		// 出現の最大数
const float POP_POS_Y = 10.0f;	// 出現のYの位置
const D3DXVECTOR3 POP_POS[] =
{// 出現の位置
	D3DXVECTOR3(-600.0f, POP_POS_Y, 100.0f),
	D3DXVECTOR3(   0.0f, POP_POS_Y, -500.0f),
	D3DXVECTOR3( 600.0f, POP_POS_Y, 100.0f),
};
const D3DXVECTOR3 MOVE[] =
{// 出現の位置
	D3DXVECTOR3( 6.0f, 0.0f, 0.0f),
	D3DXVECTOR3( 0.0f, 0.0f, 6.0f),
	D3DXVECTOR3(-6.0f, 0.0f, 0.0f),
};
const D3DXVECTOR3 POP_ROT[] =
{// 出現の位置
	D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
};
const int POP_MAX = sizeof(POP_POS) / sizeof(POP_POS[0]);	// 出現位置の最大数
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObstacleManager* CObstacleManager::Create()
{
	CObstacleManager* pManager = nullptr;

	pManager = new CObstacleManager;

	if (pManager != nullptr)
	{// nullチェック
		// 初期化
		pManager->Init();
	}

	return pManager;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObstacleManager::CObstacleManager() : CObject(CObject::PRIORITY_SYSTEM),
	m_time(0),
	m_pop(0),
	m_interval(0),
	m_move(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObstacleManager::~CObstacleManager()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CObstacleManager::Init()
{
	m_time = 0;
	m_interval = MAX_INTERVAL;
	m_move = 1.0f;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObstacleManager::Uninit()
{
	// 破棄
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObstacleManager::Update()
{
	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	int time = pGame->GetTime();
	if (time >= 0)
	{
		return;
	}

	m_time++;

	// ゲーム
	Game();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObstacleManager::Draw()
{
}

//--------------------------------------------------
// ゲーム
//--------------------------------------------------
void CObstacleManager::Game()
{
	if (m_time % m_interval == 0)
	{// 一定間隔
		int random = rand() % POP_MAX;

		// 生成
		CObstacle::Create(POP_POS[random], MOVE[random] * m_move, POP_ROT[random]);

		if (m_pop >= POP_INTERVAL)
		{// 最大数を越した
			
		}

		m_pop++;

		if ((m_pop % POP_INTERVAL) == 0)
		{// 最大数を越した
			//m_move += 0.05f;

			m_interval -= 3 + 2 * m_pop;

			if (m_interval <= MIN_INTERVAL)
			{// 最小値以下
				m_interval = MIN_INTERVAL;
			}
		}
	}
}
