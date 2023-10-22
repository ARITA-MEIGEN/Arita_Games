//=================================================
// Content     (タイトル画面の処理)(Tutorial.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/9)
//=================================================
#include"Tutorial.h"
#include"sound.h"
#include"fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial=NULL;					//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//頂点バッファへのポインタ
//===========================
//タイトル画面の初期化処理
//===========================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tutorial000.png",
		&g_pTextureTutorial);

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	
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
	g_pVtxBuffTutorial->Unlock();
}
//===========================
//タイトル画面の終了処理
//===========================
void UninitTutorial(void)
{
	//サウンドの停止
	StopSound();
	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial= NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//===========================
//タイトル画面の更新処理
//===========================
void UpdateTutorial(void)
{
	FADE pFade = GetFade();	//フェードの状態を取得
	//決定キー(ENTERキー)が押されたかどうか
	if ((GetKeyboardTrigger(DIK_RETURN) == true
		||GetJoypadTrigger(JOYKEY_Y) == true  
		|| GetJoypadTrigger(JOYKEY_X) == true 
		|| GetJoypadTrigger(JOYKEY_A) == true 
		|| GetJoypadTrigger(JOYKEY_B) == true 
		|| GetJoypadTrigger(JOYKEY_START) == true) && pFade == FADE_NONE)
	{
		//モード設定
		SetFade(MODE_GAME);
		PlaySound(SOUND_LABEL_SE_START);
	}
}
//===========================
//タイトル画面の描画処理
//===========================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数
}