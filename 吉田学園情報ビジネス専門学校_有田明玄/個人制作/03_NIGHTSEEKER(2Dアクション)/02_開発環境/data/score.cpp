//=================================================
// Content     (スコアの設定)(Score.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/28)
//=================================================
#include"score.h"	
#include"fade.h"
#include"game.h"
#include"result.h"
#include"ranking.h"

//マクロ定義
#define MAX_SCORE				(8)//スコアの最大数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureScoreBG = NULL;			//背景テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreBG = NULL;		//背景頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;									//スコアの位置
int g_nScore;											//スコアの値
//============================
//スコアの初期化処理
//============================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&g_pTextureScore);

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\scorebg000.jpg",
	//	&g_pTextureScoreBG);

	g_posScore = D3DXVECTOR3(950.0f, 100.0f, 0.0f);//位置の初期化
	g_nScore = 0;
	
	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	////頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffScoreBG,
	//	NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標の初期化
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 20 + (nCntScore * 35), g_posScore.y - 50, 0);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 20 + (nCntScore * 35), g_posScore.y - 50, 0);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 20 + (nCntScore * 35), g_posScore.y + 50, 0);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 20 + (nCntScore * 35), g_posScore.y + 50, 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();

////背景の設定
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffScoreBG->Lock(0, 0, (void**)&pVtx, 0);
//	//頂点座標の初期化
//	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), 0.0f, 0);
//	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0);
//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT, 0);
//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
//
//	//rhwの設定
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//頂点カラーの設定
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	//テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	//頂点バッファをアンロック
//	g_pVtxBuffScoreBG->Unlock();
}
//============================
//スコアの終了処理
//============================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//============================
//スコアの更新処理
//============================
void UpdateScore(void)
{

}
//==============================
//スコアの描画処理
//==============================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore = 0;

	//デバイスの取得
	pDevice = GetDevice();

////背景の設定
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffScoreBG, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, g_pTextureScoreBG);
//
//	//ポリゴンの描画       
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
//		0,										//頂点の開始場所
//		2);										//プリミティブの数
//
//スコアの設定
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//ポリゴンの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
			nCntScore * 4,							//頂点の開始場所
			2);										//プリミティブの数
	}
}
//=====================
//スコアの設定処理
//=====================
void SetScore(int nScore)
{
	//頂点座標へのポインタ
	VERTEX_2D*pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	int aPosTexU[8];	//各桁の数字を格納

	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore]), 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore] + 1), 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//=====================
//スコアの加算処理
//=====================
void AddScore(int nValue)
{
	//頂点座標へのポインタ
	VERTEX_2D*pVtx;
	int aPosTexU[8];	//各桁の数字を格納

	g_nScore += nValue;
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//============================
//スコアの状態の取得
//============================
int GetScore(void)
{
	return g_nScore;
}