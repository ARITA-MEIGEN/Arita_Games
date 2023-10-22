#ifndef _ATTACK_H_	//このマクロ定義がされてなかったら
#define _ATTACK_H_	//二重インクルード防止のマクロ定義

#include"main.h"
//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置
	D3DXCOLOR col;		//色
	int nCntAnim;		//エフェクトのカウンター
	int nPtnAnim;		//アニメーションの番号
	float fRadiuswidth;	//横幅
	float fRadiusheight;//縦幅
	bool bUse;			//使用しているかどうかの判定
	int nDirection;		//向き
}Attack;

//武器構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	D3DXCOLOR col;				//色
	float fLength;				//対角線の長さ
	float fAngle;				//対角線の角度
	int  nLife;					//寿命
	bool bCollision;			//当たり判定の使用の有無
	bool bDisp;					//使用しているかどうかの判定
}Weapon;

//プロトタイプ宣言
void InitAttack(void);		//攻撃エフェクトの初期化処理
void UninitAttack(void);	//攻撃エフェクトの終了処理
void UpdateAttack(void);	//攻撃エフェクトの更新処理
void DrawAttack(void);		//攻撃エフェクトの描画処理

//攻撃エフェクトの設定処理
void SetAttack(float posx, float posy, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight,int nDirection);
//武器の設定処理
void Setweapon(float posx, float posy, float posz, D3DXCOLOR col, int Life, bool collision);
//武器の当たり判定
bool CollisionWeapon(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height);


#endif
