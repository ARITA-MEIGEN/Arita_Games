//=================================================
// Content     (敵の設定)(Enemy.cpp)
// Author     : 有田明玄
// LastUpdate : (更新日2021/08/14)
// Since      : (作成日2021/07/06)
//=================================================
#include"enemy.h"
#include"Player.h"
#include"sound.h"
#include"game.h"
#include"Attack.h"
#include"effect.h"
#include"score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//敵のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//敵の頂点バッファ
static Enemy s_aEnemy[MAX_ENEMY];						//敵の情報

//プロトタイプ宣言
static void SettingbyTypeEnemy(int nCnt);	//タイプごとの設定
static void StateEnemy(int nCnt);			//状態変化の設定
static void OutScreenEnemy(int nCnt);		//画面外の処理
//============================
//敵の初期化処理
//============================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy004.png",
		&g_apTextureEnemy[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy001.png",
		&g_apTextureEnemy[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy002.png",
		&g_apTextureEnemy[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy003.png",
		&g_apTextureEnemy[3]);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		s_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEnemy[nCntEnemy].nType = 0;
		s_aEnemy[nCntEnemy].nLife = 0;
		s_aEnemy[nCntEnemy].nBullettimer = 0;
		s_aEnemy[nCntEnemy].bUse = false;	//使用していない状態にする
		s_aEnemy[nCntEnemy].nCntAnim = 0;
		s_aEnemy[nCntEnemy].nPtnAnim = 0;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

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

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//============================
//敵の終了処理
//============================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		//テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファを破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		s_aEnemy[i].bUse = false;
	}
}

//============================
//敵の更新処理
//============================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている場合
			//位置の更新
				s_aEnemy[nCntEnemy].posOld = s_aEnemy[nCntEnemy].pos;
				if (s_aEnemy[nCntEnemy].pos.x<=SCREEN_WIDTH)
				{
					s_aEnemy[nCntEnemy].pos.x += s_aEnemy[nCntEnemy].move.x;
				} 
				s_aEnemy[nCntEnemy].pos.y += s_aEnemy[nCntEnemy].move.y;

				//画面の中央に来た時の設定
				CenterPlayer(&s_aEnemy[nCntEnemy].pos);

				//ブロックの上に乗っている場合
				if (s_aEnemy[nCntEnemy].pBlock != NULL)
				{
					//ブロックのタイプを参照
					if (s_aEnemy[nCntEnemy].pBlock->nType == 1)
					{
						//ブロックの移動量を加算
						s_aEnemy[nCntEnemy].pos += s_aEnemy[nCntEnemy].pBlock->move;
					}
				}
				//当たり判定
				if (CollisionBlock(&s_aEnemy[nCntEnemy].pos, &s_aEnemy[nCntEnemy].posOld, &s_aEnemy[nCntEnemy].move, ENEMY_SIZE, ENEMY_SIZE, &s_aEnemy[nCntEnemy].pBlock) == true)
				{
					s_aEnemy[nCntEnemy].move.y = 0;
				}

				if (CollisionWeapon(&s_aEnemy[nCntEnemy].pos, &s_aEnemy[nCntEnemy].posOld, &s_aEnemy[nCntEnemy].move, ENEMY_SIZE, ENEMY_SIZE) == true && s_aEnemy[nCntEnemy].state != ENEMYSTATE_DAMAGE)
				{
					HitEnemy(nCntEnemy, 100);
				}

				if (s_aEnemy[nCntEnemy].nCntAnim++ % 10 == 0)
				{//アニメーションの設定
					s_aEnemy[nCntEnemy].nPtnAnim++;
					if (s_aEnemy[nCntEnemy].nPtnAnim % 3 == 0)
					{
						s_aEnemy[nCntEnemy].nPtnAnim = 0;
					}
				}

				//敵の状態管理
				StateEnemy(nCntEnemy);

				//敵が画面外に行った時の処理
				OutScreenEnemy(nCntEnemy);

				s_aEnemy[nCntEnemy].move.y += 1.0f;
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[1].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[3].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3), 0.25f);	//右回りに座標を指定
				pVtx[1].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3 + 1), 0.25f);
				pVtx[2].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3), 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3 + 1), 0.5f);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//==============================
//敵の描画処理
//==============================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている

		 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[s_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				nCntEnemy * 4,							//頂点の開始場所
				2);										//プリミティブの数
		}
	}
}
//=====================
//敵の設定処理
//=====================
void SetEnemy(D3DXVECTOR3 pos, int type)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない
			//敵の情報の設定
			s_aEnemy[nCntEnemy].pos = pos;
			s_aEnemy[nCntEnemy].nType = type;
			s_aEnemy[nCntEnemy].nBullettimer = 0;
			s_aEnemy[nCntEnemy].bUse = true;	//使用している状態にする

			//タイプ別の設定
			SettingbyTypeEnemy(nCntEnemy);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
			pVtx[1].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
			pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
			pVtx[3].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//=======================
//敵のヒット処理
//=======================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	s_aEnemy[nCntEnemy].nLife -= nDamage;
	if (s_aEnemy[nCntEnemy].nLife <= 0)
	{//体力が０になった時
		s_aEnemy[nCntEnemy].bUse = false;
		pPlayer->nLife += 400;
		//爆発の設定
		for (int e = 0; e < 20; e++)
		{
			SetEffect(
				s_aEnemy[nCntEnemy].pos- D3DXVECTOR3(0.0f,ENEMY_SIZE/2,0.0f) 
				+D3DXVECTOR3((float)(rand() % 20 - 10), (float)(rand() % 20 - 10), 0.0f)		//位置の設定
				//移動量の設定																		
				, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f
							, cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) /3.0f + 0.0f, 0.0f)
				, D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.5f)		//頂点カラーの設定
				, 30									//半径の大きさの設定
				, 30									//寿命(あんまり意味ない)
				, true									//加算合成するかどうか
				, 1);									//何枚目のテクスチャを使うかどうか
		}
			//爆発音の再生
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			//スコアの追加処理
			AddScore(20000);
		if (pPlayer->nLife>= MAX_PLIFE)
		{
			pPlayer->nLife = MAX_PLIFE;
		}
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);
	}
	else
	{//生きてる場合
		s_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		s_aEnemy[nCntEnemy].nCounterState = 15;//ダメージ時間を保つ時間を設定

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//ポリゴンをダメージ色に設定
		pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffEnemy->Unlock();

		//PlaySound(SOUND_LABEL_SE_HIT);
	}
}
//=====================
//タイプごとの設定
//=====================
static void SettingbyTypeEnemy(int nCnt)
{
		switch (s_aEnemy[nCnt].nType)
		{
		case 0:
			s_aEnemy[nCnt].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			s_aEnemy[nCnt].nLife = 200;
			s_aEnemy[nCnt].bUse = true;	//使用していない状態にする
			s_aEnemy[nCnt].nAtk = 500;
			break;
		case 1:
			s_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			s_aEnemy[nCnt].nLife = 200;
			s_aEnemy[nCnt].bUse = true;	//使用していない状態にする
			s_aEnemy[nCnt].nAtk = 500;
			break;
		default:
			break;
		}
}
//=====================
//状態変化の設定
//=====================
static void StateEnemy(int nCnt)
{
	VERTEX_2D*pVtx;
	switch (s_aEnemy[nCnt].state)
	{
	case ENEMYSTATE_NORMAL:
		break;
	case ENEMYSTATE_DAMAGE:
		s_aEnemy[nCnt].nCounterState--;
		if (s_aEnemy[nCnt].nCounterState <= 0)
		{
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			s_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;
			pVtx += 4 * nCnt;	//頂点データのポインタを4つ分進める

			//ポリゴンを通常色に設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//頂点バッファをアンロック
			g_pVtxBuffEnemy->Unlock();
		}
		break;
	}
}
//=====================
//画面外の処理
//=====================
static void OutScreenEnemy(int nCnt)
{
	if (s_aEnemy[nCnt].pos.x <= -ENEMY_SIZE)
	{//画面外に出た場合の処理(左端)
		s_aEnemy[nCnt].pos.x = ENEMY_SIZE;
		s_aEnemy[nCnt].bUse = false;		//使用していない状態にする
	}
	if (s_aEnemy[nCnt].pos.y >= SCREEN_HEIGHT + ENEMY_SIZE)
	{//画面外に出た場合の処理(下端)
		s_aEnemy[nCnt].bUse = false;		//使用していない状態にする
	}
}
//=====================
//エネミーの当たり判定
//=====================
void CollisionEnemy(D3DXVECTOR3 *pPos, float Width, float Height)
{
	//プレイヤーのが敵に当たった時の判定は別々で作らないといけない
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (s_aEnemy[nCnt].bUse == true)
		{//プレイヤーが使用されている 
		 //プレイヤーに相手がぶつかった時
			if (pPos->y >= s_aEnemy[nCnt].pos.y - ENEMY_SIZE
				&& pPos->y - Height <= s_aEnemy[nCnt].pos.y
				&&pPos->x - Width / 2 <= s_aEnemy[nCnt].pos.x + ENEMY_SIZE / 2
				&& pPos->x + Width / 2 >= s_aEnemy[nCnt].pos.x - ENEMY_SIZE / 2)
			{//プレイヤ-とプレイヤーが当たった時
				HitPlayer(s_aEnemy[nCnt].nAtk);
			}
		}
	}
}
//=====================
//敵の取得処理
//=====================
Enemy *GetEnemy(void)
{//エネミーのポインタをリセット
	return &s_aEnemy[0];
}