//=================================================
// Content     (ゲームの設定)(game.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/29)
//=================================================
#include"Player.h"
#include"input.h"
#include"background.h"
#include"enemy.h"
#include"main.h"
#include"sound.h"
#include"game.h"
#include"pause.h"
#include"result.h"
#include"mapload.h"
#include"playereffect.h"
#include"block.h"
#include"GameUI.h"
#include"Attack.h"
#include"effect.h"
#include"score.h"
#include"boss.h"
#include"bullet.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCntGameState = 0;				//ゲームの状態カウンター
bool g_bPause = false;					//ポーズ中かどうか
//============================
//ゲーム画面の初期化処理
//============================
void InitGame(void)
{
	InitBG();			//背景の初期化処理
	InitPlayer();		//プレイヤーの初期化処理
	InitEnemy();		//敵の初期化処理
	InitPause();		//ポーズの初期化処理
	InitPlayereffect();	//残像の初期化処理
	InitPlayer();		//プレイヤーの初期化処理
	InitBlock();		//ブロックの初期化処理
	InitBoss();			//ボスの初期化
	InitMapLoad();		//マップ読み込みの処理
	InitUI();			//UIの初期化処理
	InitAttack();		//攻撃エフェクトの初期化
	InitEffect();		//エフェクトの初期化
	InitScore();		//スコアの初期化処理
	InitBullet();		//弾の初期化
	SetScore(0);		//スコアの設定

	PlaySound(SOUND_LABEL_BGM000);
	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCntGameState = 0;			//カウンターをリセットする
}
//============================
//ゲーム画面の終了処理
//============================
void UninitGame(void)
{
	StopSound();
	UninitPlayer();			//プレイヤーの終了処理
	UninitEnemy();			//敵の終了処理
	UninitBG();				//背景の終了処理
	UninitPause();			//ポーズの終了処理
	UninitPlayereffect();	//残像の終了処理
	UninitBlock();			//ブロックの終了処理
	UninitUI();				//UIの終了処理
	UninitAttack();			//攻撃の終了処理
	UninitEffect();			//エフェクトの終了処理
	UninitBoss();			//ボスの終了処理
	UninitScore();			//スコアの終了処理
	UninitBullet();			//弾の終了処理
}
//============================
//ゲーム画面の更新処理
//============================
void UpdateGame(void)
{
	FADE pFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true && pFade == FADE_NONE)
	{//ポーズキー(Pキー)が押された
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_bPause = g_bPause ? false : true;
		InitPause();

	}
	if (g_bPause == false)
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:			//通常状態
		UpdateBG();				//背景の更新処理
		UpdateMapLoad();		//マップ読み込みの更新処理
		UpdatePlayer();			//プレイヤーの更新処理
		UpdateBlock();			//ブロックの更新処理
		UpdateEnemy();			//敵の更新処理
		UpdatePlayereffect();	//残像の更新処理
		UpdateUI();				//UIの更新処理
		UpdateAttack();			//攻撃エフェクトの更新処理
		UpdateEffect();			//エフェクトの更新処理
		UpdateBoss();			//ボスの更新処理
		UpdateScore();			//スコアの更新処理
		UpdateBullet();			//弾の更新処理
		break;
		case GAMESTATE_CLEAR:			//終了状態
			g_nCntGameState++;
			if (g_nCntGameState >= 60)
			{
				//g_gameState = GAMESTATE_NONE;

				//画面の設定
				SetFade(MODE_RESULT);

				g_nCntGameState = 0;	//タイマーリセット
			}
			break;
		case GAMESTATE_FAILED:			//終了状態
			g_nCntGameState++;
			if (g_nCntGameState >= 60)
			{
				//g_gameState = GAMESTATE_NONE;

				//画面の設定
				SetFade(MODE_RESULT);

				g_nCntGameState = 0;	//タイマーリセット
			}
			break;
		default:
			break;
		}
		g_nCntGameState++;	//タイマーの進行
	}
	else
	{
		UpdatePause();			//ポーズの更新処理
	}
}
//============================
//ゲーム画面の描画処理
//============================
void DrawGame(void)
{
	DrawBG();				//背景の描画処理
	DrawEnemy();			//敵の描画処理
	DrawPlayereffect();		//残像の描画処理
	DrawBlock();			//ブロックの描画処理
	DrawAttack();			//攻撃エフェクトの描画処理
	DrawPlayer();			//プレイヤーの描画処理
	DrawBoss();				//ボスの描画処理
	DrawBullet();			//弾の描画処理
	DrawEffect();			//エフェクトの描画処理
	DrawScore();			//スコアの描画処理
	DrawUI();				//UIの描画処理
	if (g_bPause==true)
	{
		DrawPause();		//ポーズの更新処理
	}
}
//============================
//ゲームの状態処理設定
//============================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntGameState = 0;
}
//============================
//ゲームの状態の取得
//============================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================
//ポーズの有効無効設定
//============================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}