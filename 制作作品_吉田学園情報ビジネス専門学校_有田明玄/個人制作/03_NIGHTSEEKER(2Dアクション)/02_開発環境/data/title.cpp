//=================================================
// Content     (タイトル画面の処理)(title.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/9)
//=================================================
#include"title.h"
#include"sound.h"
#include"fade.h"

//マクロ定義
#define NUM_TITLE		(2)									//タイトルで使うポリゴン数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitlelogo = NULL;				//タイトルロゴテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlelogo = NULL;			//タイトルロゴ頂点バッファへのポインタ
int g_nCnt = 0;	//ループ用
float g_fPtntitle = 0;	//点滅用
//===========================
//タイトル画面の初期化処理
//===========================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg003.png",
		&g_apTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\press_enter.png",
		&g_apTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titlelogo000.png",
		&g_pTextureTitlelogo);

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlelogo,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH/2-300, 500.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH/2+300, 500.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH/2-300, 700.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH/2+300, 700.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

//タイトルロゴの設定
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitlelogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, 600.0f, 0.0f);

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
	g_pVtxBuffTitlelogo->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);
}
//===========================
//タイトル画面の終了処理
//===========================
void UninitTitle(void)
{
	//音声の停止
	StopSound();

	//テクスチャの破棄
	for (int nCount = 0; nCount < NUM_TITLE; nCount++)
	{
		if (g_apTextureTitle[nCount] != NULL)
		{
			g_apTextureTitle[nCount]->Release();
			g_apTextureTitle[nCount] = NULL;
		}
	}

	//頂点バッファを破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}


	//タイトルロゴテクスチャの破棄
	if (g_pTextureTitlelogo != NULL)
	{
		g_pTextureTitlelogo->Release();
		g_pTextureTitlelogo = NULL;
	}

	//タイトルロゴ頂点バッファを破棄
	if (g_pVtxBuffTitlelogo != NULL)
	{
		g_pVtxBuffTitlelogo->Release();
		g_pVtxBuffTitlelogo = NULL;
	}

}
//===========================
//タイトル画面の更新処理
//===========================
void UpdateTitle(void)
{
	FADE pFade = GetFade();	//フェードの状態を取得

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;
	
	g_nCnt++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCnt % 30) == 0)
	{
		g_fPtntitle=1- g_fPtntitle;
	}
	if (pFade==FADE_OUT)
	{
		if ((g_nCnt % 2) == 0)
		{
			g_fPtntitle = 1 - g_fPtntitle;
		}
	}
	
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	//指定のキーが押されたかどうか
	if ((GetKeyboardTrigger(DIK_RETURN) == true 	//ENTERキー
		||GetJoypadTrigger(JOYKEY_Y) ==   true 			//パッドYキー
		|| GetJoypadTrigger(JOYKEY_X) ==  true 		//パッドXキー
		|| GetJoypadTrigger(JOYKEY_A) ==  true 	//パッドAキー
		|| GetJoypadTrigger(JOYKEY_B) ==  true 	//パッドBキー
		|| GetJoypadTrigger(JOYKEY_START) == true) && pFade != FADE_OUT)	//パッドスタートキー
	{
		PlaySound(SOUND_LABEL_SE_START);
		//モード設定
		SetFade(MODE_TUTOLIAL);
	}
}
//===========================
//タイトル画面の描画処理
//===========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureTitle[0]);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureTitle[1]);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		4,										//頂点の開始場所
		2);										//プリミティブの数

//タイトルロゴの設定
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitlelogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlelogo);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数

}