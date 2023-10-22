#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"	
#include"input.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//ポーズの状態
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,		//コンティニュー点滅
	PAUSE_MENU_RETRY,			//リトライ点滅
	PAUSE_MENU_QUIT,			//タイトル点滅
	PAUSE_MENU_MAX
}PAUSE_MENU;

//プロトタイプ宣言
void InitPause(void);	//背景の初期化処理
void UninitPause(void);//背景の終了処理
void UpdatePause(void);//背景の更新処理
void DrawPause(void);	//背景の描画処理

#endif 
