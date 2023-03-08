//=================================================
// Content     (UIの設定)(UI.h)
// Author     : 有田明玄
// Since      : (作成日2021/11/01)
//=================================================
#ifndef _GAMEUI_H_			//このマクロ定義がされてなかったら
#define _GAMEUI_H_			//二重インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
#define		NUM_LIFE	(2)//体力ゲージに使うテクスチャの枚数
//UI構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
}LifeUI;

//プロトタイプ宣言
void InitUI(void);				//UIの初期化処理
void UninitUI(void);			//UIの終了処理
void UpdateUI(void);			//UIの更新処理
void DrawUI(void);				//UIの描画処理
#endif 

