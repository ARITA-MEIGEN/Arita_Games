//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,			// タイトル画面
	SOUND_LABEL_STAGE001,			// BGM0
	SOUND_LABEL_STAGE001BOSS,		// BGM1
	SOUND_LABEL_STAGE002,			// BGM2
	SOUND_LABEL_RESULT,				// リザルト画面
	SOUND_LABEL_SE_REDBEAM,			// 赤ビーム
	SOUND_LABEL_SE_BLUEMISSILE,		// 青ミサイル
	SOUND_LABEL_SE_FUSIONSHOT,		// 合体ビーム
	SOUND_LABEL_SE_GAMESTART,		// スタート
	SOUND_LABEL_SE_EXPLOSION001,	// 爆発音(プレイヤー)
	SOUND_LABEL_SE_EXPLOSION002,	// 爆発音(被弾)
	SOUND_LABEL_SE_EXPLOSION003,	// 爆発音(雑魚)
	SOUND_LABEL_SE_EXPLOSION004,	// 爆発音(ミサイル着弾)
	SOUND_LABEL_SE_EXPLOSION005,	// 被弾音(ゲームオーバー)
	SOUND_LABEL_SE_UNION,			// 合体
	SOUND_LABEL_SE_SEPARATION,		// 分離
	SOUND_LABEL_SE_HEAL,			// 回復
	SOUND_LABEL_SE_SIREN,			// ボス戦開始
	SOUND_LABEL_SE_CHARGE,			// 主砲チャージ
	SOUND_LABEL_SE_BOSSCANNON,		// 主砲発射
	SOUND_LABEL_SE_DELETEBULLET,	// 弾を消したときの音

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
