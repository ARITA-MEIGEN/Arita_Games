#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"
#include"block.h"

//マクロ定義
#define NUM_ENEMY	(5)			//敵の種類
#define MAX_ENEMY	(256)		//敵の最大数
#define ENEMY_SIZE	(50.0f)		//敵の大きさ
//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX

}ENEMYSTATE;

//敵構造体の定義
typedef struct
{
	int nCntAnim;				//カウンターを初期化する
	int nPtnAnim;				//パターンNo.を初期化する
	float fLng;					//プレイヤーとの距離(対角線の長さ)
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	int nMoveType;				//移動のパターン
	int nType;					//種類
	D3DXVECTOR3 move;			//移動量
	ENEMYSTATE state;			//状態
	int nCounterState;			//状態管理カウンター
	int nLife;					//体力
	int nBullettimer;			//弾の発射間隔
	int nAtk;					//攻撃力
	bool bUse;					//使用しているかどうか
	Block*pBlock;				//ブロックのポインタ
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);									//敵の初期化処理
void UninitEnemy(void);									//敵の終了処理
void UpdateEnemy(void);									//敵の更新処理
void DrawEnemy(void);									//敵の描画処理
void SetEnemy(D3DXVECTOR3 pos, int type);				//敵の設定処理
void HitEnemy(int nCntEnemy, int nDamage);				//敵のヒット処理
Enemy *GetEnemy(void);									//敵の獲得処理
void CollisionEnemy(D3DXVECTOR3 *pPos, float Width, float Height);	//当たり判定
#endif
