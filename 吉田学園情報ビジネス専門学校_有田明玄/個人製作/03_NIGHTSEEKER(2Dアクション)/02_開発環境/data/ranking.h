#ifndef _RANKING_H_
#define _RANKING_H_

#include"main.h"
#include"fade.h"
#include"input.h"

//マクロ定義
#define MAX_RANK			(5)		//ランク数
#define MAX_SCORE			(8)		//スコアの桁数
#define NUM_RANK			(2)		//ランキングのスコア以外の数

//プロトタイプ宣言
void InitRanking(void);				//ランキングの初期化処理
void UninitRanking(void);			//ランキングの終了処理
void UpdateRanking(void);			//ランキングの更新処理
void DrawRanking(void);				//ランキングの描画処理
void ResetRanking(void);			//ランキングのリセット
void SetRanking(void);				//ランキングの設定
void SaveRanking(void);				//ランキングの保存
void LoadRanking(void);				//ランキングの読み込み


#endif