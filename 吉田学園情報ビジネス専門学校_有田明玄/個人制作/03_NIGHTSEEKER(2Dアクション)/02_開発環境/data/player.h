//=================================================
// Content     (プレイヤーの操作)(player.h)
// Author     : 有田明玄
// Since      : (作成日2021/10/04)
//=================================================
#ifndef _PLAYER_H_			//このマクロ定義がされてなかったら
#define _PLAYER_H_			//二重インクルード防止のマクロ定義

#include "main.h"	
#include"block.h"

//マクロ定義
#define MAX_KEYMEMORY		(10)		//キーの最大記録数(コマンド技用)
#define MIN_SPEED			(0.1f)		//摩擦による最低速度
#define DASH_SPEED			(0.9f)		//ダッシュ時の速度
#define NOMAL_SPEED			(0.5f)		//通常時の速度
#define COLLISION_PLAYER	(0.6f)		//キャラクターの当たり判定調整用
#define MAX_PATTERN			(4.0f);		//テクスチャのパターン数
#define PLAYER_HEIGHT		(60.0f)		//プレイヤーの高さ
#define PLAYER_WIDTH		(35.0f)		//プレイヤーの幅
#define TEX_X				(0.05f)		//テクスチャの大きさ調整用
#define TEX_Y				(0.2f)		//テクスチャの大きさ調整用
#define	FIRST_ATKTIME		(5)			//最初のモーションの時間
#define ALL_ATKTIME1		(20)		//技の全体の時間
#define MAX_PLIFE			(4000)		//最大ライフ

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態(点滅)
	PLAYERSTATE_NORMAL,		//通常状態
	PLAYERSTATE_ATTACK,		//攻撃状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3	posOld;			//前回の位置
	D3DXVECTOR3 move;			//移動量
	int nCntCounterAnim;		//カウンター
	int nCntPtnAnim;			//パターン番号
	int nDirectionMove;			//向き	０の時は右　１の時は左向き
	D3DXVECTOR3 rot;			//向き
	bool bIsJumping;			//ジャンプ中かどうか
	bool bIsDashing;			//ダッシュ中かどうか
	bool bDisp;					//使用中かどうか
	float fPtnflashing;			//点滅用
	int nCntState;				//状態管理カウンター
	int nLife;					//体力
	PLAYERSTATE state;			//プレイヤーの状態設定
	Block*pBlock;				//着地しているブロックのアドレスを保存
	int nCntAtk;				//攻撃回数
	int nAtkTimer;				//攻撃の時間間隔
	bool bAtk;					//攻撃してるかどうか
}Player;

//プロトタイプ宣言
void InitPlayer(void);						//プレイヤーの初期化処理
void UninitPlayer(void);					//プレイヤーの終了処理
void UpdatePlayer(void);					//プレイヤーの更新処理
void DrawPlayer(void);						//プレイヤーの描画処理
void SetPlayer(D3DXVECTOR3 pos);			//プレイヤーの設置
Player *GetPlayer(void);					//プレイヤーの情報の獲得
void CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height);	//プレイヤーの当たり判定
void HitPlayer(int nDamage);				//プレイヤーに攻撃が当たった時の処理
void CenterPlayer(D3DXVECTOR3 *pPos);		//プレイヤーが中心に来た時の処理

#endif 
