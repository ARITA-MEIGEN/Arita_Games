//=================================================
// Content     (ボスの設定)(Boss.cpp)
// Author     : 有田明玄
//=================================================
#include"Boss.h"
#include"Player.h"
#include"sound.h"
#include"game.h"
#include"Attack.h"
#include"effect.h"
#include"bullet.h"
#include"score.h"

//マクロ定義
#define INV_TIME	(10)

//スタティック変数
static LPDIRECT3DTEXTURE9 s_apTextureBoss[NUM_BOSS] = {};	//ボスのテクスチャ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffBoss = NULL;		//ボスの頂点バッファ
static BOSS s_Boss;											//ボスの情報

//プロトタイプ宣言
static void StateBoss(void);			//状態変化の設定
static void OutScreenBoss(void);		//画面外の処理
//============================
//ボスの初期化処理
//============================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\boss000.png",
		&s_apTextureBoss[0]);

	//ボスの情報の初期化
		s_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Boss.move = D3DXVECTOR3(1.5f, 0.0f, 0.0f);
		s_Boss.nType = 0;
		s_Boss.nLife = 0;
		s_Boss.bUse = false;	//使用していない状態にする
		s_Boss.nCntAnim = 0;
		s_Boss.nPtnAnim = 0;
		s_Boss.state = BOSSSTATE_NORMAL;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBoss,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBoss,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

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

	//頂点バッファをアンロック
	s_pVtxBuffBoss->Unlock();
}
//============================
//ボスの終了処理
//============================
void UninitBoss(void)
{
	//音声の停止
	StopSound();
	for (int nCntBoss = 0; nCntBoss < NUM_BOSS; nCntBoss++)
	{
		//テクスチャの破棄
		if (s_apTextureBoss[nCntBoss] != NULL)
		{
			s_apTextureBoss[nCntBoss]->Release();
			s_apTextureBoss[nCntBoss] = NULL;
		}
	}

	//頂点バッファを破棄
	if (s_pVtxBuffBoss != NULL)
	{
		s_pVtxBuffBoss->Release();
		s_pVtxBuffBoss = NULL;
	}
}
//============================
//ボスの更新処理
//============================
void UpdateBoss(void)
{
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
	if (s_Boss.bUse == true)
	{//ボスが使用されている場合
	 //位置の更新
		if (s_Boss.pos.x <= SCREEN_WIDTH)
		{
			s_Boss.posOld = s_Boss.pos;
			s_Boss.pos.x += s_Boss.move.x;
			s_Boss.pos.y += s_Boss.move.y;
		}
		//ブロックの上に乗っている場合
		if (s_Boss.pBlock != NULL)
		{
			//ブロックのタイプを参照
			if (s_Boss.pBlock->nType == 1)
			{
				//ブロックの移動量を加算
				s_Boss.pos += s_Boss.pBlock->move;
			}
		}
		//当たり判定
		CollisionBlock(&s_Boss.pos, &s_Boss.posOld, &s_Boss.move, BOSS_SIZE, BOSS_SIZE, &s_Boss.pBlock);
		
		if (CollisionWeapon(&s_Boss.pos, &s_Boss.posOld, &s_Boss.move, BOSS_SIZE, BOSS_SIZE) == true && s_Boss.state != BOSSSTATE_DAMAGE)
		{
			HitBoss(100);
		}

		//カウンターの更新
		if ((s_Boss.nCntAnim++ % 180) == 0)
		{//アニメーションの設定
			s_Boss.nAtkUse ^= 1;
		}

		//攻撃中なら
		if (s_Boss.nAtkUse == 1&&s_Boss.state!=BOSSSTATE_APPEAR&&s_Boss.state!=BOSSSTATE_DEATH)
		{
			if (s_Boss.nCntAnim%30==0)
			{
				PlaySound(SOUND_LABEL_SE_FIRE);
			SetBullet(s_Boss.pos- D3DXVECTOR3(0.0f, 100.0f, 0.0f),D3DXVECTOR3(1.0f,1.0f,0.0f),
				500,40.0f,40.0f);
			}
		}

		//画面の中央に来た時の設定
		CenterPlayer(&s_Boss.pos);

		//ボスが画面外に行った時の処理
		OutScreenBoss();

		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove+ s_Boss.nAtkUse), 0.5f);	//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse + 1), 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse + 1), 1.0f);
		s_Boss.move.y =(s_Boss.state==BOSSSTATE_APPEAR)? 0.0f:10.0f;
	}
		//ボスの状態管理
		StateBoss();

	//頂点バッファをアンロック
	s_pVtxBuffBoss->Unlock();
}
//==============================
//ボスの描画処理
//==============================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (s_Boss.bUse == true&&s_Boss.state!=BOSSSTATE_APPEAR)
	{//ボスが使用されている

	 //テクスチャの設定
		pDevice->SetTexture(0, s_apTextureBoss[0]);

		//ポリゴンの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
			0,										//頂点の開始場所
			2);										//プリミティブの数
	}
}
//=====================
//ボスの設定処理
//=====================
void SetBoss(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;


	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (s_Boss.bUse == false&&s_Boss.state!=BOSSSTATE_DEATH)
	{//ボスが使用されていない
	 //ボスの情報の設定
		s_Boss.pos = pos;
		s_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Boss.nLife = 2000;
		s_Boss.bUse = true;	//使用している状態にする
		s_Boss.state = BOSSSTATE_APPEAR;
		s_Boss.nAtk = 300;
		s_Boss.nCounterState = 180;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(+BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(+BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//音声の停止
		StopSound(SOUND_LABEL_BGM000);

		PlaySound(SOUND_LABEL_SE_BOSS);

	}
	//頂点バッファをアンロック
	s_pVtxBuffBoss->Unlock();
}
//=======================
//ボスのヒット処理
//=======================
void HitBoss(int nDamage)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	s_Boss.nLife -= nDamage;
	if (s_Boss.nLife <= 0)
	{//体力が０になった時
		s_Boss.bUse = false;
		//pPlayer->nLife = MAX_PLIFE;		//最大ライフ
		s_Boss.nCounterState = 60;
		s_Boss.state = BOSSSTATE_DEATH;
		//爆発の設定
		for (int e = 0; e < 30; e++)
		{
			SetEffect(
				s_Boss.pos-D3DXVECTOR3(0.0f, BOSS_SIZE/2, 0.0f)	//位置の設定
				//移動量の設定																		
				, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f
				,			  cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f, 0.0f)
				, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)		//頂点カラーの設定
				, 50									//半径の大きさの設定
				, 60									//寿命(あんまり意味ない)
				, true									//加算合成するかどうか
				, 1);									//何枚目のテクスチャを使うかどうか
		}
		AddScore(50000);

		PlaySound(SOUND_LABEL_SE_EXPLOSION);
	}
	else
	{//生きてる場合
		s_Boss.state = BOSSSTATE_DAMAGE;
		s_Boss.nCounterState = INV_TIME;//ダメージ時間を保つ時間を設定
		pPlayer->nLife += 20;

		//頂点バッファをロックし、頂点データへのポインタを取得
		s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		//ポリゴンをダメージ色に設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		s_pVtxBuffBoss->Unlock();

		//PlaySound(SOUND_LABEL_SE_HIT);
	}
}
//=====================
//状態変化の設定
//=====================
void StateBoss(void)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	switch (s_Boss.state)
	{
	case BOSSSTATE_APPEAR:
		s_Boss.nCounterState--;
		SetEffect(
			s_Boss.pos +
			D3DXVECTOR3((float)(rand() % 20 + 10), (float)(rand() % 20 + 10), 0.0f)		//位置の設定
																						//移動量の設定																		
			, D3DXVECTOR3(-sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f
				, -cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f, 0.0f)
			, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f)		//頂点カラーの設定
			, 50									//半径の大きさの設定
			, 900									//寿命(あんまり意味ない)
			, true									//加算合成するかどうか
			, 1);									//何枚目のテクスチャを使うかどうか
		if (s_Boss.nCounterState <= 0)
		{
			PlaySound(SOUND_LABEL_BGM001);
			s_Boss.state = BOSSSTATE_NORMAL;
		}
		break;
	case BOSSSTATE_NORMAL:
		s_Boss.nDirectionMove = (pPlayer->pos.x > s_Boss.pos.x) ? 0 : 2;
		break;
	case BOSSSTATE_DAMAGE:
		s_Boss.nCounterState--;
		if (s_Boss.nCounterState <= 0)
		{
			//頂点バッファをロックし、頂点データへのポインタを取得
			s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			s_Boss.state = BOSSSTATE_NORMAL;

			//ポリゴンを通常色に設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//頂点バッファをアンロック
			s_pVtxBuffBoss->Unlock();
		}
		break;
	case BOSSSTATE_DEATH:
		s_Boss.nCounterState--;
		if (s_Boss.nCounterState <= 0)
		{
			s_Boss.bUse = false;
			s_Boss.move.x = 0;
			//モードの設定(リザルト画面に移行)
			SetGameState(GAMESTATE_CLEAR);
			return;
		}
		break;
	}
}
//=====================
//画面外の処理
//=====================
static void OutScreenBoss(void)
{
	if (s_Boss.pos.x <= -BOSS_SIZE)
	{//画面外に出た場合の処理(左端)
		s_Boss.pos.x = BOSS_SIZE;
		s_Boss.bUse = false;		//使用していない状態にする
	}
	if (s_Boss.pos.y >= SCREEN_HEIGHT + BOSS_SIZE)
	{//画面外に出た場合の処理(下端)
		s_Boss.bUse = false;		//使用していない状態にする
	}
}
//=====================
//ボスの当たり判定
//=====================
void CollisionBoss(D3DXVECTOR3 *pPos, float Width, float Height)
{
	if (s_Boss.bUse == true)
	{//プレイヤーが使用されている 
	 //プレイヤーに相手がぶつかった時
		if (pPos->y  >= s_Boss.pos.y - BOSS_SIZE
			&& pPos->y - Height <= s_Boss.pos.y
			&&pPos->x - Width / 2 <= s_Boss.pos.x + BOSS_SIZE / 2 - 50
			&& pPos->x + Width / 2 >= s_Boss.pos.x - BOSS_SIZE / 2 + 50)
		{//プレイヤ-とプレイヤーが当たった時
			HitPlayer(s_Boss.nAtk);
		}
	}
}
//=====================
//ボスの取得処理
//=====================
BOSS *GetBoss(void)
{//ボスのポインタをリセット
	return &s_Boss;
}