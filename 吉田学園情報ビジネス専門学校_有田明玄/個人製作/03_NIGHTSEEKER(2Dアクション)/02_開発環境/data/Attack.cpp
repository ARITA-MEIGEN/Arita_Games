//=================================================
// Content     (エフェクトの処理)(Attack.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/11/04)
//=================================================
#include"Attack.h"
#include"player.h"
#include"sound.h"

//マクロ定義
#define NUM_ATTACK		(5)			//テクスチャの枚数
#define WEAPON_SIZE		(40.0f)		//武器の大きさ
#define EFFECT_SPEED	(1)			//エフェクトの速度

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureAttack = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttack = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWeapon = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWeapon = NULL;	//頂点バッファへのポインタ
Attack g_Attack;									//エフェクトの情報
static Weapon s_weapon;								//武器の情報
//============================
//エフェクトの初期化処理
//============================
void InitAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Attack000.png",
		&g_pTextureAttack);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAttack,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);

	//武器の情報の初期化
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

	g_Attack.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	g_Attack.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	g_Attack.fRadiuswidth = 0;							//半径(大きさ)
	g_Attack.bUse = false;								//使用しているかどうかの判定
	g_Attack.nCntAnim = 0;								//エフェクトのカウンター
	g_Attack.nPtnAnim = 0;								//アニメーションの番号

	//頂点バッファをアンロック
	g_pVtxBuffAttack->Unlock();

//武器の設定
		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\weapon000.png",
		&g_pTextureWeapon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWeapon,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
	//対角線の長さを算出する
	s_weapon.fLength = sqrtf((WEAPON_SIZE*WEAPON_SIZE) + (WEAPON_SIZE*WEAPON_SIZE)) / 2.0f;

	//対角線の角度を算出する
	s_weapon.fAngle = atan2f(WEAPON_SIZE, WEAPON_SIZE);
	//武器の情報の初期化
	//頂点座標の設定
	pVtx[0].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
	pVtx[3].pos.z = 0.0f;

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

	s_weapon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	s_weapon.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	g_Attack.fRadiuswidth = 0;							//半径(大きさ)
	s_weapon.bDisp = false;								//使用しているかどうかの判定

	//頂点バッファをアンロック
	g_pVtxBuffWeapon->Unlock();
}
//===========================
//エフェクトの終了処理
//===========================
void UninitAttack(void)
{
	if (g_pTextureAttack != NULL)
	{
		g_pTextureAttack->Release();
		g_pTextureAttack = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffAttack != NULL)
	{
		g_pVtxBuffAttack->Release();
		g_pVtxBuffAttack = NULL;
	}
	if (g_pTextureWeapon != NULL)
	{
		g_pTextureWeapon->Release();
		g_pTextureWeapon = NULL;
	}
	//頂点バッファを破棄
	if (g_pVtxBuffWeapon != NULL)
	{
		g_pVtxBuffWeapon->Release();
		g_pVtxBuffWeapon = NULL;
	}
}
//===========================
//エフェクトの更新処理
//===========================
void UpdateAttack(void)
{

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);
	if (g_Attack.bUse == true)
	{//エフェクトが使用されている
		if (g_Attack.nCntAnim++ % EFFECT_SPEED == 0)
		{
			if (g_Attack.nPtnAnim++ >= NUM_ATTACK - 1)
			{
				g_Attack.nPtnAnim = 0;
				g_Attack.bUse = false;
			}
		}
		Player*pPlayer = GetPlayer();
		g_Attack.pos += pPlayer->move;//武器の中心点にプレイヤーの移動量を加算
		g_Attack.pos.y -= 1.0f;
		//画面の中央に来た時の設定
		CenterPlayer(&g_Attack.pos);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight/2, 0.0f) + g_Attack.pos;
		pVtx[1].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight/2, 0.0f) + g_Attack.pos;
		pVtx[2].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[3].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*((g_Attack.nPtnAnim + 1) * g_Attack.nDirection), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*g_Attack.nPtnAnim*g_Attack.nDirection, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*((g_Attack.nPtnAnim + 1)* g_Attack.nDirection), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUM_ATTACK*g_Attack.nPtnAnim*g_Attack.nDirection, 1.0f);
	}
	//頂点バッファをアンロック
	g_pVtxBuffAttack->Unlock();

	//剣の更新
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
	if (s_weapon.bDisp == true)
	{//武器が使用されている
		Player*pPlayer = GetPlayer();
		s_weapon.pos += pPlayer->move;//武器の中心点にプレイヤーの移動量を加算
		s_weapon.pos.y -= 1.0f;
		//画面の中央に来た時の設定
		CenterPlayer(&s_weapon.pos);
		//寿命を減らす
		if (s_weapon.nLife--<=0)
		{
			s_weapon.bDisp = false;
		}
		//頂点座標の更新
		pVtx[0].pos.x = s_weapon.pos.x  + sinf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = s_weapon.pos.x  + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = s_weapon.pos.x   + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = s_weapon.pos.x   + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.z = 0.0f;

		//頂点バッファをアンロック
		g_pVtxBuffWeapon->Unlock();
	}
}
//===========================
//エフェクトの描画処理
//===========================
void DrawAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffAttack, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureAttack);

		if (g_Attack.bUse == true)
		{
			//ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				0,										//頂点の開始場所
				2);										//プリミティブの数
		}

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWeapon, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWeapon);

		if (s_weapon.bDisp == true)
		{
			//ポリゴンの描画       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
				0,										//頂点の開始場所
				2);										//プリミティブの数
		}
}
//===========================
//エフェクトの設定処理
//===========================
void SetAttack(float posx, float posy, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight,int nDirection)
{
	if (g_Attack.bUse == false)
	{
		VERTEX_2D*pVtx;
		//情報の設定
		g_Attack.pos.x = posx;
		g_Attack.pos.y = posy;
		g_Attack.pos.z = 0.0f;
		g_Attack.col = col;
		g_Attack.fRadiuswidth = fRadiuswidth;
		g_Attack.fRadiusheight = fRadiusheight;
		g_Attack.nCntAnim = 0;
		g_Attack.nPtnAnim = 0;
		g_Attack.bUse = true;
		g_Attack.nDirection = nDirection;

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffAttack->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定	(大きさを小さくする)
		pVtx[0].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[1].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, -g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[2].pos = D3DXVECTOR3(-g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;
		pVtx[3].pos = D3DXVECTOR3(g_Attack.fRadiuswidth / 2, g_Attack.fRadiusheight / 2, 0.0f) + g_Attack.pos;

		//頂点カラーの設定
		pVtx[0].col = g_Attack.col;
		pVtx[1].col = g_Attack.col;
		pVtx[2].col = g_Attack.col;
		pVtx[3].col = g_Attack.col;

		//頂点バッファをアンロック
		g_pVtxBuffAttack->Unlock();
	}
}
//===========================
//武器の設定
//===========================
void Setweapon(float posx, float posy,float posz, D3DXCOLOR col, int Life,bool collision)
{
	VERTEX_2D*pVtx;
	if (s_weapon.bDisp == false)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);
		//対角線の長さを算出する
		s_weapon.fLength = sqrtf((WEAPON_SIZE*WEAPON_SIZE) + (WEAPON_SIZE*WEAPON_SIZE)) / 1.0f;

		//対角線の角度を算出する
		s_weapon.fAngle = atan2f(WEAPON_SIZE, WEAPON_SIZE);
				
		s_weapon.pos.x = posx;				//位置
		s_weapon.pos.y = posy;				//位置
		s_weapon.pos.z = posz;
		s_weapon.col = col;					//色
		s_weapon.nLife=Life;				//寿命
		s_weapon.bDisp=true;				//使用しているかどうかの判定
		s_weapon.bCollision= collision;		//当たり判定を使うかどうか

		//武器の情報の初期化
		//頂点座標の設定
		pVtx[0].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - D3DX_PI + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + D3DX_PI - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z - s_weapon.fAngle)*s_weapon.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = s_weapon.pos.x + sinf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.y = s_weapon.pos.y + cosf(s_weapon.pos.z + s_weapon.fAngle)*s_weapon.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー設定
		pVtx[0].col = s_weapon.col;
		pVtx[1].col = s_weapon.col;
		pVtx[2].col = s_weapon.col;
		pVtx[3].col = s_weapon.col;

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//右回りに座標を指定
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffWeapon->Unlock();
	}
}
//===========================
//武器の当たり判定設定
//===========================
bool CollisionWeapon(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height)
{
	bool bIsHit = false;		//着地しているかどうか

	//武器に相手がぶつかった時
	if (s_weapon.bDisp == true && s_weapon.bCollision == true)
	{//武器が使用されている 
		 //敵にプレイヤーの攻撃がぶつかった時
		if (pPos->y >= s_weapon.pos.y - WEAPON_SIZE
			&& pPos->y - Height <= s_weapon.pos.y
			&&pPos->x - Width / 2 <= s_weapon.pos.x + WEAPON_SIZE
			&& pPos->x + Width / 2 >= s_weapon.pos.x - WEAPON_SIZE)
		{//プレイヤ-とプレイヤーが当たった時
			bIsHit = true;
			PlaySound(SOUND_LABEL_SE_HITSWORDATTACK);
			pMove->y = 0;
		}
	}
	return bIsHit;
}