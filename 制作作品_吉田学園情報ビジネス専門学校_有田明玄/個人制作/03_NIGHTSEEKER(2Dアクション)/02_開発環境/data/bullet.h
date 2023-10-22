//=================================================
// Content     (弾丸の設定)(bullet.h)
// Author     : 有田明玄
//=================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//発射位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//横幅
	float fHeight;		//縦幅
	int nLife;			//寿命
	int nDamage;		//ダメージ量
	bool bUse;			//使用しているかどうかの判定
}Bullet;

//プロトタイプ宣言
void InitBullet(void);				//弾の初期化処理
void UninitBullet(void);			//弾の終了処理
void UpdateBullet(void);			//弾の更新処理
void DrawBullet(void);				//弾の描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int Damage, float Width, float Height);	//弾の設置
void SetHorming(int CntBullet);		//弾のホーミングの設定
Bullet *GetBullet(void);			//弾の情報の獲得
void CollisionBullet(D3DXVECTOR3 *pPos, float Width, float Height);	//弾の当たり判定

#endif 


