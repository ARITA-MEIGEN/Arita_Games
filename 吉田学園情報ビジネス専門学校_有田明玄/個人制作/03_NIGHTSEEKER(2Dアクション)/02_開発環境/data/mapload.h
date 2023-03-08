//=================================================
// Content     (プレイヤーの操作)(mapload.h)
// Author     : 有田明玄
// Since      : (作成日2021/10/04)
//=================================================
#ifndef _MAPLOAD_H_			//このマクロ定義がされてなかったら
#define _MAPLOAD_H_			//二重インクルード防止のマクロ定義

#include "main.h"	


//ブロック構造体の定義
typedef enum
{
	BLOCK_NONE = 0,
	BLOCK_BLOWN,
	BLOCK_MAX
}BLOCKTYPE;

//プロトタイプ宣言
void InitMapLoad(void);				//マップ読み込みの初期化処理
void UpdateMapLoad(void);			//マップ読み込みの更新処理

#endif 

