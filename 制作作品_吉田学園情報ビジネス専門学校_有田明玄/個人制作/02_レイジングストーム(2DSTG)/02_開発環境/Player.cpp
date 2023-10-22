//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Player.h"
#include"renderer.h"
#include"Application.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Option.h"
#include"Enemy.h"
#include"Item.h"
#include"Lifegauge.h"
#include"sound.h"
#include"Fade.h"
#include"Special.h"
#include"Effect.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"Game.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYER_TEX] = {};
int CPlayer::m_nLife=0;
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer() :CObject2D(OBJTYPE_PLAYER)
{
	m_Move = { 0.0f,0.0f,0.0f };
	SetObjType(OBJTYPE_PLAYER);
	nCnt = 0;
	nCntState = 0;
	fPtntitle = 0.0f;
	m_state = PLAYERSTATE_APPEAR;
	m_nLife = PLAYER_DEFAULTLIFE;
	bFusion = false;
	m_nRedCT = 0;
	m_nBlueCT = 0;
	m_nYellowCT = 0;
	m_nSpecial = 0;

	//仮配置
	m_apOption[0] = COption::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));
	m_apOption[1] = COption::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CPlayer::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	BindTexture(m_apTexture[0]);	//テクスチャの設定
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CPlayer::Update()
{
	CObject2D::Update();				//更新
	Move();								//移動
	CBullet::GetPlayerPos(GetPos());	//弾に現在の座標を送る
	COption::MemPos(GetPos());			//位置をオプションに記録させる
	StateManagement();					//状態管理
	AutoShot();							//連射

	if (bFusion == true&&bShot==true)
	{//合体攻撃中
		CSpecial::AddSpecial(-0.7f);
	}
}

//=============================================================================
// 描画
//=============================================================================
void  CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// プレイヤー生成
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer;
	if (pPlayer != nullptr)
	{// ポリゴンの初期化処理
		pPlayer->Init(PLAYER_WIDTH, PLAYER_HEIGHT);
		pPlayer->SetPos(pos);
		COption::ResetPos(pPlayer->GetPos());			//リセット
	}
	return pPlayer;
}

//=============================================================================
// 移動
//=============================================================================
void CPlayer::Move(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	D3DXVECTOR3 pos = GetPos();

	if (pKeyboard->GetPress(DIK_W) || JOYPAD_UP)
	{
		m_Move.y = -PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_A)||JOYPAD_LEFT)
		{
			m_Move.x = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if(pKeyboard->GetPress(DIK_D)||JOYPAD_RIGHT)
		{
			m_Move.x = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_S) || JOYPAD_DOWN)
	{
		m_Move.y = PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_A)||JOYPAD_LEFT)
		{
			m_Move.x = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_D)||JOYPAD_RIGHT)
		{
			m_Move.x = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_A) || JOYPAD_LEFT)
	{
		m_Move.x = -PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_W)||JOYPAD_UP)
		{
			m_Move.y = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_S)||JOYPAD_DOWN)
		{
			m_Move.y = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_D) || JOYPAD_RIGHT)
	{
		m_Move.x = PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_W)||JOYPAD_UP)
		{
			m_Move.y = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_S)||JOYPAD_DOWN)
		{
			m_Move.y = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}

	if (pKeyboard->GetTrigger(DIK_LSHIFT)||pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A)|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B))
	{//合体
		Fusion();
	}

	//位置を更新
	if (bFusion==true)
	{
		m_Move.x *= 0.5f;
		m_Move.y *= 0.5f;
	}
	pos.x += m_Move.x;
	pos.y += m_Move.y;
	m_Move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//位置の反映
	SetPos(pos);

	//画面外にいった場合
	Offscreen();

}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CPlayer::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_RED001.png",
		&m_apTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\FUSION001.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CPlayer::Unload()
{
	for (int i = 0; i < PLAYER_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 当たり判定まわりのやつ
//=============================================================================
void CPlayer::Hit()
{
	for (int j = 0; j < MAX_TYPE; j++)
	{
		for (int i = 0; i < MAX_POLYGON; i++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(i,j);
			if (pObject != nullptr)
			{
				CObject::EObjType objType;
				objType = pObject->GetObjType(i,j);			//種類の取得

				D3DXVECTOR3 PlayerPos = CObject2D::GetPos();
				D3DXVECTOR2 PlayerSiz = CObject2D::GetSiz();	//相手のサイズを取得

				switch (objType)
				{
				case OBJTYPE_ENEMY:
				{
					CEnemy *pEnemy = (CEnemy*)pObject;
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();	//相手の位置情報取得
					D3DXVECTOR2 EnemySiz = pEnemy->GetSiz();	//相手のサイズを取得
					if (CObject2D::Hit(PlayerPos, EnemyPos, PlayerSiz / 2, EnemySiz) == true&&pEnemy->GetState()!=(CEnemy::ENEMYSTATE_APPEAR, CEnemy::ENEMYSTATE_DEATH))
						//当たり判定の処理 2で割っているのは当たり判定の調整
					{
						//ダメージ処理                                            
						Damage();
					}
				}
				break;

				case OBJTYPE_ITEM:
				{
					CItem *pItem = (CItem*)pObject;
					D3DXVECTOR3 ItemPos = pItem->GetPos();	//アイテムの位置情報取得
					D3DXVECTOR2  ItemSiz = pItem->GetSiz();	//アイテムのサイズを取得
					if (CObject2D::Hit(PlayerPos, ItemPos, PlayerSiz, ItemSiz) == true)	//当たり判定の処理！2で割っているのは当たり判定の調整
					{
						PlaySound(SOUND_LABEL_SE_HEAL);
						m_nLife++;
						CLife::LifeRecovery();
						pItem->Uninit();
						if (m_nLife <= 3)
						{
							m_apOption[m_nLife - 2] = COption::Create(GetPos());
						}
						else if (m_nLife >= PLAYER_MAXLIFE)
						{//最大体力を超えた場合
							m_nLife = PLAYER_MAXLIFE;
						}
					}

				}
				default:
					break;
				}
			}
		}
	}
}

//=============================================================================
// 体力の減少
//=============================================================================
int CPlayer::GetLife()
{
	return m_nLife;
}

//=============================================================================
// 連射処理
//=============================================================================
void CPlayer::AutoShot()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	if (bFusion == false)
	{//合体していないとき
		if (pKeyboard->GetPress(DIK_SPACE) == true||JOYPAD_SHOT)
		{
			if (ShotTimer % RED_RATE == 0 && m_nRedCT <= 0)
			{//赤
				Shot(0);
				PlaySound(SOUND_LABEL_SE_REDBEAM);
				m_nRedCT = RED_RATE;
			}
			if (ShotTimer % BLUE_RATE == 0 && m_apOption[0] != nullptr&&m_nBlueCT <= 0)
			{//青
				Shot(1);
				PlaySound(SOUND_LABEL_SE_BLUEMISSILE);
				m_nBlueCT = BLUE_RATE;
			}
			if (ShotTimer % YELLOW_RATE == 0 && m_apOption[1] != nullptr&&m_nYellowCT <= 0)
			{//黄
				Shot(2);
				m_nYellowCT = YELLOW_RATE;
			}
			ShotTimer++;
		}
		else
		{
			ShotTimer = 0;
		}
	}
	else
	{//合体時
		if ((bShot == false) &&
			(CSpecial::GetSpecial() > 0.0f) && (pKeyboard->GetPress(DIK_SPACE) || JOYPAD_SHOT))
		{
			Shot(0);
			bShot = true;
			CBullet::SetBeam(true);
			PlaySound(SOUND_LABEL_SE_FUSIONSHOT);
		}
	}

	if (CSpecial::GetSpecial() <= 0.0f && (bFusion == true))
	{//ゲージがなくなった場合
		Separation();
	}

	if ((bShot == true) &&
		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_X)==false &&pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_Y)==false &&
			pKeyboard->GetPress(DIK_SPACE)==false)  ||
			(bFusion==false))
	{//離したとき
		bShot = false;
		CBullet::SetBeam(false);
		StopSound(SOUND_LABEL_SE_FUSIONSHOT);
	}


	m_nRedCT--;
	m_nBlueCT--;
	m_nYellowCT--;
}

//=============================================================================
// 射撃
//=============================================================================
void CPlayer::Shot(int number)
{
	//射撃
	if (bFusion == false)
	{//分離攻撃
		D3DXVECTOR3 pos = GetPos();

		switch (number)
		{
		case 0:
			pos.y -= PLAYER_HEIGHT;
			CBullet::Create(pos, CBullet::BTYPE_REDBEAM);
			break;
		case 1:
			pos = m_apOption[0]->GetPos();
			pos.y -= OPTION_HEIGHT;
			CBullet::Create(pos, (CBullet::BTYPE_BLUEMSSILE));
			break;

		case 2:
			pos = m_apOption[1]->GetPos();
			pos.y -= OPTION_HEIGHT;
			CBullet::Create(pos, (CBullet::BTYPE_YELLOWDRILL));
			break;
		default:
			break;
		}
	}
	else if (bFusion == true)
	{//合体攻撃
		D3DXVECTOR3 pos = GetPos();
		pos.y -= SCREEN_HEIGHT/2;
		CBullet::Create(pos, CBullet::BTYPE_FUSIONSHOT);
		
	}
}

//=============================================================================
// 画面外の処理
//=============================================================================
void CPlayer::Offscreen()
{
	D3DXVECTOR3 pos = GetPos();
	if (pos.y > SCREEN_HEIGHT - PLAYER_HEIGHT / 2)
	{//始点(Y座標)が画面の下端に当たった
		pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2;
	}
	else if (pos.y < PLAYER_HEIGHT / 2)
	{//始点(Y座標)が画面の上端に当たった
		pos.y = PLAYER_HEIGHT / 2;
	}
	if (pos.x > SCREEN_WIDTH - PLAYER_WIDTH / 2)
	{//始点(X座標)が画面の右端に当たった
		pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
	}
	else if (pos.x < PLAYER_WIDTH / 2)
	{//始点(X座標)が画面の左端に当たった
		pos.x = PLAYER_WIDTH / 2;
	}
	SetPos(pos);

	//画面内に入ってからNORMALに戻す
	if (pos.x <= SCREEN_WIDTH + GetSiz().x / 2 &&
		pos.x >= -GetSiz().x / 2 &&
		pos.y <= SCREEN_HEIGHT + GetSiz().y / 2 &&
		pos.y >= -GetSiz().y / 2 &&
		m_state == PLAYERSTATE_APPEAR)
	{//画面内に入ったら
		m_state = PLAYERSTATE_NORMAL;
	}
}

//=============================================================================
// 合体の処理
//=============================================================================
void CPlayer::Fusion()
{
	if (m_nLife >= PLAYER_DEFAULTLIFE)
	{
		if (bFusion == true)
		{//合体解除
			Separation();
		}
		else if (bFusion == false && CSpecial::GetSpecial()>0.0f)
		{//合体
			PlaySound(SOUND_LABEL_SE_UNION);
			bFusion = true;
			BindTexture(m_apTexture[1]);	//テクスチャの設定
			for (int i = 0; i < MAX_OPTION; i++)
			{
				m_apOption[i]->Uninit();
			}
		}
	}
}

//=============================================================================
// 状態管理
//=============================================================================
void  CPlayer::StateManagement()
{
	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:
		//通常時のみ当たり判定の処理を行う
		Hit();
		break;

	case PLAYERSTATE_DAMAGE:
		nCnt++;
		if ((nCnt % 5) == 0)
		{
			fPtntitle = 1 - fPtntitle;
		}

		//ポリゴンをダメージ色に設定
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, fPtntitle));

		if (nCntState <= 0)
		{//無敵時間が解除されたとき

			fPtntitle = 0;
			nCnt = 0;

			m_state = PLAYERSTATE_NORMAL;

			//ポリゴンを通常色に設定
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	case PLAYERSTATE_DEATH:
		if (nCntState == NEXT_TIME-1)
		{//死んで最初の1fだけ通る
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 30; i++)
			{
				CEffect::Create(GetPos(),																		//位置
					D3DXVECTOR2(GetSiz().x, GetSiz().x),														//大きさ
					GetRot(),																					//向き
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//y
						0.0f),																			//z
					600,																						//寿命
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 1.0f));														//色
			}
			PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		}

		if (nCntState <= 0)
		{
			if (CFade::Get() == CFade::FADE_NONE)
			{
				CFade::Set(CApplication::MODE_RESULT);
				m_state = PLAYERSTATE_APPEAR;
			}
		}
		break;
	}
	
	nCntState--;
}

//=============================================================================
// ダメージ設定
//=============================================================================
void CPlayer::Damage()
{
	if (m_state == PLAYERSTATE_NORMAL&&m_nLife >= 1&&CGame::GetGame()!=CGame::GAME_END)
	{
		m_nLife--;
		CLife::LifeDecrease();
		m_state = PLAYERSTATE_DAMAGE;
		nCntState = 60;				//無敵時間

		if (m_nLife <= 0)
		{
			//爆発処理
			PlaySound(SOUND_LABEL_SE_EXPLOSION005);
			m_state = PLAYERSTATE_DEATH;
			CApplication::StopTime(60);
			nCntState = NEXT_TIME;				//フェードまでの時間
			CApplication::SlowTime(true);			//スローにする
		}
		else if (m_nLife <= 2)
		{
			if (bFusion == true)
			{//合体状態での被弾
				Separation();
			}
			for (int i = 0; i < 30; i++)
			{//オプション爆発
				CEffect::Create(m_apOption[m_nLife - 1]->GetPos(),												//位置
					m_apOption[m_nLife - 1]->GetSiz()*2.0f,														//大きさ
					GetRot(),																					//向き
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,			//y
						0.0f),																					//z
					600,																						//寿命
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 1.0f));														//色
			}
			m_apOption[m_nLife - 1]->Uninit();	//体力に応じて機体を破壊
			m_apOption[m_nLife - 1] = nullptr;
			PlaySound(SOUND_LABEL_SE_EXPLOSION002);
		}
		else if (m_nLife >= PLAYER_MAXLIFE)
		{//最大体力を超えた場合
			m_nLife = PLAYER_MAXLIFE;
		}
	}
}

//=============================================================================
// プレイヤーの分離
//=============================================================================
void CPlayer::Separation()
{
	PlaySound(SOUND_LABEL_SE_SEPARATION);
	bFusion = false;
	BindTexture(m_apTexture[0]);	//テクスチャの設定
	for (int i = 0; i < MAX_OPTION; i++)
	{
		m_apOption[i] = COption::Create(GetPos());
	}
}

//=============================================================================
// プレイヤーの状態取得
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState()
{
	return m_state;
}
