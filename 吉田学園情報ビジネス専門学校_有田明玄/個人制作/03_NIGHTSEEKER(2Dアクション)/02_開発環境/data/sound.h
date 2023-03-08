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
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3
	SOUND_LABEL_BGM004,				// BGM4
	SOUND_LABEL_SE_EXPLOSION,		// 爆発音
	SOUND_LABEL_SE_SWORDATTACK,		//剣の攻撃音
	SOUND_LABEL_SE_HITSWORDATTACK,	//剣が当たった時の音
	SOUND_LABEL_SE_HIT,				//プレイヤーがダメージを受けた時の音
	SOUND_LABEL_SE_START,			//スタート
	SOUND_LABEL_SE_SELECT,			//選択
	SOUND_LABEL_SE_BOSS,			//ボス登場
	SOUND_LABEL_SE_FIRE,			//ボスの攻撃
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
