//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include"main.h"
#include"Application.h"
#include"Game.h"
#include"Player.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Enemy.h"
#include"Option.h"
#include"Bg.h"
#include"Effect.h"
#include"Item.h"
#include"Score.h"
#include"Lifegauge.h"
#include"Mapdata.h"
#include"sound.h"
#include"Special.h"
#include"EnemyManager.h"
#include"Boss.h"
#include"InputKeyBoard.h"
#include"InputJoyPad.h"
#include"Fade.h"

//静的メンバ変数
CPlayer*CGame::m_pPlayer = nullptr;
CExplosion*CGame::m_pExplosion = nullptr;
CEnemy*CGame::m_pEnemy = nullptr;
CBg*CGame::m_pBg = nullptr;
CScore*CGame::m_pScore = nullptr;
CLife*CGame::m_Life= nullptr;				//体力ゲージ
CMapdata* CGame::m_pMap = nullptr;
CSpecial*CGame::m_pSpecial=nullptr;
CGame::GAME CGame::m_gamestate;
//====================================
//コンストラクタ
//====================================
CGame::CGame()
{
}

//====================================
//デストラクタ
//====================================
CGame::~CGame()
{

}

//====================================
//初期化
//====================================
HRESULT CGame::Init()
{
	//テクスチャの読み込み
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	COption::Load();
	CBg::Load();
	CEffect::Load();
	CItem::Load();
	CScore::Load();
	CLife::Load();
	CSpecial::Load();

	//マップデータ読み込み
	m_pMap = new CMapdata;
	m_pMap->Load();

	//背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_GAME);
	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));

	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 460.0f, 35.0f, 0));
	m_pScore->SetScore(0);

	//必殺技ゲージ
	m_pSpecial = CSpecial::Create(D3DXVECTOR3(SCREEN_WIDTH/2, 35.0f, 0));

	m_gamestate = GAME_NORMAL;

	//体力
	m_Life = CLife::Create();

	PlaySound(SOUND_LABEL_STAGE001);

	return S_OK;
}

//====================================
//終了
//====================================
void CGame::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}
	if (m_pExplosion != nullptr)
	{
		m_pExplosion->Uninit();
		m_pExplosion = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	if (m_Life != nullptr)
	{
		m_Life->Uninit();
		m_Life = nullptr;
	}
	
	//テクスチャの破棄
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CPlayer::Unload();
	COption::Unload();
	CBg::Unload();
	CEffect::Unload();
	CItem::Unload();
	CScore::Unload();
	CLife::Unload();
}

//====================================
//更新
//====================================
void CGame::Update()
{
#ifdef _DEBUG
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_T) == true)
	{
		CItem::Create(CItem::ITEM_HEALING, D3DXVECTOR3(640.0f, 100.0f, 0.0f));
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_E) == true)
	{
		CEnemy::Create((CEnemy::MOVEPATTERN)4, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if ((pKeyboard->GetTrigger(DIK_RETURN) == true || pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true)
		&& CFade::Get() == CFade::FADE_NONE)		//ENTERキー
	{//エンターでリザルト画面に
	 //モード設定
		CFade::Set(CApplication::MODE_RESULT);
	}

#endif // !_DEBUG
	m_pMap->Update();
}

//====================================
//描画
//====================================
void CGame::Draw()
{

}

//====================================
//プレイヤーの取得
//====================================
CPlayer * CGame::GetPlayer()
{
	return m_pPlayer;
}

//====================================
//爆発の取得
//====================================
CExplosion * CGame::GetExplosion()
{
	return m_pExplosion;
}

//====================================
//敵の取得
//====================================
CEnemy * CGame::GetEnemy()
{
	return m_pEnemy;
}

//====================================
//背景の取得
//====================================
CBg * CGame::GetBg()
{
	return m_pBg;
}

//====================================
//スコアの取得
//====================================
CScore * CGame::GetScore()
{
	return m_pScore;
}

//====================================
//ゲームの状態設定
//====================================
void CGame::SetGame(GAME gamestate)
{
	m_gamestate = gamestate;
}

//====================================
//ゲームの状態獲得
//====================================
CGame::GAME CGame::GetGame()
{
	return m_gamestate;
}
