#ifndef _EFFECT_H_	//このマクロ定義がされてなかったら
#define _EFFECT_H_	//二重インクルード防止のマクロ定義

#include"main.h"

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//位置
	D3DXCOLOR col;		//色
	float fRadius;		//半径(大きさ)
	int nLife;			//寿命
	bool bAdd;			//加算合成をするかどうか
	bool bUse;			//使用しているかどうかの判定
	int nType;			//テクスチャの種類
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, bool ADD, int nType);
#endif
