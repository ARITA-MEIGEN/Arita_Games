#include"main.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mapload.h"
#include"block.h"
#include"player.h"
#include"enemy.h"
#include"boss.h"

//マクロ定義
#define NUM_BLOCK_X			(320)		//横幅用
#define NUM_BLOCK_Y			(18)		//縦幅用
#define MAX_BLOCK_X			(32)		//画面内のブロック数用
#define MAX_BLOCK_Y			(18)		//画面内のブロック数用
#define FILE_BLOCK_PLACE	"data\\TXT\\mapdata.txt"	//読み込むファイル名
//スタティック変数
static int   s_Block[NUM_BLOCK_Y][NUM_BLOCK_X];					//ブロックの座標の保存
static float blockW = (float)SCREEN_WIDTH / MAX_BLOCK_X;		//ブロックの横の長さ
static float blockH = (float)SCREEN_HEIGHT / MAX_BLOCK_Y;		//ブロックの縦の長さ
static float blockX[NUM_BLOCK_X];
static float blockY[NUM_BLOCK_Y];
//======================================================
//マップ読み込みの初期化処理
//======================================================
void InitMapLoad(void)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK_X; nCnt++)
	{
		blockX[nCnt] = (nCnt%NUM_BLOCK_X)*blockW;
	}
	for (int nCnt = 0; nCnt < NUM_BLOCK_Y; nCnt++)
	{
		blockY[nCnt] = (nCnt%NUM_BLOCK_Y)*blockH;
	}
	//static int aBlock[NUM_BLOCK_Y][NUM_BLOCK_X];
	const int lenLine = 1024; //一行の最大数
	char strLine[lenLine];
	FILE*fp = fopen(FILE_BLOCK_PLACE, "r");		//excelの読み込み？
	if (fp != NULL)
	{
		//EXCELデータ読み込み用
		for (int y = 0; y < NUM_BLOCK_Y; y++)
		{
			fgets(strLine, lenLine, fp);			//一行読み込み
			for (int x = 0; x < NUM_BLOCK_X; x++)
			{
				switch (atoi(&(strLine[x * 2])))	//数値を一文字ずつ受け取る(多分)	なんでx*2なのか分からない　atoiでchar型からint型に変える
				{
				case 0://受け取った数値に応じて指定の色にする
					s_Block[y][x] = 0;		
					break;
				case 1:	//停止ブロック生成
					s_Block[y][x] = 1;		
					break;
				case 2:	//移動ブロックの生成
					s_Block[y][x] = 2;		
					break;	
				case 3:	//敵の生成
					s_Block[y][x] = 3;	
					break;
				case 4:	//プレイヤーの生成
					s_Block[y][x] = 4;
					break;
				case 5:	//ボスの生成フラグ
					s_Block[y][x] = 5;
					break;
				}
			}
		}
		//ブロック配置用
		for (int y = 0; y < NUM_BLOCK_Y; y++)
		{
			for (int x = 0; x < NUM_BLOCK_X; x++)
			{
				switch (s_Block[y][x])	//数値を一文字ずつ受け取る(多分)	なんでx*2なのか分からない　atoiでchar型からint型に変える
				{
				case 0://受け取った数値に応じて指定の色にする
					break;
				case 1:	//停止ブロック生成
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 1);	
					break;
				case 2:	//移動ブロックの生成
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 2);
					break;
				case 3:	//敵の設定
					SetEnemy(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f),0);
					break;
				case 4:	//プレイヤーの生成
					SetPlayer(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f));
					break;
				case 5:	//ボスの生成フラグ
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 5);
					break;
				}
			}
		}
	}
}
//======================================================
//マップ読み込みの更新処理
//======================================================
void UpdateMapLoad(void)
{
	////static int aBlock[NUM_BLOCK_Y][NUM_BLOCK_X];
	//const int lenLine = 1024; //一行の最大数
	//char strLine[lenLine];
	//FILE*fp = fopen(FILE_BLOCK_PLACE, "r");		//excelの読み込み？
	//if (fp != NULL)
	//{
	//	for (int y = 0; y < NUM_BLOCK_Y; y++)
	//	{
	//		fgets(strLine, lenLine, fp);		//一行読み込み
	//		for (int x = 0; x < NUM_BLOCK_X; x++)
	//		{
	//			switch (atoi(&(strLine[x * 2])))//数値を一文字ずつ受け取る(多分)	なんでx*2なのか分からない　atoiでchar型からint型に変える
	//			{
	//			case 0://受け取った数値に応じて指定の色にする
	//				break;
	//			case 1:
	//				SetBlock(D3DXVECTOR3(blockX[x], blockY[y], 0.0f), blockW, blockH, 1);	//ブロックの設置
	//				break;
	//			}
	//		}
	//	}
	//}
}