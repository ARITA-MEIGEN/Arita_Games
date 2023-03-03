#ifndef _BOSS_H_
#define _BOSS_H_

#include"main.h"
#include"block.h"

//マクロ定義
#define NUM_BOSS	(2)			//ボスの種類
#define MAX_BOSS	(256)		//ボスの最大数
#define BOSS_SIZE	(300.0f)		//ボスの大きさ
//ボスの状態
typedef enum
{
	BOSSSTATE_APPEAR = 0,	//出現状態(点滅)
	BOSSSTATE_NORMAL,		//通常状態
	BOSSSTATE_DAMAGE,		//ダメージ状態
	BOSSSTATE_DEATH,		//死亡状態
	BOSSSTATE_MAX

}BOSSSTATE;

//ボス構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 move;			//移動量
	BOSSSTATE state;			//状態
	float fLng;					//プレイヤーとの距離(対角線の長さ)
	int nType;					//種類
	int nCntAnim;				//カウンターを初期化する
	int nPtnAnim;				//パターンNo.を初期化する
	int nCounterState;			//状態管理カウンター
	int nMoveType;				//移動のパターン
	int nDirectionMove;			//向き	０の時は右　１の時は左向き
	int nLife;					//体力
	int nAtkUse;				//攻撃中かどうか
	int nAtk;					//攻撃力
	bool bUse;					//使用しているかどうか
	Block*pBlock;				//ブロックのポインタ
}BOSS;

//プロトタイプ宣言
void InitBoss(void);									//ボスの初期化処理
void UninitBoss(void);									//ボスの終了処理
void UpdateBoss(void);									//ボスの更新処理
void DrawBoss(void);									//ボスの描画処理
void SetBoss(D3DXVECTOR3 pos);							//ボスの設定処理
void HitBoss(int nDamage);								//ボスのヒット処理
BOSS *GetBoss(void);									//ボスの獲得処理
//ボスの当たり判定
void CollisionBoss(D3DXVECTOR3 *pPos, float Width, float Height);

#endif

