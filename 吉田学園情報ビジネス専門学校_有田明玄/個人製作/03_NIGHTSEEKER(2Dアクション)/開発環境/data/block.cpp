//=================================================
// Content     (ブロックの設定)(Block.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/10/12)
//=================================================
#include"block.h"
#include"player.h"
#include"input.h"
#include"enemy.h"
#include"boss.h"
//スタティック変数
static bool btexture;		//テクスチャを張るかどうか
static LPDIRECT3DTEXTURE9 s_pTextureBlock = NULL;		//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffBlock = NULL;	//頂点バッファへのポインタ
static Block s_aBlock[MAX_BLOCK];						//ブロックの情報
static bool bStopBlock;									//ブロックの動きを止めるかどうか
	
//スタティック関数
static void SetBlockType(int nType, int BlockNumber);
//============================
//ブロックの初期化処理
//============================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.jpg",
		&s_pTextureBlock);

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		s_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aBlock[nCntBlock].bUse = false;	//使用していない状態にする
		s_aBlock[nCntBlock].fHeight = 0.0f;
		s_aBlock[nCntBlock].fWidth = 0.0f;
	}

	btexture = true;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBlock,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	s_pVtxBuffBlock->Unlock();
}
//============================
//ブロックの終了処理
//============================
void UninitBlock(void)
{
	//テクスチャの破棄
	if (s_pTextureBlock != NULL)
	{
		s_pTextureBlock->Release();
		s_pTextureBlock = NULL;
	}
	//頂点バッファを破棄
	if (s_pVtxBuffBlock != NULL)
	{
		s_pVtxBuffBlock->Release();
		s_pVtxBuffBlock = NULL;
	}
}
//============================
//ブロックの更新処理
//============================
void UpdateBlock(void)
{
	int nCntBlock;
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//1キーををしたときテクスチャをはがす
	 if (GetKeyboardTrigger(DIK_1) == true)
	{
		 btexture= !btexture;
	}
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている
			//前回の位置を記録
			s_aBlock[nCntBlock].posold = s_aBlock[nCntBlock].pos;
			
			if (bStopBlock == false)
			{
				//画面の中央に来た時の設定
				CenterPlayer(&s_aBlock[nCntBlock].pos);
			}
			
			//位置の更新
			s_aBlock[nCntBlock].pos += s_aBlock[nCntBlock].move;

			//プレイヤーの当たり判定
			CollisionPlayer(&s_aBlock[nCntBlock].pos, &s_aBlock[nCntBlock].posold, &s_aBlock[nCntBlock].move, s_aBlock[nCntBlock].fWidth, s_aBlock[nCntBlock].fHeight);

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[1].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[2].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[3].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	s_pVtxBuffBlock->Unlock();
}
//==============================
//ブロックの描画処理
//==============================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	if (btexture == true)
	{
		pDevice->SetTexture(0, s_pTextureBlock);
	}
	else if(btexture == false)
	{
		pDevice->SetTexture(0, NULL);
	}
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている

		 //ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				nCntBlock * 4,							//頂点の開始場所
				2);										//プリミティブの数
		}
	}
}
//=====================
//ブロックの設定処理
//=====================
void SetBlock(D3DXVECTOR3 pos, float Width, float Height,int Type)
{
	int nCntBlock;
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない
			s_aBlock[nCntBlock].pos = pos;
			s_aBlock[nCntBlock].fHeight = Height;
			s_aBlock[nCntBlock].fWidth = Width;
			s_aBlock[nCntBlock].nType = Type;
			s_aBlock[nCntBlock].bUse = true;	//使用している状態にする

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[1].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[2].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[3].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;

			//タイプに応じて色や移動量の設定
			SetBlockType(s_aBlock[nCntBlock].nType,nCntBlock);
			break;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	s_pVtxBuffBlock->Unlock();
}
//=====================
//ブロックの当たり判定
//=====================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height,Block**pBlock)
{
	bool bIsLanding = false;		//着地しているかどうか
		bStopBlock = false;			//壁に当たっているかどうか

	//ブロックに相手がぶつかった時
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている 
			if (pPos->x + Width / 2 > s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2 /*+ DASH_SPEED*/		//ブロックの左右の設定 
				&& pPos->x - Width / 2 < s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2/*- DASH_SPEED*/)
			{
				//上から落ちて地面にめり込んだ場合(上辺)
				if (pPosOld->y <= s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2			//前回のプレイヤーの位置(y軸)がブロックの位置より高い場合
					&& pPos->y >= s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2			//現在のプレイヤーの位置(y軸)がブロックの位置より低い場合
					)//プレイヤーの左右にブロックが当たった場合
				{//プレイヤ-とブロックが当たった時
					if (pBlock!=NULL)
					{
						//プレイヤー構造体のpBlockにs_aBlockのアドレスを設定
						*pBlock = &s_aBlock[nCntBlock];
					}
					bIsLanding = true;
					pPos->y = s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2;
					pMove->y = 0;
				}
				//下から飛んでブロックにめり込んだ場合(下辺)
				else if (pPosOld->y - Height >= s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2		//前回のプレイヤーの位置がブロックの位置より低い場合
						&& pPos->y - Height <= s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2		//現在のプレイヤーの位置がブロックの位置より高い場合
					)//プレイヤーの左右にブロックが当たった場合
				{//プレイヤ-とブロックが当たった時
					pMove->y = 0;
					pPos->y = s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2 + Height;
				}
			}
			 //横からぶつかった場合
			if (pPosOld->y > s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2		//ブロックの上下の範囲指定
				&& pPosOld->y - Height < s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2)
			{
				//横からぶつかった場合(右辺)
				if (pPosOld->x - Width / 2 >= s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 		//前回のプレイヤーの位置がブロックの位置より右にいる場合
					&& pPos->x - Width / 2 < s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 		//現在のプレイヤーの位置がブロックの位置より左にいる(めり込んでいる)場合
					)//プレイヤーの左右にブロックが当たった場合
				{//プレイヤ-とブロックが当たった時
					bStopBlock = true;
					pPos->x = s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 + Width / 2;
					s_aBlock[nCntBlock].move.x = 0;
					pMove->x = 0;
				}																					
				//横からぶつかった場合(左辺)
				else if (pPosOld->x + Width / 2 <= s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2	//前回のプレイヤーの位置がブロックの位置より左にいる場合
						 && pPos->x + Width / 2 > s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2	//現在のプレイヤーの位置がブロックの位置より右にいる(めり込んでいる)場合
					)//プレイヤーの左右にブロックが当たった場合
				{//プレイヤ-とブロックが当たった時
					bStopBlock = true;
					pPos->x = s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2 - Width / 2;
					s_aBlock[nCntBlock].move.x = 0;
					pMove->x = 0;
				}
			}
			//プレイヤーの獲得処理
			Player*pPlayer = GetPlayer();
			if (s_aBlock[nCntBlock].nType== 5
				&& (pPos->y - Height <= s_aBlock[nCntBlock].pos.y
				&&pPos->x <= s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2
				&& pPos->x >= s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2
				&&&pPlayer->pos==pPos))
			{//このブロックの上を通過するとボスが登場
				SetBoss(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2, 0.0f));
			}
		}
	}
	return bIsLanding;
}
//=====================
//ブロックの種類の設定
//=====================
static void SetBlockType(int nType, int BlockNumber)
{
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	switch (nType)
	{
	case 1:
		pVtx[BlockNumber * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case 2:
		pVtx[BlockNumber * 4].col =		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	case 5:
		pVtx[BlockNumber * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
	//頂点バッファをアンロック
	s_pVtxBuffBlock->Unlock();
}
//=====================
//ブロックの取得処理
//=====================
Block *GetBlock(void)
{//エネミーのポインタをリセット
	return &s_aBlock[0];
}