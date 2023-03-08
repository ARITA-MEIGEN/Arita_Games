//=================================================
// Content     (ランキングの処理)(ranking.cpp)
// Author     : 有田明玄
//=================================================
#include"ranking.h"
#include"sound.h"
#include<stdio.h>
#include"score.h"

//マクロ定義
#define FILE_NAME	("data/TXT/ranking.txt")		//ランキングを保存するファイル

//ランキングスコア構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
}RankScore;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//ランキングテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//ランキング頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//スコアテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//スコア頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;				//ランキングの背景へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL;		//ランキングの背景の頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];						//ランキングスコアの情報
int g_nRankUpdate = -1;									//更新ランクNo.
int g_nTimerRanking;									//ランキング画面表示タイマー
float g_fPtnrank = 1.0f;								//プレイヤーランキングの点滅
int g_nCntrank = 0;										//点滅のカウント用
//============================
//ランキングの初期化処理
//============================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//読み込み処理
	LoadRanking();

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&g_pTextureRankScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRank);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rankbg001.jpg",
		&g_pTextureRankBG);

	//頂点ポインタを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	//スコアの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_SCORE * MAX_RANK; nCntRank++)
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
	g_pVtxBuffRankScore->Unlock();

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(600.0f, 550.0f - (95 * nCntRank), 0.0f);		//位置
	}


	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

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
	//頂点バッファをアンロック
	g_pVtxBuffRank->Unlock();

//背景の設定
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);
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

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロック
	g_pVtxBuffRankBG->Unlock();

	//タイマーのリセット
	g_nTimerRanking = 0;

	//ランキングの保存
	SaveRanking();
}
//===========================
//ランキングの終了処理
//===========================
void UninitRanking(void)
{
	StopSound();
	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffRankBG != NULL)
	{
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}
//===========================
//ランキングの更新処理
//===========================
void UpdateRanking(void)
{
	VERTEX_2D*pVtx;
	int nCntRank;
	int nCntScore;
	g_nCntrank++;
	g_nTimerRanking++;
	FADE pFade = GetFade();
	if ((g_nTimerRanking >= 600 || GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_X) == true)  && pFade == FADE_NONE)
	{//タイトルへ移行
		//PlaySound(SOUND_LABEL_SE_START);
		SetFade(MODE_TITLE);
	}

//スコアの設定
	if ((g_nCntrank % 30) == 0)
	{//ランクインしたとき点滅させるためのタイマー
		g_fPtnrank = 1.0f - g_fPtnrank;
	}
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x - 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y - 40, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x + 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y - 40, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x - 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y + 40, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x + 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y + 40, 0.0f);

			//頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffRankScore->Unlock();
	
	//ランクインした場合
	if (g_nRankUpdate != -1)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntRank = 0; nCntRank < MAX_SCORE; nCntRank++)
		{
			
			//ランキングを点滅させる
			pVtx[g_nRankUpdate * 4 * MAX_SCORE].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);

			pVtx += 4;
		}
		//頂点バッファをアンロック
		g_pVtxBuffRankScore->Unlock();

//スコアのランキングの更新
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(400.0f - 50, SCREEN_HEIGHT/2- 240, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(400.0f + 50, SCREEN_HEIGHT / 2- 240, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400.0f - 50, SCREEN_HEIGHT / 2+ 240, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(400.0f + 50, SCREEN_HEIGHT / 2+ 240, 0.0f);

		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffRank->Unlock();
	}
}
//===========================
//ランキングの描画処理
//===========================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//デバイスの取得
	pDevice = GetDevice();
//背景の設定
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankBG);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数
//ランキングの設定
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRank);

	//ポリゴンの描画       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		2);										//プリミティブの数

//スコアの設定
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankScore);

	for (nCntRank = 0; nCntRank < MAX_SCORE * MAX_RANK; nCntRank++)
	{
		//ポリゴンの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
			nCntRank * 4,							//頂点の開始場所
			2);										//プリミティブの数
	}
}
//===========================
//ランキングのリセット
//===========================
void ResetRanking(void)
{
	//読み込み処理
	LoadRanking();

	//ランキングの設定
	SetRanking();

	//タイマーのリセット
	g_nTimerRanking = 0;

	//ランキングの保存
	SaveRanking();
}
//===========================
//ランキングの設定処理
//===========================
void SetRanking(void)
{
	int nCntRank, nCntScore, nSave;
	int aPosTexU[8];					//各桁の数字を格納
	g_nRankUpdate = -1;
	g_nTimerRanking = 0;

	int pScore = GetScore();

	//スコアの最下位より大きければ入れ替え
	if (pScore >= g_aRankScore[0].nScore)
	{
		g_aRankScore[0].nScore = pScore;
		g_nRankUpdate++;
	}
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK-1; nCntRank++)
	{
		if (g_aRankScore[nCntRank].nScore > g_aRankScore[nCntRank + 1].nScore)
		{//ランキングの並べ替え
			nSave = g_aRankScore[nCntRank + 1].nScore;
			g_aRankScore[nCntRank + 1].nScore = g_aRankScore[nCntRank].nScore;
			g_aRankScore[nCntRank].nScore = nSave;
			g_nRankUpdate++;
		}
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		aPosTexU[0] = g_aRankScore[nCntRank].nScore % 100000000 / 10000000;
		aPosTexU[1] = g_aRankScore[nCntRank].nScore % 10000000 / 1000000;
		aPosTexU[2] = g_aRankScore[nCntRank].nScore % 1000000 / 100000;
		aPosTexU[3] = g_aRankScore[nCntRank].nScore % 100000 / 10000;
		aPosTexU[4] = g_aRankScore[nCntRank].nScore % 10000 / 1000;
		aPosTexU[5] = g_aRankScore[nCntRank].nScore % 1000 / 100;
		aPosTexU[6] = g_aRankScore[nCntRank].nScore % 100 / 10;
		aPosTexU[7] = g_aRankScore[nCntRank].nScore % 10 / 1;

		for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 0.0f);//右回りに座標を指定
			pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 1.0f);

			pVtx += 4;	//頂点データのポインタを4つ分進める
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffRankScore->Unlock();
}
//===========================
//ランキングの読み込み処理
//===========================
void LoadRanking(void)
{
	FILE*pFile;
	
	pFile = fopen(FILE_NAME, "r");

	if (pFile!=NULL)
	{
		//行数読み込み
		for (int nCnt=0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}

	//ファイルを閉じる
	fclose(pFile);
}
//===========================
//ランキングの保存処理
//===========================
void SaveRanking(void)
{
	FILE*pFile;

	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{
		//行数読み込み
		for (int nCnt=0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}

	//ファイルを閉じる
	fclose(pFile);
}