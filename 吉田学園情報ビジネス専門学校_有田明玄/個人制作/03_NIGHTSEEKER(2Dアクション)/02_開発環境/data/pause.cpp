//=================================================
// Content     (ポーズの操作)(Pause.cpp)
// Author     : 有田明玄
// LastUpdate : (更新日2021/07/18)
// Since      : (作成日2021/07/06)
//=================================================
#include"pause.h"

//マクロ定義
#define NUM_PAUSE	(5)		//ポーズの枚数
#define MODE_COUNT	(3)		//モードの数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePause[NUM_PAUSE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			//頂点バッファへのポインタ
PAUSE_MENU g_Pause;										//ポーズの状態設定
//======================================================
//ポーズの初期化処理
//======================================================
void InitPause(void)
{
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause100.png",
		&g_apTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&g_apTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_apTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_apTexturePause[3]);

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	g_Pause = PAUSE_MENU_CONTINUE;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
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

		//テクスチャ座標の設定
		pVtx[0].tex += D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[1].tex += D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex += D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex += D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();
}
//======================================================
//ポーズの終了処理
//======================================================
void UninitPause(void)
{
	int nCntPause;
	//テクスチャの破棄
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}
	//頂点バッファを破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//======================================================
//ポーズの更新処理
//======================================================
void UpdatePause(void)
{
	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//メニューの選択
	if (GetKeyboardTrigger(DIK_W) == true|| GetKeyboardTrigger(DIK_UP) == true||GetJoypadTrigger(JOYKEY_UP) == true||GetJoypadStick(JOYKEY_LSTICK).y <= -1.0)
	{
		//上に移動
		g_Pause = (PAUSE_MENU((g_Pause + (MODE_COUNT-1)) % MODE_COUNT));
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || GetJoypadStick(JOYKEY_LSTICK).y >= 1.0)
	{
		//下に移動
		g_Pause = (PAUSE_MENU((g_Pause + 1) % MODE_COUNT));
		PlaySound(SOUND_LABEL_SE_SELECT);

	}
	
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_X) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{//決定キーが押された
		switch (g_Pause)
		{
		case PAUSE_MENU_CONTINUE:		//コンティニュー点滅
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:			//リトライ点滅
			SetFade(MODE_GAME);
			SetEnablePause(false);
			break;

		case PAUSE_MENU_QUIT:			//タイトル点滅
			SetFade(MODE_TITLE);
			SetEnablePause(false);
			break;
		}
		PlaySound(SOUND_LABEL_SE_START);
	}
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT / 5, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT - (SCREEN_HEIGHT / 5), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT - (SCREEN_HEIGHT / 5), 0.0f);

	pVtx[8].pos = D3DXVECTOR3(440.0f, 200.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(840.0f, 200.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(440.0f, 300.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(840.0f, 300.0f, 0.0f);

	pVtx[12].pos = D3DXVECTOR3(440.0f, 310.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(840.0f, 310.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(440.0f, 410.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(840.0f, 410.0f, 0.0f);

	pVtx[16].pos = D3DXVECTOR3(440.0f, 420.0f, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(840.0f, 420.0f, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(440.0f, 520.0f, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(840.0f, 520.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	switch (g_Pause)
	{
	case PAUSE_MENU_CONTINUE:
		pVtx[8].col =  D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[9].col =  D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[10].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[11].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;

	case PAUSE_MENU_RETRY:
		pVtx[12].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[13].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[14].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[15].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;

	case PAUSE_MENU_QUIT:
		pVtx[16].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[17].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[18].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[19].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;
	}
	//頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();
}
//======================================================
//ポーズの描画処理
//======================================================
void DrawPause(void)
{
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポーズの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	for (nCntPause = 0; nCntPause < 4; nCntPause++)
	{
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//ポーズの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPause + 1) * 4, 2);
	}
}