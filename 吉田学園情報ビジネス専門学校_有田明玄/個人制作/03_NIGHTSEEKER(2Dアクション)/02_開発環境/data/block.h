//=================================================
// Content     (ブロックの設定)(Block.h)
// Author     : 有田明玄
// Since      : (作成日2021/10/12)
//=================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//マクロ定義
#define MAX_BLOCK		(5120)	//ブロックの最大数

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//現在の発射位置
	D3DXVECTOR3 posold;	//前回の発射位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//色
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//種類
	bool death;			
	bool bUse;			//使用しているかどうかの判定
}Block;

//プロトタイプ宣言
void InitBlock(void);											        //ブロックの初期化処理
void UninitBlock(void);													//ブロックの終了処理
void UpdateBlock(void);													//ブロックの更新処理
void DrawBlock(void);													//ブロックの描画処理
void SetBlock(D3DXVECTOR3 pos, float Width, float Height,int Type);		//ブロックの設置
Block *GetBlock(void);													//ブロックの情報の獲得
//ブロックの当たり判定
bool CollisionBlock(D3DXVECTOR3 *pPos,		//現在の位置
					D3DXVECTOR3 *pPosOld,	//前回の位置
					D3DXVECTOR3 *pMove,		//移動量
					float Width,			//幅
					float fHeight,			//高さ
					Block**pBlock);			
#endif 

