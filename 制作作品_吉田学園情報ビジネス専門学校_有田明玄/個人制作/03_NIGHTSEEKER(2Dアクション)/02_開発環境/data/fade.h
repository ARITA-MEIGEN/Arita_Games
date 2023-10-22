#ifndef _FADE_H_
#define _FADE_H_

#include"main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0,	//何もしていない状態
	FADE_IN,		//フェードイン状態
	FADE_OUT,		//フェードアウト状態
	FADE_MAX,
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);	//フェードの初期化処理
void UninitFade(void);			//フェードの終了処理
void UpdateFade(void);			//フェードの更新処理
void DrawFade(void);			//フェードの描画処理
void SetFade(MODE modeNext);	//フェードの設定処理
FADE GetFade(void);				//フェードの獲得処理

#endif
