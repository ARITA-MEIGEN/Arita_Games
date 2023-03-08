//=================================================
// Content     (弾丸の設定)(bullet.cpp)
// Author     : 有田明玄
//=================================================
#include "bullet.h"	
#include"effect.h"
#include"Player.h"
#include "enemy.h"
#include"boss.h"

//マクロ定義
#define MAX_BULLET			(5120)	//弾の最大数
#define PBULLET_SIZE		(15)	//プレイヤーの弾のサイズ
#define EBULLET_SIZE		(5)		//敵の弾のサイズ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報
													//============================
													//弾の初期化処理
													//============================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].nDamage = 0;
		g_aBullet[nCntBullet].fHeight = 0.0f;
		g_aBullet[nCntBullet].fWidth = 0.0f;
		g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth/2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//============================
//弾の終了処理
//============================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//============================
//弾の更新処理
//============================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].pos.y <= -g_aBullet[nCntBullet].fHeight)
			{//画面外に出た場合の処理(上端)
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}
			else if (g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT + g_aBullet[nCntBullet].fHeight)
			{//画面外に出た場合の処理(下端)
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}
			else if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH + g_aBullet[nCntBullet].fWidth)
			{//画面外に出た場合の処理(右端)
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}
			else if (g_aBullet[nCntBullet].pos.x <= -g_aBullet[nCntBullet].fWidth)
			{//画面外に出た場合の処理(左端)
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}
			//弾の寿命のカウントダウン
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}

			//弾の更新
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

			//テクスチャの設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), g_aBullet[nCntBullet].fHeight, 10, true, 1);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//==============================
//弾の描画処理
//==============================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている

		 //ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				nCntBullet * 4,							//頂点の開始場所
				2);										//プリミティブの数
		}
	}
}
//=====================
//弾の設定処理
//=====================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int Damage,float Width,float Height)
{
	int nCntBullet;
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].fWidth = Width;
			g_aBullet[nCntBullet].fHeight = Height;
			g_aBullet[nCntBullet].nDamage = Damage;
			g_aBullet[nCntBullet].bUse = true;	//使用している状態にする
			g_aBullet[nCntBullet].nLife = 500;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

			//敵が使用されている
			SetHorming(nCntBullet);
			break;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//=====================
//ホーミング弾の設定処理
//=====================
void SetHorming(int CntBullet)
{//ホーミングの設定
	int nCntBullet;
	nCntBullet = CntBullet;
	Player *pPlayer = GetPlayer(); //ポインタ

	float fRotMove, fRotDest, fRotDiff;

	//現在の移動方向(角度)
	fRotMove = atan2f(g_aBullet[nCntBullet].move.x, g_aBullet[nCntBullet].move.y);			
	//目的の移動方向(角度)	相手の座標から自分を引くかんじ
	fRotDest = atan2f(pPlayer->pos.x - g_aBullet[nCntBullet].pos.x, (pPlayer->pos.y-PLAYER_HEIGHT/2-20.0f) - g_aBullet[nCntBullet].pos.y);		
	//目的の移動方向までの差分
	fRotDiff = fRotDest - fRotMove;															

	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= D3DX_PI * 2;
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2;
	}

	fRotMove += fRotDiff*1.0f;	//移動方向(角度)の補正

	if (fRotMove > D3DX_PI)
	{
		fRotMove -= D3DX_PI * 2;
	}
	else if (fRotMove < -D3DX_PI)
	{
		fRotMove += D3DX_PI * 2;
	}

	g_aBullet[nCntBullet].move.x = sinf(fRotMove)*4.0f;
	g_aBullet[nCntBullet].move.y = cosf(fRotMove)*4.0f;
}
//=====================
//弾の当たり判定処理
//=====================
void CollisionBullet(D3DXVECTOR3 *pPos, float Width, float Height)
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse==true)
		{//敵が使用されている
			if ( pPos->y  >= g_aBullet[nCnt].pos.y - g_aBullet[nCnt].fHeight / 2 			//上端
				&& pPos->y - Height <= g_aBullet[nCnt].pos.y + g_aBullet[nCnt].fHeight / 2					//下端
				&&  pPos->x + Width / 2 >= g_aBullet[nCnt].pos.x - g_aBullet[nCnt].fWidth / 2		//左端
				&& pPos->x - Width / 2 <= g_aBullet[nCnt].pos.x + g_aBullet[nCnt].fWidth / 2)		//右端
			{//プレイヤーに弾が当たった時
			 //プレイヤーのヒット処理
				HitPlayer(g_aBullet[nCnt].nDamage);
				g_aBullet[nCnt].bUse = false;			//使用していない状態
			}
		}
	}
}
//=====================
//バレットの取得処理
//=====================
Bullet *GetBullet(void)
{//エネミーのポインタをリセット
	return &g_aBullet[0];
}