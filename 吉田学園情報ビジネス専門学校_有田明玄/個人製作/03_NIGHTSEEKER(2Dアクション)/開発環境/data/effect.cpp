//=================================================
// Content     (エフェクトの処理)(effect.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/09/07)
//=================================================
#include"effect.h"
#include"player.h"

//マクロ定義
#define MAX_EFFECT		(91920)	//エフェクトの最大数
#define NUM_EFFECT		(3)		//エフェクトの枚数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEffect[NUM_EFFECT] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];							//エフェクトの情報
//============================
//エフェクトの初期化処理
//============================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bat000.png",
		&g_apTextureEffect[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_apTextureEffect[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//敵の情報の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
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

		g_aEffect[nCntEffect].pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aEffect[nCntEffect].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0;				//半径(大きさ)
		g_aEffect[nCntEffect].nLife = 0;				//寿命
		g_aEffect[nCntEffect].bUse = false;				//使用しているかどうかの判定
		g_aEffect[nCntEffect].bAdd = false;				//加算合成するかどうか

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}
//===========================
//エフェクトの終了処理
//===========================
void UninitEffect(void)
{
	for (int  nCnt = 0; nCnt < NUM_EFFECT; nCnt++)
	{
		if (g_apTextureEffect[nCnt] != NULL)
		{
			g_apTextureEffect[nCnt]->Release();
			g_apTextureEffect[nCnt] = NULL;
		}
	}
	//頂点バッファを破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//===========================
//エフェクトの更新処理
//===========================
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_2D*pVtx;
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//エフェクトが使用されている
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	//位置の更新

			//プレイヤーが中央に来た場合
			CenterPlayer(&g_aEffect[nCntEffect].pos);

			//頂点カラー設定	(アルファ値を下げて色を薄くする)
			g_aEffect[nCntEffect].col.a -= 0.01f;
			
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].fRadius-=0.05f;	//半径の減少

			//頂点座標の設定	(大きさを小さくする)
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[1].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius,- g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[2].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[3].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;

			//寿命が尽きた場合
			if (g_aEffect[nCntEffect].fRadius <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			if (g_aEffect[nCntEffect].col.a <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			g_aEffect[nCntEffect].nLife--;		

			//寿命が尽きた場合
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();

}
//===========================
//エフェクトの描画処理
//===========================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCntEffect].nType]);

			if (g_aEffect[nCntEffect].bAdd == true)
			{

				//アルファブレンディングを加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				nCntEffect * 4,							//頂点の開始場所
				2);										//プリミティブの数
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}
//===========================
//エフェクトの設定処理
//===========================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,bool ADD,int Type)
{
	int nCntEffect;
	VERTEX_2D*pVtx;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			g_aEffect[nCntEffect].bAdd = ADD;
			g_aEffect[nCntEffect].nType = Type;
			
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCntEffect * 4;	//頂点データのポインタを4つ分進める

			//頂点カラー設定	(アルファ値を下げて色を薄くする)
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].fRadius--;

			//頂点座標の設定	(大きさを小さくする)
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//頂点バッファをアンロック
			g_pVtxBuffEffect->Unlock();
			break;
		}
	}
}