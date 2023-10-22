#include "Bullet.h"
#include"Application.h"
#include"renderer.h"
#include"Explosion.h"
#include"Enemy.h"
#include"Effect.h"
#include"Easing.h"
#include"Player.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[BULLET_TEX] = {};
bool CBullet::m_bUse = false;			//撃ってるかどうか
D3DXVECTOR3 CBullet::m_playerpos;	//プレイヤーの位置
//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet() :CObject2D(OBJTYPE_BULLET)
{
	SetObjType(OBJTYPE_BULLET);
	m_eType = BTYPE_INVALID;
	m_frame = 0;
	m_bEnemy = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
	SetObjType(OBJTYPE_INVALID);
	m_eType = BTYPE_INVALID;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CBullet::Init(float Width, float Height)
{
 	CObject2D::Init(Width,  Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CBullet::Uninit()
{
 	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CBullet::Update()
{
	//位置を更新
	CObject2D::Update();

	//移動量の更新
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;

	//当たり判定の処理
	if (Hit() == S_FALSE)
	{//ヒットしなかった場合
		if (m_eType == BTYPE_BLUEMSSILE)
		{//2号機の弾だけ追尾する
			SetHorming();
			//CEffect::Create(Pos, GetSiz(), GetRot());
		}
		SetPos(Pos);
	}
	else
	{//弾が相手に当たった場合
		//弾を消す
		switch (m_eType)
		{
		case CBullet::BTYPE_REDBEAM:
			break;
		case CBullet::BTYPE_BLUEMSSILE:
			PlaySound(SOUND_LABEL_SE_EXPLOSION004);
			break;
		case CBullet::BTYPE_YELLOWDRILL:
			break;
		case CBullet::BTYPE_FUSIONSHOT:
			break;
		default:
			break;
		}
		Uninit();
		return;
	}

	if (m_eType == BTYPE_FUSIONSHOT)
	{//ビームの処理
		FusionBeam();
	}

	if (m_bUse == false && m_eType == BTYPE_FUSIONSHOT)
	{//ビームを使用してない場合消去
		Uninit();
		return;
	}

	Offscreen();	//画面外の処理
	m_NextHItTime--;
	m_frame++;
}

//=============================================================================
// 描画
//=============================================================================
void  CBullet::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	if (m_eType != (BTYPE_REDBEAM, BTYPE_BLUEMSSILE, BTYPE_YELLOWDRILL, BTYPE_FUSIONSHOT))
	{
		//アルファブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	CObject2D::Draw();

	if (m_eType != BTYPE_REDBEAM || m_eType != BTYPE_BLUEMSSILE || m_eType != BTYPE_YELLOWDRILL || m_eType != BTYPE_FUSIONSHOT)
	{
		//通常に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CBullet::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_REDBEAM.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_BLUEMISSILE.png",
		&m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOWDRILL.png",
		&m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\FUSIONBEAM_001.png",
		&m_apTexture[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnemyBullet.png",
		&m_apTexture[4]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CBullet::Unload()
{
	for (int i = 0; i < BULLET_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// バレット生成
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, EBULLETTYPE type)
{
	CBullet*pBullet = nullptr;
	pBullet = new CBullet;
	//速度設定
	pBullet->SetPos(pos);			//位置設定
	pBullet->m_eType = type;
	pBullet->m_HitCount = DEFAULT_HIT;
	switch (pBullet->m_eType)
	{
	case CBullet::BTYPE_REDBEAM:
		pBullet->Init(BULLET_WIDTH_RED, BULLET_HEIGHT_RED);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[0]);	//テクスチャの設定
		break;

	case CBullet::BTYPE_BLUEMSSILE:
		pBullet->Init(BULLET_WIDTH_BLUE, BULLET_HEIGHT_BLUE);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -BLUE_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[1]);	//テクスチャの設定
		pBullet->Lockon();
		break;

	case CBullet::BTYPE_YELLOWDRILL:
		pBullet->Init(BULLET_WIDTH_YELLOW, BULLET_HEIGHT_YELLOW);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -YELLOW_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[2]);	//テクスチャの設定
		pBullet->m_HitCount = YELLOW_HIT;
		break;
	case CBullet::BTYPE_FUSIONSHOT:
		pBullet->Init(BEAM_WIDTH, SCREEN_HEIGHT);
		pBullet->m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[3]);	//テクスチャの設定
		break;

	case ENEMY_BULLET:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		pBullet->Lockon();
		break;

	case ENEMY_CANNON01:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_CANNON02:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_CANNON03:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;

		break;
	case ENEMY_CANNON04:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON06:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON07:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON08:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON09:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//テクスチャの設定
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_BEAMCANNON:
		pBullet->Init(BEAM_WIDTH, 200.0f);
		pBullet->m_Move = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pBullet->BindTexture(m_apTexture[3]);	//テクスチャの設定
		pBullet->m_bEnemy = true;
		
		break;

	default:
		break;
	}

	return pBullet;
}

//=============================================================================
//当たり判定関連
//=============================================================================
HRESULT CBullet::Hit()
{
	if (m_bEnemy==false)
	{//プレイヤーの弾
		for (int i = 0; i < MAX_TYPE; i++)
		{
			for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
			{
				CObject*pObject;
				pObject = CObject::GetObj(nCnt, i);
				if (pObject != nullptr)
				{
					CObject::EObjType objType;
					objType = pObject->GetObjType(nCnt, i);			//種類の取得

					D3DXVECTOR3 BulletPos = CObject2D::GetPos();
					D3DXVECTOR2 BulletSiz = CObject2D::GetSiz();	//相手のサイズを取得

					if (objType == OBJTYPE_ENEMY)					//敵かどうか判定なおかつ非合体時
					{//敵に攻撃
						CEnemy *pEnemy = (CEnemy*)pObject;
						D3DXVECTOR3 EnemyPos = pEnemy->GetPos();	//相手の位置情報取得
						D3DXVECTOR2 EnemySiz = pEnemy->GetSiz();	//相手のサイズを取得
						if (pEnemy->GetMovePtn() != CEnemy::MOVE_BOSS_BASE &&
							CObject2D::Hit(BulletPos, EnemyPos, BulletSiz, EnemySiz) == true &&
							pEnemy->GetState() != CEnemy::ENEMYSTATE_DEATH)	//当たり判定の処理！
						{
							m_HitCount--;
							//ダメージ処理
							switch (m_eType)
							{
							case CBullet::BTYPE_REDBEAM:
								pEnemy->Damage(RED_DAMAGE);
								break;

							case CBullet::BTYPE_BLUEMSSILE:
								pEnemy->Damage(BLUE_DAMAGE);
								break;

							case CBullet::BTYPE_YELLOWDRILL:
								pEnemy->Damage(YELLOW_DAMAGE);
								break;

							case CBullet::BTYPE_FUSIONSHOT:
								pEnemy->Damage(FUSION_DAMAGE);
								break;
							default:
								break;
							}
							if (m_eType != BTYPE_FUSIONSHOT&&m_HitCount<=0)
							{//ビーム以外は弾を消す
								return	S_OK;
							}
							else if (m_HitCount>0)
							{//当たり判定が復活するまでの時間
								m_NextHItTime = DEFAULT_NEXTHIT;
							}
						}
					}
					else if (objType == OBJTYPE_BULLET)
					{//ビームが弾に当たった時
						CBullet *pBullet = (CBullet*)pObject;
						D3DXVECTOR3 pBulletPos = pBullet->GetPos();	//敵の弾の位置情報取得
						D3DXVECTOR2 pBulletSiz = pBullet->GetSiz();	//敵の弾のサイズを取得
						if (CObject2D::Hit(BulletPos,pBulletPos, BulletSiz, pBulletSiz) == true &&
							pBullet->m_bEnemy == true)	//当たり判定の処理！
						{//敵の弾がビームに当たった場合消す
							m_HitCount--;
							if (m_NextHItTime<=0&&m_HitCount <= 0 && m_eType == BTYPE_FUSIONSHOT&&pBullet->m_eType != ENEMY_BEAMCANNON)
							{//敵の主砲以外は消せるようにする
								pBullet->Uninit();
								PlaySound(SOUND_LABEL_SE_DELETEBULLET);
							}
							else if (m_HitCount>0)
							{//当たり判定が復活するまでの時間
								m_NextHItTime = DEFAULT_NEXTHIT;
							}
						}
					}
				}
			}
		}
	}
	else
	{//敵の弾
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_PLAYER);
			if (pObject != nullptr)
			{
				CObject::EObjType objType;
				objType = pObject->GetObjType(nCnt, OBJTYPE_PLAYER);		//種類の取得

				D3DXVECTOR3 BulletPos = CObject2D::GetPos();
				D3DXVECTOR2 BulletSiz = CObject2D::GetSiz();				//相手のサイズを取得
					
				if (objType == OBJTYPE_PLAYER)
				{//プレイヤーの場合
					CPlayer *pPlayer = (CPlayer*)pObject;
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();				//相手の位置情報取得
					D3DXVECTOR2 PlayerSiz = pPlayer->GetSiz();				//相手のサイズを取得
					if (CObject2D::Hit(BulletPos, PlayerPos, BulletSiz/2, PlayerSiz) == true && pPlayer->GetState() == CPlayer::PLAYERSTATE_NORMAL)	//当たり判定の処理！
					{
						//ダメージ処理
						pPlayer->Damage();
					}
				}
			}
		}
	}
	return S_FALSE;
}

//=============================================================================
//ホーミング弾のターゲット設定
//=============================================================================
void CBullet::Lockon()
{
	float fRotMove, fRotDest, fRotDiff, fTgMove = 0.0f, fTgDest = 0.0f, fTgDiff = 0.0f;	//計算・比較用
	float TgLength = 1000.0f;	//適当な数値をぶっこんだ

	if (m_bEnemy == true)
	{//敵の弾
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_PLAYER);
			if (pObject != nullptr)
			{//使用中かどうか判定
				D3DXVECTOR3 BulletPos = CObject2D::GetPos();						//弾の座標を取得
				CPlayer *pPlayer = (CPlayer*)pObject;
				fRotMove = atan2f(m_Move.x, m_Move.y);							//現在の移動方向(角度)
																				//目的の移動方向(角度)	相手の座標から自分を引くかんじ
				fRotDest = atan2f(pPlayer->GetPos().x - BulletPos.x, pPlayer->GetPos().y - BulletPos.y);
				fRotDiff = fRotDest - fRotMove;									//目的の移動方向までの差分
				D3DXVECTOR3 fDiff = pPlayer->GetPos() - BulletPos;
				float fLength = D3DXVec3Length(&fDiff);							//距離
				if (fLength <= TgLength)
				{
					//ターゲットの情報を代入
					TgLength = fLength;
					fTgMove = fRotMove;
					fTgDest = fRotDest;
					fTgDiff = fRotDiff;
					m_Target = nCnt;
				}
			}
		}
		if (TgLength < 1000.0f)
		{//射程距離内に敵がいる場合
			if (fTgDiff > D3DX_PI)
			{
				fTgDiff -= D3DX_PI * 2;
			}
			else if (fTgDiff < -D3DX_PI)
			{
				fTgDiff += D3DX_PI * 2;
			}

			fTgMove += fTgDiff*1.0f;	//移動方向(角度)の補正

			if (fTgMove > D3DX_PI)
			{
				fTgMove -= D3DX_PI * 2;
			}
			else if (fTgMove < -D3DX_PI)
			{
				fTgMove += D3DX_PI * 2;
			}

			SetRot(fTgMove + D3DX_PI);	//角度をターゲットに向ける

			m_Move.x = sinf(fTgMove)*ENEMY_SPEED;
			m_Move.y = cosf(fTgMove)*ENEMY_SPEED;
		}
	}
	else
	{//プレイヤーの弾
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_ENEMY);
			if (pObject != nullptr)
			{//使用中かどうか判定
				D3DXVECTOR3 BulletPos = CObject2D::GetPos();						//弾の座標を取得
				if (pObject->GetObjType(nCnt, OBJTYPE_ENEMY) == OBJTYPE_ENEMY)		//敵かどうか判定
				{
					CEnemy *pEnemy = (CEnemy*)pObject;
					if (pEnemy->GetState() != (CEnemy::ENEMYSTATE_APPEAR, CEnemy::ENEMYSTATE_DEATH))
					{
						fRotMove = atan2f(m_Move.x, m_Move.y);							//現在の移動方向(角度)
																						//目的の移動方向(角度)	相手の座標から自分を引くかんじ
						fRotDest = atan2f(pEnemy->GetPos().x - BulletPos.x, pEnemy->GetPos().y - BulletPos.y);
						fRotDiff = fRotDest - fRotMove;									//目的の移動方向までの差分
						D3DXVECTOR3 fDiff = pEnemy->GetPos() - BulletPos;
						float fLength = D3DXVec3Length(&fDiff);							//距離
						if (fLength <= TgLength)
						{
							//ターゲットの情報を代入
							TgLength = fLength;
							fTgMove = fRotMove;
							fTgDest = fRotDest;
							fTgDiff = fRotDiff;
							m_Target = nCnt;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
//ホーミング弾の設定処理
//=============================================================================
void CBullet::SetHorming()
{//ホーミングの設定

	float fRotMove, fRotDest, fRotDiff, fTgMove = 0.0f, fTgDest = 0.0f, fTgDiff = 0.0f;	//計算・比較用
	float TgLength = 1000.0f;	//適当な数値をぶっこんだ

	CObject*pObject;
	pObject = CObject::GetObj(m_Target, OBJTYPE_ENEMY);
	if (pObject != nullptr)
	{//使用中かどうか判定
		D3DXVECTOR3 BulletPos = CObject2D::GetPos();												//弾の座標を取得
		if (pObject->GetObjType(m_Target, OBJTYPE_ENEMY) == OBJTYPE_ENEMY)							//ロックオンした敵かどうか判定
		{
			CEnemy *pEnemy = (CEnemy*)pObject;
			CEnemy::ENEMYSTATE Estate = pEnemy->GetState();
			if (Estate == CEnemy::ENEMYSTATE_NORMAL || Estate == CEnemy::ENEMYSTATE_DAMAGE)
			{
				fRotMove = atan2f(m_Move.x, m_Move.y);													//現在の移動方向(角度)
				//目的の移動方向(角度)	相手の座標から自分を引くかんじ
				fRotDest = atan2f(pEnemy->GetPos().x - BulletPos.x, pEnemy->GetPos().y - BulletPos.y);
				fRotDiff = fRotDest - fRotMove;															//目的の移動方向までの差分
				D3DXVECTOR3 fDiff = pEnemy->GetPos() - BulletPos;
				float fLength = D3DXVec3Length(&fDiff);				//距離
				if (fLength <= TgLength)
				{
					//ターゲットの情報を代入
					TgLength = fLength;
					fTgMove = fRotMove;
					fTgDest = fRotDest;
					fTgDiff = fRotDiff;
				}
			}
		}
	}
	if (TgLength < 1000.0f)
	{//射程距離内に敵がいる場合
		if (fTgDiff > D3DX_PI)
		{
			fTgDiff -= D3DX_PI * 2;
		}
		else if (fTgDiff < -D3DX_PI)
		{
			fTgDiff += D3DX_PI * 2;
		}

		fTgMove += fTgDiff*0.8f;	//移動方向(角度)の補正

		if (fTgMove > D3DX_PI)
		{
			fTgMove -= D3DX_PI * 2;
		}
		else if (fTgMove < -D3DX_PI)
		{
			fTgMove += D3DX_PI * 2;
		}

		SetRot(fTgMove + D3DX_PI);	//角度をターゲットに向ける

		m_Move.x = sinf(fTgMove)*BLUE_SPEED;
		m_Move.y = cosf(fTgMove)*BLUE_SPEED;
	}
}

//=============================================================================
// 画面外の処理
//=============================================================================
void CBullet::Offscreen()
{
	D3DXVECTOR3 pos = GetPos();
	if (m_eType!= BTYPE_FUSIONSHOT&&( pos.y > SCREEN_HEIGHT + GetSiz().y / 2|| pos.y < -GetSiz().y / 2|| pos.x > SCREEN_WIDTH + GetSiz().x / 2|| pos.x <  -GetSiz().x / 2))
	{//始点(Y座標)が画面の下端に当たった
		Uninit();
		return;
	}
}

//=============================================================================
//ビームの使用状態
//=============================================================================
void CBullet::SetBeam(bool use)
{
	m_bUse = use;
}

//=============================================================================
//ビームの設定
//=============================================================================
void CBullet::FusionBeam()
{
	SetUV(GetUV(0).x, GetUV(1).x, GetUV(0).y - 0.1f, GetUV(1).y - 0.1f);

	m_playerpos.y -=SCREEN_HEIGHT / 2;
	SetPos(m_playerpos);
}

//=============================================================================
//プレイヤーの移動量を渡す用
//=============================================================================
 void CBullet::GetPlayerPos(D3DXVECTOR3 pos)
{
	 m_playerpos = pos;
}


