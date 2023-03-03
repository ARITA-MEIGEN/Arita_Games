#ifndef _PLAYEREFFECT_H_	//このマクロ定義がされてなかったら
#define _PLAYEREFFECT_H_	//二重インクルード防止のマクロ定義

#include"main.h"
//プロトタイプ宣言
void InitPlayereffect(void);		//残像の初期化処理
void UninitPlayereffect(void);		//残像の終了処理
void UpdatePlayereffect(void);		//残像の更新処理
void DrawPlayereffect(void);		//残像の描画処理

//残像の設定処理
void SetPlayereffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight, int nLife, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d);
#endif
