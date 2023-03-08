//=================================================
// Content     (プレイヤーの操作)(player.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/10/04)
//=================================================
#include"player.h"
#include"input.h"
#include"playereffect.h"
#include"block.h"
#include"Attack.h"
#include"game.h"
#include"enemy.h"
#include"effect.h"
#include"boss.h"
#include"bullet.h"
#include"boss.h"
#include"sound.h"

//スタティック変数
static LPDIRECT3DTEXTURE9 s_pTexturePlayer = NULL;				//プレイヤーのテクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPlayer = NULL;			//プレイヤーの頂点バッファへのポインタ
static Player s_Player;											//プレイヤーの情報
static int s_nTimer;											//時計
static int s_Commandmemory[MAX_KEYMEMORY];						//コマンド技用メモリー

//プロトタイプ宣言
static void ResetPlayer(void);						//初期化
static void ControlPlayer(void);					//操作関係の処理
static void GroundPlayer(void);						//地面に面している時の処理
static void ComandPlayer(void);						//コマンド技
static void	KeyMemory(int nKey);					//入力情報の記憶
static void SidePlayer(void);						//画面外についた時の処理
static void UpdatePlayerState(void);				//情報更新
static void PlayerJunp(void);						//ジャンプ関係の処理
static void PlayerPositionUpdate(void);				//位置の更新
static void Playerstate(void);						//状態管理
static void PlayerAttack(void);						//プレイヤーの攻撃
//======================================================
//プレイヤーの初期化処理
//======================================================
void InitPlayer(void)
{
    ResetPlayer();		//プレイヤーの情報の初期化
}
//======================================================
//プレイヤーの終了処理
//======================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (s_pTexturePlayer != NULL)
	{
		s_pTexturePlayer->Release();
		s_pTexturePlayer = NULL;
	}
	//頂点バッファを破棄
	if (s_pVtxBuffPlayer != NULL)
	{
		s_pVtxBuffPlayer->Release();
		s_pVtxBuffPlayer = NULL;
	}
}
//======================================================
//プレイヤーの更新処理
//======================================================
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;
	if (s_Player.bDisp==true)
	{
		s_Player.bIsDashing = false;	//ダッシュ解除

		//プレイヤーの操作関係
		ControlPlayer();

		//プレイヤーの位置の更新関係の処理
		PlayerPositionUpdate();

		//プレイヤーのコマンド技
		ComandPlayer();

		//ブロックの当たり判定と着地判定
		s_Player.bIsJumping = !CollisionBlock(&s_Player.pos, &s_Player.posOld, &s_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT, &s_Player.pBlock);

		//エネミーの当たり判定
		CollisionEnemy(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//弾の当たり判定
		CollisionBullet(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//ボスの当たり判定
		CollisionBoss(&s_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

		//プレイヤーが画面外に到達した際にループさせる処理
		SidePlayer();

		//移動量更新(減衰させる)
		s_Player.move.x += (0.0f - s_Player.move.x)*MIN_SPEED;
		s_Player.move.y += 1.0f;

		//地面に接している時の処理
		GroundPlayer();

		//プレイヤーのジャンプ関係の処理
		PlayerJunp();

		//ダッシュ中の残像の設定
		if (s_nTimer % 5 == 0 && s_Player.bIsDashing == true)
		{//頂点バッファをロックし、頂点情報へのポインタを取得
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//残像の設定
			SetPlayereffect(s_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.5f), (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 60, pVtx[0].tex, pVtx[1].tex, pVtx[2].tex, pVtx[3].tex);

			//頂点バッファをアンロック
			s_pVtxBuffPlayer->Unlock();
		}

		//プレイヤーの情報更新
		UpdatePlayerState();

		//プレイヤーの攻撃
		PlayerAttack();

		//常に体力が減るようにする
		s_Player.nLife--;
	}
		//プレイヤーの状態管理
		Playerstate();

	if (s_Player.nLife <= 0)
	{
		HitPlayer(0);
	}
	s_nTimer++;		//タイマーカウント増加
}
//======================================================
//プレイヤーの描画処理
//======================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//プレイヤーが使用されている状態
	if (s_Player.bDisp == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_pTexturePlayer);

		//プレイヤーの描画       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//======================================================
//プレイヤーの設定
//======================================================
void SetPlayer(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (s_Player.bDisp == false)
	{//ブロックが使用されていない
		s_Player.pos = pos;
		s_Player.nLife = MAX_PLIFE;
		s_Player.state = PLAYERSTATE_NORMAL;		//通常状態にする
		s_Player.bDisp = true;						//使用している状態にする

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
		pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
		pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;
		pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove + TEX_X, 0.0f);	//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove) - TEX_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove + TEX_X, 0.2f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove) - TEX_X, 0.2f);
	}
	//頂点バッファをアンロック
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//プレイヤーの操作関係の処理
//======================================================
void ControlPlayer(void)
{
	//頂点座標へのポインタ
	if (GetKeyboardPress(DIK_LSHIFT) == true|| GetJoypadPress(JOYKEY_RB) == true)
	{//LSHIFTでダッシュ状態へ以降
		s_Player.bIsDashing = true;
	}
	if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true || GetJoypadStick(JOYKEY_LSTICK).x <= -1.0f)
	{//Aキーが押された
		s_Player.nDirectionMove = 1;		//左向きにする
		if (s_Player.bIsDashing == true)
		{
			s_Player.move.x -= sinf(D3DX_PI*0.5f)*DASH_SPEED;
		}
		else
		{
			s_Player.move.x -= sinf(D3DX_PI*0.5f)*NOMAL_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true || GetJoypadStick(JOYKEY_LSTICK).x >= 1.0f)
	{//Dキーが押された
		s_Player.nDirectionMove =0;			//右向きにする
		if (s_Player.bIsDashing == true)
		{
			s_Player.move.x += sinf(D3DX_PI*0.5f)*DASH_SPEED;
		}
		else
		{
			s_Player.move.x += sinf(D3DX_PI*0.5f)*NOMAL_SPEED;
		}
	}
	//攻撃の設定
	if (GetKeyboardTrigger(DIK_RETURN) == true && s_Player.bAtk != true || GetJoypadPress(JOYKEY_X) == true && s_Player.bAtk != true)
	{//ENTERキーが押された
		int Direction = (s_Player.nDirectionMove == 1) ? -1 : 1;
		s_Player.bAtk = true;
		s_Player.nCntCounterAnim = 0;			//アニメカウンターのリセット
		s_Player.nCntPtnAnim = 0;				//パターンのリセット
		s_Player.nCntAtk = ALL_ATKTIME1;		//状態管理カウンターの設定
		Setweapon(s_Player.pos.x - 40.0f*Direction, s_Player.pos.y - 14.0f, 2.0f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), FIRST_ATKTIME,false);
		PlaySound(SOUND_LABEL_SE_SWORDATTACK);
	}
}
//======================================================
//プレイヤーが地面に面している時の処理
//======================================================
void GroundPlayer(void)
{
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (s_Player.bIsJumping == false && s_Player.bAtk == false)
	{//ジャンプしていないとき
		if(s_Player.move.x < MIN_SPEED && s_Player.move.x > -MIN_SPEED)
		{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove+ TEX_X, 0.01f);	//右回りに座標を指定
				pVtx[1].tex = D3DXVECTOR2(0.25f*(1+s_Player.nDirectionMove)- TEX_X, 0.01f);
				pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nDirectionMove+ TEX_X, 0.2f);
				pVtx[3].tex = D3DXVECTOR2(0.25f*(1 + s_Player.nDirectionMove)- TEX_X, 0.2f);
		}
		else if (s_Player.move.x >= MIN_SPEED || s_Player.move.x <= -MIN_SPEED)
		{//移動中の場合アニメーションを更新
			if (s_Player.nCntCounterAnim++ % 10 == 0)
			{
				s_Player.nCntPtnAnim++;
				s_Player.nCntPtnAnim %= 4;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));	//右回りに座標を指定
			pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));
			pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
		}
	}
			
	//頂点バッファをアンロック
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//プレイヤーのコマンド技
//======================================================
void ComandPlayer(void)
{
	//キーの記憶処理
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		KeyMemory(DIK_W);
	}
	else if (GetKeyboardTrigger(DIK_A) == true)
	{
		KeyMemory(DIK_A);
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{
		KeyMemory(DIK_S);
	}
	else if (GetKeyboardTrigger(DIK_D) == true)
	{
		KeyMemory(DIK_D);
	}
	//ハイジャンプ
	if (s_Commandmemory[0] == DIK_S&& s_Commandmemory[1] == DIK_S&& GetKeyboardTrigger(DIK_RETURN)==true)
	{
		s_Player.move.y -= 30.0f;
	}
	//高速移動
	if (s_Commandmemory[0] == DIK_A&& s_Commandmemory[1] == DIK_S&& s_Commandmemory[2] == DIK_D&& GetKeyboardTrigger(DIK_RETURN) == true)
	{
		s_Player.bIsDashing = true;
		s_Player.move.x -= 30.0f;
	}
}
//======================================================
//プレイヤーの入力情報の記憶
//======================================================
void KeyMemory(int nKey)		
{
	int nSaveKey=0;
	for (int nCnt = 0; nCnt < MAX_KEYMEMORY; nCnt++)
	{
		nSaveKey = s_Commandmemory[nCnt + 1];
		s_Commandmemory[nCnt + 1] = s_Commandmemory[nCnt];
		s_Commandmemory[nCnt] = nSaveKey;
	}
	s_Commandmemory[0] = nKey;								
}
//=====================
//プレイヤーのの当たり判定
//=====================
void CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height)
{
	//ブロックがプレイヤーに当たった時の判定は別々で作らないといけない
	if (s_Player.bDisp == true)
	{//ブロックが使用されている 
	 //ブロックに相手がぶつかった時
	 //横からぶつかった場合
		if (pPosOld->y + Height / 2 > s_Player.pos.y - PLAYER_HEIGHT 	//ブロックの上下の範囲指定
			&& pPosOld->y - Height / 2 < s_Player.pos.y )
		{
			//横からぶつかった場合(右辺に相手が当たった場合)
			if (pPosOld->x - Width / 2 >= s_Player.pos.x + PLAYER_WIDTH / 2//前回のプレイヤーの位置がブロックの位置より右にいる場合
				&& pPos->x - Width / 2 < s_Player.pos.x + PLAYER_WIDTH / 2 //現在のプレイヤーの位置がブロックの位置より左にいる(めり込んでいる)場合
				)//プレイヤーの左右にブロックが当たった場合
			{//プレイヤ-とブロックが当たった時
				pMove->x = 0;
				s_Player.pos.x = pPos->x- Width / 2 - PLAYER_WIDTH / 2;
			}
			//横からぶつかった場合(左辺に相手が当たった場合)
			else if (pPosOld->x + Width / 2  <= s_Player.pos.x - PLAYER_WIDTH / 2 	//前回のプレイヤーの位置がブロックの位置より左にいる場合
				&& pPos->x + Width / 2  > s_Player.pos.x - PLAYER_WIDTH / 2			//現在のプレイヤーの位置がブロックの位置より右にいる(めり込んでいる)場合
				)//プレイヤーの左右にブロックが当たった場合
			{//プレイヤ-とブロックが当たった時
				pMove->x = 0;
				s_Player.pos.x = pPos->x + Width / 2 + PLAYER_WIDTH / 2 ;
			}
		}
	}
}
//======================================================
//プレイヤーの情報リセットの処理
//======================================================
void ResetPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player001.png",
		&s_pTexturePlayer);

	s_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
	s_Player.move = D3DXVECTOR3(0.0f, 0.f, 0.0f);							//移動量を初期化する
	//s_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//角度の初期化する(そのうち使うかも？)
	s_Player.nCntCounterAnim = 0;											//カウンターを初期化
	s_Player.nCntPtnAnim = 0;												//パターン番号を初期化//向きを初期化	
	s_Player.nDirectionMove = 0;											//０の時は右　１の時は左向き									
	s_Player.bDisp = false;													//使用中にする
	s_Player.bIsJumping = false;											//ジャンプ状態解除にする
	s_Player.state = PLAYERSTATE_NORMAL;									//通常状態にする
	s_nTimer = 0;															//タイマーリセット
	s_Player.nCntAtk = 0;													//攻撃カウントリセット

	//頂点座標へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffPlayer,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//右回りに座標を指定
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロック
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//プレイヤーの情報更新
//======================================================
static void UpdatePlayerState(void)
{
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, -PLAYER_HEIGHT, 0.0f) + s_Player.pos;
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, 0.0f) + s_Player.pos;

	//頂点バッファをアンロック
	s_pVtxBuffPlayer->Unlock();
}
//======================================================
//プレイヤーが画面端についた時の処理
//======================================================
static void SidePlayer(void)
{
	//画面外にいった場合
	if (s_Player.pos.x > SCREEN_WIDTH - PLAYER_WIDTH/2)
	{//始点(X座標)が画面の右端に当たった
		s_Player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
	}
	else if (s_Player.pos.x < PLAYER_WIDTH/2)
	{//始点(X座標)が画面の左端に当たった
		s_Player.pos.x = PLAYER_WIDTH/2;
	}
}
//======================================================
//プレイヤーのジャンプ関係の処理
//======================================================
static void PlayerJunp(void)
{
	VERTEX_2D*pVtx;
	if ((GetKeyboardTrigger(DIK_SPACE) == true||GetJoypadTrigger(JOYKEY_A)) && s_Player.bIsJumping == false )
	{//SPACEキーが押された
		s_Player.move.y += -20.0f;
		if (s_Player.bAtk==false)
		{
			//ジャンプする際立ちモーションの場合歩きモーションに移行させる
			if (s_Player.nCntPtnAnim % 2 == 0 && s_Player.state != PLAYERSTATE_ATTACK)
			{
				s_Player.nCntPtnAnim++;
			}

			//頂点バッファをロックし、頂点情報へのポインタを取得
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));	//右回りに座標を指定
			pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.81f - (0.2f*s_Player.nDirectionMove));
			pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 1.0f - (0.2f*s_Player.nDirectionMove));
			//頂点バッファをアンロック
			s_pVtxBuffPlayer->Unlock();
		}
	}
	else if ((GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A)) && s_Player.bIsJumping == true)
	{//SPACEキーが押された
		s_Player.move.y -= -20.0f;
	}
}
//======================================================
//プレイヤーの位置の更新
//======================================================
static void PlayerPositionUpdate(void)
{
	//前回の位置を記録
	s_Player.posOld = s_Player.pos;

	//位置を更新
	s_Player.pos.x += s_Player.move.x;
	s_Player.pos.y += s_Player.move.y;

	//ブロックの上に乗っている場合
	if (s_Player.pBlock != NULL)
	{
		//ブロックのタイプを参照
		if (s_Player.pBlock->nType == 1)
		{
			//ブロックの移動量を加算
			s_Player.pos += s_Player.pBlock->move;
		}
	}
}
//======================================================
//プレイヤーの状態管理
//======================================================
static void Playerstate(void)
{
	VERTEX_2D*pVtx;

	switch (s_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		s_Player.nCntState--;
		if ((s_Player.nCntState % 5) == 0)
		{
			s_Player.fPtnflashing = 1 - s_Player.fPtnflashing;
		}
		//頂点バッファをロックし、頂点データへのポインタを取得
		s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//ポリゴンをダメージ色に設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, s_Player.fPtnflashing);
		//頂点バッファをアンロック
		s_pVtxBuffPlayer->Unlock();

		if (s_Player.nCntState <= 0)
		{//無敵時間が解除されたとき

			s_Player.fPtnflashing = 0.0f;
			//頂点バッファをロックし、頂点データへのポインタを取得
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			s_Player.state = PLAYERSTATE_NORMAL;

			//ポリゴンを通常色に設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//頂点バッファをアンロック
			s_pVtxBuffPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		s_Player.nCntState--;
		if (s_Player.nCntState <= 0)
		{
			s_Player.move.x = 0;
			s_Player.state = PLAYERSTATE_NORMAL;
			//モードの設定(リザルト画面に移行)
			SetGameState(GAMESTATE_FAILED);
			return;
		}
		break;
	}
}
//=======================
//プレイヤーのヒット処理
//=======================
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;
	if (s_Player.bDisp==true&&s_Player.state==PLAYERSTATE_NORMAL)
	{
		s_Player.nLife -= nDamage;
		if (s_Player.nLife <= 0)
		{//体力が０になった時
			s_Player.nLife = 0;
			s_Player.state = PLAYERSTATE_DEATH;
			s_Player.nCntState = 60;
			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				SetEffect(
					s_Player.pos + D3DXVECTOR3((float)(rand() % 20 - 10), (float)(rand() % 20 - 10), 0.0f)		//位置の設定
																													//移動量の設定
					, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f, 0.0f)
					, D3DXCOLOR(1.0f, 0.0f,0.0f, 1.0f)		//頂点カラーの設定
					, 30			//半径の大きさの設定
					, 90
					,false
					,0);
			}
			s_Player.bDisp = false;
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}
		else
		{//生きてる場合
			s_Player.state = PLAYERSTATE_DAMAGE;
			s_Player.nCntState = 30;//ダメージ時間を保つ時間を設定

			//頂点バッファをロックし、頂点データへのポインタを取得
			s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//ポリゴンをダメージ色に設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			//頂点バッファをアンロック
			s_pVtxBuffPlayer->Unlock();

			PlaySound(SOUND_LABEL_SE_HIT);
		}

	}
}
//======================================================
//プレイヤーの攻撃
//======================================================
static void PlayerAttack(void)
{
	VERTEX_2D*pVtx;
	if (s_Player.bAtk == true)
	{
		int Direction = (s_Player.nDirectionMove == 1) ? -1 : 1;

		s_Player.nCntAtk--;
		//剣とエフェクトと当たり判定の設定
		if (s_Player.nCntAtk == ALL_ATKTIME1 - FIRST_ATKTIME * 2)
		{//三枚目のモーション判定
			s_Player.nCntPtnAnim++;
			SetAttack(s_Player.pos.x + 52.0f*Direction, s_Player.pos.y - 48.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f, Direction);
			Setweapon(s_Player.pos.x + 50.0f*Direction, s_Player.pos.y - 15.0f, 4.5f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ALL_ATKTIME1 - FIRST_ATKTIME * 2, true);
		}
		else if (s_Player.nCntAtk == ALL_ATKTIME1 - FIRST_ATKTIME)
		{//二枚目のモーション再生時に当たり判定と剣の設定
			s_Player.nCntPtnAnim++;
			Setweapon(s_Player.pos.x - 30.0f*Direction, s_Player.pos.y - 65.0f, -0.2f*Direction, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), FIRST_ATKTIME, false);
		}
		//寿命が終わったら
		if (s_Player.nCntAtk <= 0)
		{
			s_Player.nCntCounterAnim = 0;			//アニメカウンターのリセット
			s_Player.nCntAtk = 0;					//カウンターのリセット
			s_Player.nCntPtnAnim = 0;				//パターンのリセット
			s_Player.bAtk = false;
		}
		//頂点バッファをロックし、頂点データへのポインタを取得
		s_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.41f - (0.2f*s_Player.nDirectionMove));	//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.41f - (0.2f*s_Player.nDirectionMove));
		pVtx[2].tex = D3DXVECTOR2(0.25f*s_Player.nCntPtnAnim + TEX_X, 0.6f - (0.2f*s_Player.nDirectionMove));
		pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Player.nCntPtnAnim + 1) - TEX_X, 0.6f - (0.2f*s_Player.nDirectionMove));
		//頂点バッファをアンロック
		s_pVtxBuffPlayer->Unlock();
	}
}
//=====================================================
//プレイヤーが画面の中心に来た時の場合
//=====================================================
void CenterPlayer(D3DXVECTOR3 *pPos)
{
	//ボスの取得
	BOSS*pBoss = GetBoss();
	if (s_Player.pos.x >= SCREEN_WIDTH / 2&&pBoss->bUse==false&&pBoss->state!=BOSSSTATE_DEATH)
	{
		//被害者の位置を更新
		s_Player.pos.x = SCREEN_WIDTH / 2;
		pPos->x -= s_Player.move.x;
	}
}
//======================================================
//プレイヤーの取得処理
//======================================================
Player *GetPlayer(void)
{//エネミーのポインタをリセット
	return &s_Player;
}