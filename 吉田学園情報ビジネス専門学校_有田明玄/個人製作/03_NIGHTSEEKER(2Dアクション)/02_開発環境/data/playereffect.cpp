//=================================================
// Content     (エフェクトの処理)(playerPlayereffect.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/09/07)
//=================================================
#include"playereffect.h"
#include"player.h"

//マクロ定義
#define MAX_Playereffect		(9192)	//エフェクトの最大数

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
	float fRadiuswidth;	//横幅
	float fRadiusheight;//縦幅
	int nLife;			//寿命
	bool bUse;			//使用しているかどうかの判定
}Playereffect;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayereffect = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayereffect = NULL;	//頂点バッファへのポインタ
Playereffect g_aPlayereffect[MAX_Playereffect];						//エフェクトの情報
//============================
//エフェクトの初期化処理
//============================
void InitPlayereffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPlayereffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player001.png",
		&g_pTexturePlayereffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Playereffect,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayereffect,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);

	//敵の情報の初期化
	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		g_aPlayereffect[nCntPlayereffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aPlayereffect[nCntPlayereffect].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
		g_aPlayereffect[nCntPlayereffect].fRadiuswidth = 0;							//半径(大きさ)
		g_aPlayereffect[nCntPlayereffect].nLife = 0;								//寿命
		g_aPlayereffect[nCntPlayereffect].bUse = false;								//使用しているかどうかの判定

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffPlayereffect->Unlock();
}
//===========================
//エフェクトの終了処理
//===========================
void UninitPlayereffect(void)
{
	if (g_pTexturePlayereffect != NULL)
	{
		g_pTexturePlayereffect->Release();
		g_pTexturePlayereffect = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffPlayereffect != NULL)
	{
		g_pVtxBuffPlayereffect->Release();
		g_pVtxBuffPlayereffect = NULL;
	}
}
//===========================
//エフェクトの更新処理
//===========================
void UpdatePlayereffect(void)
{
	int nCntPlayereffect;

	VERTEX_2D*pVtx;
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == true)
		{//エフェクトが使用されている

			//頂点カラー設定	(アルファ値を下げて色を薄くする)
			g_aPlayereffect[nCntPlayereffect].col.a -= 1.0f/30.0f;

			pVtx[0].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[1].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[2].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[3].col = g_aPlayereffect[nCntPlayereffect].col;

			g_aPlayereffect[nCntPlayereffect].nLife--;

			//寿命が尽きた場合
			if (g_aPlayereffect[nCntPlayereffect].nLife <= 0)
			{
				g_aPlayereffect[nCntPlayereffect].bUse = false;
			}

			//画面の中央に来た時の設定
			CenterPlayer(&g_aPlayereffect[nCntPlayereffect].pos);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, -g_aPlayereffect[nCntPlayereffect].fRadiusheight, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, -g_aPlayereffect[nCntPlayereffect].fRadiusheight, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffPlayereffect->Unlock();
}
//===========================
//エフェクトの描画処理
//===========================
void DrawPlayereffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPlayereffect;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayereffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayereffect);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == true)
		{
			//ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				nCntPlayereffect*4,						//頂点の開始場所
				2);										//プリミティブの数
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//===========================
//エフェクトの設定処理
//===========================
void SetPlayereffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight, int nLife, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	int nCntPlayereffect;
	VERTEX_2D*pVtx;

	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == false)
		{
			g_aPlayereffect[nCntPlayereffect].pos = pos;
			g_aPlayereffect[nCntPlayereffect].col = col;
			g_aPlayereffect[nCntPlayereffect].fRadiuswidth = fRadiuswidth;
			g_aPlayereffect[nCntPlayereffect].fRadiusheight = fRadiusheight;
			g_aPlayereffect[nCntPlayereffect].nLife = nLife;
			g_aPlayereffect[nCntPlayereffect].bUse = true;

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCntPlayereffect * 4;	//頂点データのポインタを4つ分進める

			//頂点カラー設定
			pVtx[0].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[1].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[2].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[3].col = g_aPlayereffect[nCntPlayereffect].col;

			//頂点座標の設定	(大きさを小さくする)
			pVtx[0].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth, -g_aPlayereffect[nCntPlayereffect].fRadiusheight * 2, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth, -g_aPlayereffect[nCntPlayereffect].fRadiusheight * 2, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;

			pVtx[0].tex = a;	//右回りに座標を指定
			pVtx[1].tex = b;
			pVtx[2].tex = c;
			pVtx[3].tex = d;

			//頂点バッファをアンロック
			g_pVtxBuffPlayereffect->Unlock();
			break;
		}
	}
}