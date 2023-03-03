//=============================================================================
//
// 敵(ボス1)
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"sound.h"
#include"Explosion.h"
#include"Boss.h"
#include"Score.h"
#include"Enemy.h"
#include"Fade.h"
#include"Effect.h"
#include"Game.h"


//静的メンバ変数宣言	
CBoss::BOSSSTATE CBoss::m_BossState = BOSSSTATE_NONE;
//=============================================================================
// コンストラクタ
//=============================================================================
CBoss::CBoss()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CBoss::~CBoss()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CBoss::Init(float Width, float Height)
{
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -255.0f, 0.0f);
	m_nLife = MAX_BOSSLIFE;
	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//素体
	m_pBossbase = CEnemy::Create(CEnemy::MOVE_BOSS_BASE, m_pos);

	//固定砲台
	m_apBossCannon[0] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x - 120.0f, m_pos.y + 75.0f, 0.0f));
	m_apBossCannon[1] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x + 120.0f, m_pos.y + 75.0f, 0.0f));
	m_apBossCannon[2] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x - 295.0f, m_pos.y + 65.0f, 0.0f));
	m_apBossCannon[3] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x + 295.0f, m_pos.y + 65.0f, 0.0f));

	//自機狙い
	m_apBossATCannon[0] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y + 60.0f, 0.0f));
	m_apBossATCannon[1] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x - 200.0f, m_pos.y + 60.0f, 0.0f));
	m_apBossATCannon[2] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y + 40.0f, 0.0f));
	m_apBossATCannon[3] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y + 40.0f, 0.0f));

	//コアビーム
	m_pBossCoreCannon = CEnemy::Create(CEnemy::MOVE_BOSS_CORECANNON, D3DXVECTOR3(m_pos.x, m_pos.y + 105.0f, 0.0f));
	//コア
	m_apBossCore[0] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x + 255.0f, m_pos.y - 30.0f, 0.0f));
	m_apBossCore[1] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x - 255.0f, m_pos.y - 30.0f, 0.0f));
	m_apBossCore[2] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x + 505.0f, m_pos.y - 20.0f, 0.0f));
	m_apBossCore[3] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x - 505.0f, m_pos.y - 20.0f, 0.0f));
	m_BossState = BOSSSTATE_APPEAR;

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CBoss::Uninit()
{
	m_BossState = BOSSSTATE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//座標をリセット(しないと最初っから画面内扱いになるので)
	CObject::Release();
}

//=============================================================================
// 更新
//=============================================================================
void  CBoss::Update()
{
	if (m_BossState == BOSSSTATE_APPEAR)
	{
		m_pos.y += m_move.y;
	}

	if (m_nLife <= 4 && m_frame % 600 == 0)
	{
		CEnemy::Create(CEnemy::MOVE_004, D3DXVECTOR3(-200.0f, SCREEN_HEIGHT / 2, 0.0f));
		CEnemy::Create(CEnemy::MOVE_005, D3DXVECTOR3(SCREEN_WIDTH + 200.0f, SCREEN_HEIGHT / 2, 0.0f));

	}
	if (m_nLife <= 1 && m_frame % 360 == 0)
	{//左右の上から斜め方向に降りてくる
		CEnemy::Create(CEnemy::MOVE_006, D3DXVECTOR3(-100.0f,0.0f, 0.0f));
		CEnemy::Create(CEnemy::MOVE_007, D3DXVECTOR3(SCREEN_WIDTH + 100.0f, -0.0f, 0.0f));
	}

	InScreen();
	SetPos();
	StateManager();
	m_time--;
	m_frame++;
}

//=============================================================================
// 描画
//=============================================================================
void  CBoss::Draw()
{

}

//=============================================================================
// 敵生成
//=============================================================================
CBoss* CBoss::Create()
{
	CBoss*pBoss;
	pBoss = new CBoss;
	pBoss->Init(0.0f, 0.0f);
	StopSound(SOUND_LABEL_STAGE001);
	PlaySound(SOUND_LABEL_SE_SIREN);
	return pBoss;
}

//=============================================================================
// ダメージ設定
//=============================================================================
void CBoss::CoreDamage()
{
	//ダメージ処理                                                           
  	m_nLife--;
	if (m_nLife <= 0)
	{
		m_BossState = BOSSSTATE_DEATH;
		CGame::GetScore()-> AddScore(100000);
		CApplication::StopTime(60);
		CApplication::SlowTime(true);			//スローにする
		m_time = NEXT_BOSS_TIME;				//フェードまでの時間
		CGame::SetGame(CGame::GAME_END);
	}
	PlaySound(SOUND_LABEL_SE_EXPLOSION003);
	CGame::GetScore()->AddScore(50000);
}

//=============================================================================
// 状態管理
//=============================================================================
void CBoss::StateManager()
{
	switch (m_BossState)
	{
	case CBoss::BOSSSTATE_DEATH:
		if (m_time == NEXT_BOSS_TIME - 1)
		{//死んで最初の1fだけ通る
			for (int i = 0; i < 20; i++)
			{//爆発
				CEffect::Create(m_pBossbase->GetPos(),																//位置
					D3DXVECTOR2(m_pBossbase->GetSiz().y/2, m_pBossbase->GetSiz().y/2),								//大きさ
					m_pBossbase->GetRot(),																			//向き
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10+5) / 1.0f + 00.0f,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10+5) / 1.0f + 0.0f,			//y
						0.0f),																						//z
					600,																							//寿命
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 5.0f));															//色
			}
			//素体
			m_pBossbase->Uninit();

			//爆発処理
			for (int i = 0; i < MAX_CANNON; i++)
			{
				if (m_apBossCannon[i] != nullptr)
				{
					//固定砲台
					m_apBossCannon[i]->Uninit();
				}
			}

			for (int i = 0; i < MAX_ATCANNON; i++)
			{
				if (m_apBossCannon[i] != nullptr)
				{
					//自機狙い
					m_apBossATCannon[i]->Uninit();
				}
			}
			PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		}

		if (m_time <= 0)
		{
			if (CFade::Get() == CFade::FADE_NONE)
			{
				m_BossState = BOSSSTATE_APPEAR;
				CFade::Set(CApplication::MODE_RESULT);
			}
		}
		break;
	}
}

//=============================================================================
// 画面外から画面内に入った時の処理(登場時)
//=============================================================================
void CBoss::InScreen()
{
	if (m_pos.y >= 75.0f&&m_BossState==BOSSSTATE_APPEAR)
	{
		StopSound();
		PlaySound(SOUND_LABEL_STAGE001BOSS);
		m_move.y = 0.0f;
		m_BossState = BOSSSTATE_NORMAL;
	}
}

//=============================================================================
//座標更新
//=============================================================================
void CBoss::SetPos()
{
	//素体
	m_pBossbase ->SetPos (m_pos);

	//固定砲台
	m_apBossCannon[0]->SetPos( D3DXVECTOR3(m_pos.x - 120.0f, m_pos.y + 75.0f+75.0f, 0.0f));
	m_apBossCannon[1]->SetPos(D3DXVECTOR3(m_pos.x + 120.0f, m_pos.y + 75.0f + 75.0f, 0.0f));
	m_apBossCannon[2]->SetPos(D3DXVECTOR3(m_pos.x - 295.0f, m_pos.y + 65.0f + 75.0f, 0.0f));
	m_apBossCannon[3]->SetPos(D3DXVECTOR3(m_pos.x + 295.0f, m_pos.y + 65.0f + 75.0f, 0.0f));

	//自機狙い
	m_apBossATCannon[0]->SetPos(D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y + 60.0f + 75.0f, 0.0f));
	m_apBossATCannon[1]->SetPos(D3DXVECTOR3(m_pos.x - 200.0f, m_pos.y + 60.0f + 75.0f, 0.0f));
	m_apBossATCannon[2]->SetPos(D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y + 40.0f + 75.0f, 0.0f));
	m_apBossATCannon[3]->SetPos(D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y + 40.0f + 75.0f, 0.0f));

	//コアビーム
	m_pBossCoreCannon->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 105.0f + 75.0f, 0.0f));
	//コア
	m_apBossCore[0]->SetPos(D3DXVECTOR3(m_pos.x + 255.0f, m_pos.y - 30.0f + 75.0f, 0.0f));
	m_apBossCore[1]->SetPos(D3DXVECTOR3(m_pos.x - 255.0f, m_pos.y - 30.0f + 75.0f, 0.0f));
	m_apBossCore[2]->SetPos(D3DXVECTOR3(m_pos.x + 505.0f, m_pos.y - 20.0f + 75.0f, 0.0f));
	m_apBossCore[3]->SetPos(D3DXVECTOR3(m_pos.x - 505.0f, m_pos.y - 20.0f + 75.0f, 0.0f));
}

//=============================================================================
// 画面外から画面内に入った時の処理(登場時)
//=============================================================================
CBoss::BOSSSTATE CBoss::GetState()
{
	return m_BossState;
}

//=============================================================================
// 体力の取得
//=============================================================================
int CBoss::GetLife()
{
	return m_nLife;
}
