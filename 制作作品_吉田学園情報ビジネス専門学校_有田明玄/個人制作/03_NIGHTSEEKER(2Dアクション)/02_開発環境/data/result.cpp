//=================================================
// Content     (リザルト画面の処理)(result.cpp)
// Author     : 有田明玄
// LastUpdate : (更新日2021/09/02)
// Since      : (作成日2021/08/29)
//=================================================
#include"result.h"
#include"sound.h"
#include"fade.h"
#include"input.h"
#include"game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResultBG = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBG = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureResult[2] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ
int g_nTimerResult;								//タイマー
//===========================
//リザルト画面の初期化処理
//===========================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg003.png",
		&g_pTextureResultBG);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameclear_logo.png",
		&g_apTextureResult[0]);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameover_logo.png",
		&g_apTextureResult[1]);

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultBG,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffResultBG->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, SCREEN_HEIGHT / 2 - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, SCREEN_HEIGHT / 2 - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	g_nTimerResult = 0;	//タイマーのリセット
	GAMESTATE pGamestate = GetGameState();

	//ゲームの状況に応じて変化
	switch (pGamestate)
	{//サウンドの再生
	case GAMESTATE_CLEAR:
		PlaySound(SOUND_LABEL_BGM003);
		break;
	case GAMESTATE_FAILED:
		PlaySound(SOUND_LABEL_BGM004);
		break;
	default:
		break;
	}
}
//===========================
//リザルト画面の終了処理
//===========================
void UninitResult(void)
{
	//サウンドの停止
	StopSound();
	
	//テクスチャの破棄
	if (g_pTextureResultBG != NULL)
	{
		g_pTextureResultBG->Release();
		g_pTextureResultBG = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffResultBG != NULL)
	{
		g_pVtxBuffResultBG->Release();
		g_pVtxBuffResultBG = NULL;
	}
//結果の表示
	for (int nCount = 0;  nCount < 2;  nCount++)
	{
		//テクスチャの破棄
		if (g_apTextureResult[nCount] != NULL)
		{
			g_apTextureResult[nCount]->Release();
			g_apTextureResult[nCount] = NULL;
		}
	}
	//頂点バッファを破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	
}
//===========================
//リザルト画面の更新処理
//===========================
void UpdateResult(void)
{
	g_nTimerResult++;	//時間経過で次の画面に移行

	//決定キー(ENTERキー)が押されたかどうか
	FADE pFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE		//ENTERキー
		|| GetJoypadTrigger(JOYKEY_Y) == true && pFade == FADE_NONE			//Yボタン
		|| GetJoypadTrigger(JOYKEY_X) == true && pFade == FADE_NONE			//Xボタン
		|| GetJoypadTrigger(JOYKEY_START) == true && pFade == FADE_NONE		//スタートボタン
		|| g_nTimerResult >= 600 && pFade == FADE_NONE)						//時間経過
	{
		PlaySound(SOUND_LABEL_SE_START);
		//モード設定
		SetFade(MODE_RANKING);
	}
}
//===========================
//リザルト画面の描画処理
//===========================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultBG);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ゲームの情報の取得
	GAMESTATE pGamestate = GetGameState();
	//ゲームの状況に応じて変化
	switch (pGamestate)
	{
	case GAMESTATE_CLEAR:
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureResult[0]);
		break;
	case GAMESTATE_FAILED:
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureResult[1]);
		break;
	default:
		pDevice->SetTexture(0, NULL);
		break;
	}
	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数
}
