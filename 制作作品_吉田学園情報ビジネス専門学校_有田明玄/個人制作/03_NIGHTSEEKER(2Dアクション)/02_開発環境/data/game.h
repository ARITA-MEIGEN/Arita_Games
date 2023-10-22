#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//二重インクルード防止のマクロ定義

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE=0,	//何もしていない状態
	GAMESTATE_NORMAL,	//通常状態
	GAMESTATE_BOSS,		//ボス戦
	GAMESTATE_CLEAR,	//ゲームクリア状態
	GAMESTATE_FAILED,	//ゲームオーバー状態
	GAMESTATE_PAUSE,	//停止状態
	GAMESTATE_MAX
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void);
void UpdateGame(void);
void UninitGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);

#endif