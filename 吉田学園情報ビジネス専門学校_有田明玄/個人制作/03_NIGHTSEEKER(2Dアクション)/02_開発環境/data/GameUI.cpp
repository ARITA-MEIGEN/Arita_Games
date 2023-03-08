//=================================================
// Content     (プレイヤーの操作)(UI.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/10/04)
//=================================================
#include"GameUI.h"
#include"player.h"
//マクロ定義
#define LIFEGAUGE_SIZE		(20.0f)		//体力ゲージのサイズ調整用

//スタティック変数
static LPDIRECT3DTEXTURE9 s_apTexturePlayerLife[NUM_LIFE] = {};	//体力ゲージのテクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPlayerLife = NULL;		//体力ゲージの頂点バッファへのポインタ

//プロトタイプ宣言
static void ResetLifegauge(void);					//プレイヤーの体力ゲージの初期化
static void UpdatePlayerLife(void);					//体力ゲージの情報更新
//======================================================
//プレイヤーの初期化処理
//======================================================
void InitUI(void)
{
	ResetLifegauge();	//体力ゲージの情報の初期化
}
//======================================================
//プレイヤーの終了処理
//======================================================
void UninitUI(void)
{
	//体力ゲージのテクスチャの破棄
	for (int  nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		if (s_apTexturePlayerLife[nCnt]!=NULL)
		{
			s_apTexturePlayerLife[nCnt]->Release();
			s_apTexturePlayerLife[nCnt] = NULL;
		}
	}
	//体力ゲージの頂点バッファを破棄
	if (s_pVtxBuffPlayerLife != NULL)
	{
		s_pVtxBuffPlayerLife->Release();
		s_pVtxBuffPlayerLife = NULL;
	}
}
//======================================================
//プレイヤーの更新処理
//======================================================
void UpdateUI(void)
{
	//体力ゲージの更新
	UpdatePlayerLife();
}
//======================================================
//プレイヤーの描画処理
//======================================================
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//三枚分のテクスチャの設定
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_apTexturePlayerLife[nCnt]);

		//プレイヤーの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//======================================================
//プレイヤーの体力ゲージの初期化
//======================================================
static void ResetLifegauge(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Lifegaugeblood.png",
		&s_apTexturePlayerLife[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifegauge004.png",
		&s_apTexturePlayerLife[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffPlayerLife,
		NULL);

	//プレイヤーの情報の獲得
	Player*pPlayer = GetPlayer();
	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		pVtx[0].pos= D3DXVECTOR3(50.0f, 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 80.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	s_pVtxBuffPlayerLife->Unlock();
}
//======================================================
//体力ゲージの情報更新
//======================================================
static void UpdatePlayerLife(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの情報の獲得
	Player*pPlayer = GetPlayer();

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(50.0f, 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 80.0f, 0.0f);
		
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	s_pVtxBuffPlayerLife->Unlock();
}