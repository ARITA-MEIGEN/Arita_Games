//=================================================
// Content     (背景の操作)(BG.cpp)
// Author     : 有田明玄
// LastUpdate : (更新日2021/07/18)
// Since      : (作成日2021/07/06)
//=================================================
#include "background.h"
#include"player.h"
#include"block.h"
#include"player.h"
//マクロ定義
#define NUM_BG	(3)			//背景の枚数
#define BG_SPEED	(0.0005f)	//背景の速度

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//頂点バッファへのポインタ
int g_nCounterAnimBG;								//カウンターを初期化する
int g_nPatternAnimBG;								//パターンNo.を初期化する
D3DXVECTOR3 g_posBG;								//位置
D3DXVECTOR3 g_moveBG;								//移動量

//スタティック関数
static void ControlBG(void);		//背景の操作関係の処理
//======================================================
//背景の初期化処理
//======================================================
void InitBG(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg000.jpg",
			&g_apTextureBG[0]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg001.png",
			&g_apTextureBG[1]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg002.png",
			&g_apTextureBG[2]);
	
	g_nCounterAnimBG = 0;						//カウンターを初期化する
	g_nPatternAnimBG = 0;						//パターンNo.を初期化する
	g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
	g_moveBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量を初期化する

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG-1; nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 20.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 20.0f, SCREEN_HEIGHT / 2 - 260.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20.0f, SCREEN_HEIGHT / 2 - 260.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//======================================================
//背景の終了処理
//======================================================
void UninitBG(void)
{
	int nCntBG;
	//テクスチャの破棄
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBG[nCntBG] != NULL)
		{
			g_apTextureBG[nCntBG]->Release();
			g_apTextureBG[nCntBG] = NULL;
		}
	}
	//頂点バッファを破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//======================================================
//背景の更新処理
//======================================================
void UpdateBG(void)
{
	//位置を更新
	g_posBG = g_moveBG;

	//プレイヤーの動きに応じて背景の移動
	ControlBG();

	//移動量更新(減衰させる)
	g_moveBG.x += (0.0f - g_moveBG.x)*0.1f;
	g_moveBG.y += (0.0f - g_moveBG.y)*0.1f;

	VERTEX_2D*pVtx;//頂点座標へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBG = 0; nCntBG < NUM_BG-1; nCntBG++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));//右回りに座標を指定
		pVtx[1].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx[2].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx[3].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx += 4;
	}
	pVtx[0].pos += D3DXVECTOR3(0.0f, 0.0f,0.0f);//右回りに座標を指定
	pVtx[1].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}
//======================================================
//背景の描画処理
//======================================================
void DrawBG(void)
{
	static int nCntBG;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntBG  = 0; nCntBG <NUM_BG; nCntBG++)
	{
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);
	
		//背景の描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBG*4, 2);
	}
}
//======================================================
//背景の操作関係の処理
//======================================================
static void ControlBG(void)
{
	CenterPlayer(&g_moveBG);
	g_moveBG.x/=-3000;
}