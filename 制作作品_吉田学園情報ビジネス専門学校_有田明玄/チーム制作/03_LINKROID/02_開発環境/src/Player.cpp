//=============================================================================
// Content     (ゲームの設定)(player.cpp)
// Author     : 有田明玄
//=============================================================================

//-----------------------------------------------------------------------------
//インクルード
//-----------------------------------------------------------------------------
#include "Player.h"
#include "PlayerController.h"
#include "Application.h"
#include "sound.h"
#include "renderer.h"
#include "input.h"

#include "Item.h"
#include "Item_Bom.h"
#include "Bom.h"
#include "Shadow.h"
#include "Mesh.h"
#include "Game.h"
#include "Time.h"
#include "effect.h"
#include "Particle.h"
#include "Map.h"
#include "SkillGauge.h"
#include "SkillSelect.h"
#include "MapSelect.h"
#include "motion.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
const std::string CPlayer::MOTION_PATH = "data/TXT/Player001.txt";	// モーションデータパス
const int	CPlayer::MAX_STOCK = 3; 			// 持てるアイテムの最大数
const float CPlayer::PLAYER_SPEED = 1.5f; 		// 移動速度
const float CPlayer::ADD_SPEED = 1.5f;			// アイテムで加算するスピード
const float CPlayer::SKILL_BUFF_TIME = 60.0f;	// バフの効果時間
const int CPlayer::SKILL_WAVE_TIME = 30;		// スキルの発生時間
const float CPlayer::THROW_DISTANCE = 4.0f;		// 投擲距離
const float CPlayer::RUSH_SPEED = 4.5f;			// 突進速度

const CPlayer::SKILL_FUNC CPlayer::m_SkillFunc[] =
{
	UPDATE_FUNC_CAST(Skill_Idel),
	UPDATE_FUNC_CAST(Skill_Rush),
	UPDATE_FUNC_CAST(Skill_Speed),
	UPDATE_FUNC_CAST(Skill_Bom),
	UPDATE_FUNC_CAST(Skill_Wave),
};

//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
int CPlayer::m_nNumPlayer = 0;					// プレイヤーの数

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer(int nPriority) :
	CObject(nPriority),
	m_nStunTime(0),
	m_nStockItem(0),
	m_nItemBuffTime(0),
	m_nSkillBuffTime(0),
	m_fSkillGauge(0.0f),
	m_fSubGauge(0.0f)
{
	m_nPlayerNumber = m_nNumPlayer;
	m_nNumPlayer++;
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	m_nNumPlayer--;
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// モーションの読込み
	m_motion = new CMotion(MOTION_PATH.data());
	m_Motion = PM_NEUTRAL;	//ニュートラルモーションに変更
	m_motion->SetSizeMag(D3DXVECTOR3(0.9f,0.9f,0.9f));

	//モデルとモーションの読み込み
	m_apModel = m_motion->GetParts();

	for (int i = 0; i < (int)m_apModel.size(); i++)
	{
		//色指定
		switch (m_nPlayerNumber)
		{
		case 0:
			m_apModel[i]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		case 1:
			m_apModel[i]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		case 2:
			m_apModel[i]->SetCol(D3DXCOLOR(0.55f, 0.55f, 0.0f, 1.0f));
			break;
		case 3:
			m_apModel[i]->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
	}

	//初期化
	m_skill = (SKILL_STATE)(CSkillSelect::GetSelectSkill(m_nNumPlayer - 1));
	m_bKnockBack = false;
	m_bTeleport = false;
	m_bMaxGauge = false;
	m_bOperate = true;
	m_nSkillCT = 0;

	m_funcSkill = m_SkillFunc;
	SetSkill(SKILL_IDLE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	if (m_pShadow != nullptr)
	{
		m_pShadow = nullptr;
	}

	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	if (m_motion != nullptr)
	{
		m_motion->Uninit();
		delete m_motion;
		m_motion = nullptr;
	}

	CObject::Release();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{
	if (CApplication::getInstance()->GetModeState() == CApplication::MODE_RESULT)
	{//リザルト時モーションのみ再生
		m_motion->Update();
	}

	if (CApplication::getInstance()->GetModeState() != CApplication::MODE_GAME)
	{//ゲームじゃない場合return
		return;
	}
	
	if (!(CGame::GetGame() != CGame::GAME_END) && !(CGame::GetGame() != CGame::GAME_START))
	{//ゲーム中のみ動ける
		return;
	}

	/* ↓GAME状態の場合↓ */

	// 座標更新
	Updatepos();

	if (m_nStunTime > 0)
	{// スタンしていたらスタン時間を減算させる
		m_nStunTime--;
	}

	CObject::Update();

	Skill();

	Item();

	// モーション
	m_motion->Update();

	if (m_nStunTime <= 0 && m_bOperate)
	{
		m_nStunTime = 0;
		m_bKnockBack = false;

		// 移動
		Move();
	}

	// 角度の正規化
	Normalization();

	// ブロックとの当たり判定
	BlockCollision();

	// ブロックがない空間で停まる
	StopNoBlock();

	// ブロックの中心で曲がる
	TurnCenterBlock();

#ifdef _DEBUG
	CDebugProc::Print("Player：pos(%f,%f,%f)\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("Player：rot(%f,%f,%f)\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("Player：Motion : %d\n", (int)m_Motion);
	CDebugProc::Print("Player：State :%d\n", (int)m_skillStateNow);
	CDebugProc::Print("Player：Fream : %d\n", m_frame);
	CDebugProc::Print("Player：ItemStock : %d\n", m_nStockItem);
#endif // _DEBUG

}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用

	//現在のマテリアルを維持
	pDevice->GetMaterial(&matDef);

	//パーツのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//パーツのモデルの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//パーツのモデルの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < (int)m_apModel.size(); i++)
	{
		if (m_apModel[i]->GetParent() == nullptr)
		{
			m_apModel[i]->SetParentMatrix(&m_mtxWorld);
		}
	}
}

//-----------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer(CObject::OBJTYPE_MODEL);
	pPlayer->m_pos = pos;
	pPlayer->m_pos.y -= 10.0f;
	pPlayer->m_rot = rot;
	pPlayer->Init();

	return pPlayer;
}

//-----------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------
CPlayer * CPlayer::Create(CBlock* block, D3DXVECTOR3 rot)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer(CObject::OBJTYPE_MODEL);
	pPlayer->m_pos = block->GetPos();
	pPlayer->m_pos.y -= 10.0f;
	pPlayer->m_rot = rot;

	block->SetOnPlayer(pPlayer);
	pPlayer->m_pOnBlock = block;

	pPlayer->Init();

	return pPlayer;
}

//-----------------------------------------------------------------------------
// 移動
//-----------------------------------------------------------------------------
void CPlayer::Move()
{
	if (m_controller == nullptr)
	{
		return;
	}

	// 移動量
	D3DXVECTOR3 move = m_controller->Move();

	if (D3DXVec3Length(&move) == 0.0f)
	{
		return;
	}

	// 斜め入力があった場合
	if (move.z != 0.0f && move.x != 0.0)
	{
		if (m_moveVec.x != 0.0f)
		{ // X軸に進んでた場合
			move.z = 0.0f;
			move.x = 1.0f;
		}
		else if (m_moveVec.z != 0.0f)
		{ // Z軸に進んでた場合
			move.x = 0.0f;
			move.z = 1.0f;
		}
		else
		{ // 止まってた場合
			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	m_direction.x = move.x;
	m_direction.y = -move.z;

	D3DXVec2Normalize(&m_direction, &m_direction);

	//モーション再生
	if ((move.x != 0.0f || move.z != 0.0f) && m_Motion != PM_WALK)
	{
		m_Motion = PM_WALK;
		m_motion->SetNumMotion(m_Motion);
	}
	else if (move.x == 0.0f && move.z == 0.0f && m_Motion != PM_NEUTRAL)
	{
		m_Motion = PM_NEUTRAL;
		m_motion->SetNumMotion(m_Motion);
	}

	D3DXVec3Normalize(&m_movePlanVec, &move);	// 入力ベクトルを用意する
}

//-----------------------------------------------------------------------------
// 移動方向を見て曲がる
//-----------------------------------------------------------------------------
void CPlayer::TurnLookAtMoveing()
{
	if (m_direction.y < 0.0f)
	{
		SetRot(D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f));
	}
	else if (m_direction.y > 0.0f)
	{
		SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if (m_direction.x > 0.0f)
	{
		SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	}
	else if (m_direction.x < 0.0f)
	{
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	}
}

//-----------------------------------------------------------------------------
// ブロックがない場所で停まる
//-----------------------------------------------------------------------------
void CPlayer::StopNoBlock()
{
	D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
	D3DXVECTOR2 moveNowVec;

	moveNowVec.x = m_movePlanVec.x;
	moveNowVec.y = -m_movePlanVec.z;

	D3DXVec2Normalize(&moveNowVec, &moveNowVec);

	CDebugProc::Print("moveNowVec : %.1f,%.1f\n", moveNowVec.x, moveNowVec.y);

	BlockIdx += moveNowVec;

	CDebugProc::Print("Player：BlockIdx : %.1f,%.1f\n", BlockIdx.x, BlockIdx.y);

	CBlock* moveBlock = CGame::GetMap()->GetBlock((int)BlockIdx.x, (int)BlockIdx.y);	// 進行方向にあるブロック

	// 移動先予定のブロックが存在しない場合警告を出す
	assert(moveBlock != nullptr);

	if (moveBlock->IsStop())
	{
		m_movePlanVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 停止
	}
}

//-----------------------------------------------------------------------------
// ブロックの中心付近で曲がる
//-----------------------------------------------------------------------------
void CPlayer::TurnCenterBlock()
{
	bool XMin = m_pos.x <= m_pOnBlock->GetPos().x + (m_pOnBlock->GetSize().x * 0.05f);
	bool XMax = m_pos.x >= m_pOnBlock->GetPos().x - (m_pOnBlock->GetSize().x * 0.05f);
	bool ZMin = m_pos.z <= m_pOnBlock->GetPos().z + (m_pOnBlock->GetSize().z * 0.05f);
	bool ZMax = m_pos.z >= m_pOnBlock->GetPos().z - (m_pOnBlock->GetSize().z * 0.05f);

	// ブロック内に収まっているか
	if (XMin && XMax && ZMin && ZMax)
	{
		// 方向ベクトル掛ける移動量
		D3DXVec3Normalize(&m_movePlanVec, &m_movePlanVec);
		m_move = m_movePlanVec * PLAYER_SPEED;

		if (m_State == PST_SPEED || m_ItemState == ITEM_SPEED)
		{
			m_move *= ADD_SPEED;
		}

		if (m_bKnockBack)
		{
			//m_move *= 2.0f;
		}

		D3DXVec3Normalize(&m_moveVec, &m_move);

		// 回転
		TurnLookAtMoveing();

	}
}

//-----------------------------------------------------------------------------
// スキル処理
//-----------------------------------------------------------------------------
void CPlayer::Skill()
{
	if (m_controller == nullptr)
	{
		return;
	}

	//最大値を超えたら最大値にする
	if (m_fSkillGauge >= MAX_GAUGE)
	{
		m_fSkillGauge = MAX_GAUGE;
	}

	// スキル処理
	assert((m_skillStateNow >= 0) && (m_skillStateNow < SKILL_MAX));
	(this->*(m_funcSkill[m_skillStateNow]))();

	if (m_nSkillBuffTime > 0 || m_bMaxGauge)
	{//スキルの効果時間があったら
		m_fSkillGauge -= m_fSubGauge;
		m_bMaxGauge = false;
	}

	if (m_nSkillBuffTime <= 0 && m_State != PST_STAND)
	{// スキルを使った後に効果時間が切れたらデフォルトに戻す
		m_State = PST_STAND;
	}
}

//-----------------------------------------------------------------------------
// スキルが未使用の状態関数
//-----------------------------------------------------------------------------
void CPlayer::Skill_Idel()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_H))
	{
		SetSkill(SKILL_WAVE);
	}

	if (m_nSkillBuffTime > 0)
	{
		return;
	}

	//キー入力でスキルを発動する
	if (m_controller->Skill())
	{
		SetSkill(m_skill);

		switch (m_skill)
		{
		case CPlayer::SKILL_SPEED:
			SlowlySubGauge();
			break;

		case CPlayer::SKILL_BOM:
			SlowlySubGauge();
			break;

		case CPlayer::SKILL_WAVE:
			SubGauge();
			break;

		case CPlayer::SKILL_RUSH:
			SubGauge();
			break;

		default:
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// スピードアップスキル
//-----------------------------------------------------------------------------
void CPlayer::Skill_Speed()
{
	m_nSkillBuffTime--;
	if (m_nSkillBuffTime <= 0)
	{
		SetSkill(SKILL_IDLE);
		return;
	}
}

//-----------------------------------------------------------------------------
// 塗り範囲強化スキル
//-----------------------------------------------------------------------------
void CPlayer::Skill_Paint()
{
	m_nSkillBuffTime--;
	if (m_nSkillBuffTime <= 0)
	{
		SetSkill(SKILL_IDLE);
		return;
	}

	//3×3の範囲を塗る
	for (int nCntY = 0; nCntY < 3; nCntY++)
	{
		for (int nCntX = 0; nCntX < 3; nCntX++)
		{
			//乗っているブロックの番号を取得
			D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
			//範囲内のブロックを塗る
			BlockIdx = D3DXVECTOR2(BlockIdx.x - 1.0f, BlockIdx.y - 1.0f);			//左上に設定する
			D3DXVECTOR2 Idx = D3DXVECTOR2(BlockIdx.x + nCntX, BlockIdx.y + nCntY);
			CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);

			if (Block != nullptr)
			{//ブロックを塗る
				//Block->SetOnPlayer(this);	//プレイヤーの
				Block->SetPlayerNumber(m_nPlayerNumber);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// ノックバックスキル
//-----------------------------------------------------------------------------
void CPlayer::Skill_Knockback()
{
	m_nSkillBuffTime--;
	if (m_nSkillBuffTime <= 0)
	{
		SetSkill(SKILL_IDLE);
		return;
	}
}

//-----------------------------------------------------------------------------
// 爆弾攻撃スキル
//-----------------------------------------------------------------------------
void CPlayer::Skill_Bom()
{
	m_nSkillBuffTime--;
	if (m_nSkillBuffTime <= 0)
	{
		SetSkill(SKILL_IDLE);
		return;
	}

	if (m_nSkillCT > 0)
	{
		m_nSkillCT--;
	}

	if (m_controller == nullptr)
	{
		return;
	}

	if (m_nSkillCT <= 0)
	{// キー入力すると投げる
		//乗っているブロックの番号を取得
		D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);

		CBlock* Block = CGame::GetMap()->GetBlock((int)BlockIdx.x, (int)BlockIdx.y);
		if (Block != nullptr)
		{//ブロックを塗る
			Block->SetPlayerNumber(m_nPlayerNumber);
			CCreateBom::Create(Block, Block->GetPos(), m_nPlayerNumber, 120);
		}
		m_nSkillCT = 60;
	}
}

//-----------------------------------------------------------------------------
// 衝撃波スキル
//-----------------------------------------------------------------------------
void CPlayer::Skill_Wave()
{
	// 最初だけ通る
	if (m_nSkillTimer == 0)
	{
		m_nSkillTimer = SKILL_WAVE_TIME;
		m_Motion = PM_WAVE;
		m_motion->SetNumMotion(m_Motion);
		Stun(SKILL_WAVE_TIME - 1);

		//エフェクト生成
		D3DXCOLOR col;
		//色指定
		switch (m_nPlayerNumber)
		{
		case 0:
			col = (D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		case 1:
			col = (D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		case 2:
			col = (D3DXCOLOR(0.55f, 0.55f, 0.0f, 1.0f));
			break;
		case 3:
			col = (D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}
		CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), col, CParticle::PAR_CIRCLE);
	}

	m_nSkillTimer--;

	if (m_nSkillTimer <= 0)
	{
		m_Motion = PM_NEUTRAL;
		m_motion->SetNumMotion(m_Motion);
		m_nSkillTimer = 0;

		D3DXVECTOR2 range = { 0.0f,0.0f };	//攻撃範囲

		range.x = m_direction.x;
		range.y = m_direction.y;

		//範囲を塗る
		int maxI = 3;

		//乗っているブロックの番号を取得
		D3DXVECTOR2 NowBlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);

		for (int i = 0; i < maxI; i++)
		{
			int horizontal = i - (int)((maxI * 0.5f) + 0.5f);

			for (int nCntX = 0; nCntX < 5; nCntX++)
			{
				//範囲内のブロックを塗る
				D3DXVECTOR2 BlockIdx(NowBlockIdx.x + range.x + horizontal * range.y, NowBlockIdx.y + range.y + horizontal * range.x);			//中央左に設定する
				D3DXVECTOR2 Idx = D3DXVECTOR2(BlockIdx.x + nCntX * range.x, BlockIdx.y + nCntX * range.y);
				CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);

				if (Block != nullptr)
				{//ブロックを塗る
					Block->SetSink(-25.0f - 5.0f * nCntX);

					if (Block->GetOnPlayer() != nullptr)
					{
						Block->GetOnPlayer()->Stun(20);
					}

					Block->SetPlayerNumber(m_nPlayerNumber);
				}
			}
		}
		SetSkill(SKILL_IDLE);
	}
}

//-----------------------------------------------------------------------------
// 座標の更新
//-----------------------------------------------------------------------------
void CPlayer::Updatepos()
{
	m_posold = m_pos;	// 前回の位置の保存
	m_pos += m_move;	// 位置の更新
}

//-----------------------------------------------------------------------------
// 角度の正規化
//-----------------------------------------------------------------------------
void CPlayer::Normalization()
{
	//角度の正規化
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//-----------------------------------------------------------------------------
// ブロックとの判定
//-----------------------------------------------------------------------------
void CPlayer::BlockCollision()
{
	for (int i = 0; i < CGame::GetMap()->GetBlockCount(); i++)
	{
		CBlock* pBlock = CGame::GetMap()->GetBlock(i);

		if (pBlock == nullptr)
		{
			continue;
		}

		if (pBlock->IsMovePermit())
		{
			return;
		}

		bool XMin = m_pos.x <= pBlock->GetPos().x + (pBlock->GetSize().x * 0.5f);
		bool XMax = m_pos.x >= pBlock->GetPos().x - (pBlock->GetSize().x * 0.5f);
		bool ZMin = m_pos.z <= pBlock->GetPos().z + (pBlock->GetSize().z * 0.5f);
		bool ZMax = m_pos.z >= pBlock->GetPos().z - (pBlock->GetSize().z * 0.5f);

		if (XMin && XMax && ZMin && ZMax)
		{
			if (pBlock->GetNumber() != m_nPlayerNumber && m_fSkillGauge < MAX_GAUGE && m_skillStateNow == PST_STAND && m_skillStateNow != SKILL_RUSH)
			{//自分以外の色を塗り替えていたらゲージの加算(ゲージがマックスではなく、無強化の場合)
				m_fSkillGauge++;
			}

			if (m_pOnBlock != nullptr && pBlock != m_pOnBlock)
			{
				m_pOnBlock->SetOnPlayer(nullptr);
				m_pOnBlock->SetStop(false);
			}

			if (pBlock->GetOnPlayer() != this && pBlock->GetOnPlayer() != nullptr)
			{//乗ったブロックにすでにプレイヤーがいたら
				KnockBack(pBlock->GetOnPlayer(), this);
			}

			pBlock->SetOnPlayer(this);					//プレイヤーの
			pBlock->SetPlayerNumber(m_nPlayerNumber);	//プレイヤーの
			pBlock->SetSink(2.5f);						// ブロックを沈める
			pBlock->SetStop(true);						// その場所を侵入不可にする
			m_pOnBlock = pBlock;						//乗っているブロックを設定
		}
	}

	if (m_ItemState == ITEM_PAINT && m_pOnBlock != nullptr)
	{
		//横の範囲を塗る
		for (int nCntX = 0; nCntX < 3; nCntX++)
		{
			//乗っているブロックの番号を取得
			D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
			//範囲内のブロックを塗る
			BlockIdx = D3DXVECTOR2(BlockIdx.x - 1.0f, BlockIdx.y);			//中央左に設定する
			D3DXVECTOR2 Idx = D3DXVECTOR2(BlockIdx.x + nCntX, BlockIdx.y);
			CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);

			if (Block != nullptr)
			{
				Block->SetPlayerNumber(m_nPlayerNumber);
			}
		}
	}

	TakeItem();
}

//-----------------------------------------------------------------------------
// アイテムを拾う処理
//-----------------------------------------------------------------------------
void CPlayer::TakeItem()
{
	//乗っているブロックの情報を取得
	CBlock* Block = m_pOnBlock;

	if (Block != nullptr)
	{//アイテムの情報を取得する
		CItem *pItem = Block->GetOnItem();

		if (pItem != nullptr)
		{//アイテムを拾った場合
			m_nItemBuffTime = (int)CItem::BUFF_TIME;		//バフの効果時間を設定する

			if (pItem->GetEffect() == CItem::SPEED)
			{
				m_ItemState = ITEM_SPEED;
			}
			else if (pItem->GetEffect() == CItem::PAINT)
			{
				m_ItemState = ITEM_PAINT;
			}
			else if (pItem->GetEffect() == CItem::BOM && m_nStockItem < MAX_STOCK)
			{
				m_StockItemState = STOCK_BOM;
				m_nStockItem++;					//ストック数を増やす
			}

			//ブロックの上のアイテムを消去
			Block->DeleteItem();
		}
	}
}

//-----------------------------------------------------------------------------
// アイテム処理
//-----------------------------------------------------------------------------
void CPlayer::Item()
{
	if (m_controller == nullptr)
	{
		return;
	}

	if (m_nItemBuffTime > 0)
	{// アイテム強化効果の時間を減算する
		m_nItemBuffTime--;
	}

	if (m_nItemBuffTime <= 0 && m_ItemState != ITEM_NONE)
	{// アイテムを拾った後に効果時間が切れたらデフォルトに戻す
		m_ItemState = ITEM_NONE;
	}

	if (m_StockItemState == STOCK_BOM)
	{// 爆弾を持っているなら
		if (m_controller->Throw())
		{// キー入力すると投げる
			m_nStockItem--;			//ストック数を減らす
			
			//乗っているブロックの番号を取得
			D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
			D3DXVECTOR2 Idx(BlockIdx.x, BlockIdx.y);

			if (m_rot.y == D3DX_PI * 0.0f)
			{//下
				//2マス左に投げる
				Idx.y += THROW_DISTANCE;
			} 
			else if (m_rot.y == D3DX_PI * 1.0f)
			{//上
				//2マス左に投げる
				Idx.y -= THROW_DISTANCE;
			}
			else if (m_rot.y == D3DX_PI * 0.5f)
			{//左
				//2マス左に投げる
				Idx.x -= THROW_DISTANCE;
			}
			else if (m_rot.y == D3DX_PI * -0.5f)
			{//右
				//2マス右に投げる
				Idx.x += THROW_DISTANCE;
			}

			CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);
			if (Block != nullptr)
			{//ブロックを塗る
				Block->SetPlayerNumber(m_nPlayerNumber);
				CCreateBom::Create(Block, Block->GetPos(), m_nPlayerNumber, 120);
			}
		}
	}

	if (m_nStockItem <= 0)
	{//ストック数が0の時
		m_StockItemState = STOCK_NONE;		//何も持っていない状態にする
	}
}

//-----------------------------------------------------------------------------
// ブロックの情報を取得する処理
//-----------------------------------------------------------------------------
CBlock* CPlayer::OnBlock(float X, float Y)
{
	//乗っているブロックの番号を取得
	D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
	//自分の乗っている位置からXとY分加算した位置
	D3DXVECTOR2 Idx = D3DXVECTOR2(BlockIdx.x + X, BlockIdx.y + Y);

	return CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);
}

//-----------------------------------------------------------------------------
// ノックバック処理
//-----------------------------------------------------------------------------
void CPlayer::KnockBack(CPlayer *pFastPlayer, CPlayer *pLatePlayer)
{
	if (true)
	{
		return;
	}
	if (pLatePlayer->m_nStunTime != 0)
	{
		return;
	}

	D3DXVECTOR3 moveVec;
	D3DXVec3Normalize(&moveVec, &pLatePlayer->m_move);

	//最初にブロックにいたプレイヤーを後から来たプレイヤーの進行方向に飛ばす
	pFastPlayer->m_movePlanVec = moveVec;
	//後から来たプレイヤーを進行方向の逆に飛ばす
	pLatePlayer->m_movePlanVec = -moveVec;

	// 触れたプレイヤー同士にスタンを付与
	pLatePlayer->m_nStunTime = 12;
	pFastPlayer->m_nStunTime = 12;

	// ノックバック状態を取得
	pFastPlayer->m_bKnockBack = true;
	pLatePlayer->m_bKnockBack = true;
}

//-----------------------------------------------------------------------------
// コントローラーの設定
//-----------------------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}

//-----------------------------------------------------------------------------
// リザルト時のモーション再生
//-----------------------------------------------------------------------------
void CPlayer::SetResultMotion(int Rank)
{
	if (Rank == 0 && m_Motion != PM_WIN)
	{//一位の時
		m_Motion = PM_WIN;						// 勝利モーション再生
		m_motion->SetNumMotion(m_Motion);
	}
	else if (Rank != 0 && m_Motion != PM_LOSE)
	{//それ以外
		m_Motion = PM_LOSE;						// 敗北モーション再生
		m_motion->SetNumMotion(m_Motion);
	}
}

//-----------------------------------------------------------------------------
// スタン
//-----------------------------------------------------------------------------
void CPlayer::Stun(int inTime)
{
	m_nStunTime = inTime;
	m_Motion = PM_STAN;
	m_motion->SetNumMotion(m_Motion);
	m_movePlanVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// 徐々にゲージの減少
//-----------------------------------------------------------------------------
void CPlayer::SlowlySubGauge()
{
	//スキルの効果時間
	m_nSkillBuffTime = (int)(SKILL_BUFF_TIME) * 5;

	//スキルゲージの減少量を算出
	m_fSubGauge = (MAX_GAUGE / (float)m_nSkillBuffTime);
}

//-----------------------------------------------------------------------------
// 一気にゲージの減少
//-----------------------------------------------------------------------------
void CPlayer::SubGauge()
{
	//スキルゲージの減少量を算出
	m_fSubGauge = MAX_GAUGE;
	m_bMaxGauge = true;
}

//-----------------------------------------------------------------------------
// 突進
//-----------------------------------------------------------------------------
void CPlayer::Skill_Rush()
{
	// 移動キーを入力出来なくする
	m_bOperate = false;

	// 移動量
	D3DXVECTOR3 move = m_controller->Move();

	if (m_rot.y == D3DX_PI*0.0f)
	{//下
		move.z = -RUSH_SPEED;
	}
	else if (m_rot.y == D3DX_PI*1.0f)
	{//上
		move.z = RUSH_SPEED;
	}
	else if (m_rot.y == D3DX_PI*0.5f)
	{//左
		move.x = -RUSH_SPEED;
	}
	else if (m_rot.y == D3DX_PI*-0.5f)
	{//右
		move.x = RUSH_SPEED;
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//乗っているブロックの番号を取得
		D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
		D3DXVECTOR2 Idx;

		if (m_move.x != 0.0f)
		{
			//範囲内のブロックを塗る
			BlockIdx = D3DXVECTOR2(BlockIdx.x, BlockIdx.y - 1.0f);			//上に設定する
			Idx = D3DXVECTOR2(BlockIdx.x, BlockIdx.y + nCnt);
		}
		else if (m_move.z != 0.0f)
		{
			//範囲内のブロックを塗る
			BlockIdx = D3DXVECTOR2(BlockIdx.x - 1.0f, BlockIdx.y);			//左に設定する
			Idx = D3DXVECTOR2(BlockIdx.x + nCnt, BlockIdx.y);
		}
		CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);

		if (Block != nullptr)
		{
			Block->SetPlayerNumber(m_nPlayerNumber);
		}
	}

	// 乗っているブロックから進行方向のブロックを取得する
	D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
	D3DXVECTOR2 moveNowVec;

	moveNowVec.x = m_movePlanVec.x;
	moveNowVec.y = -m_movePlanVec.z;

	D3DXVec2Normalize(&moveNowVec, &moveNowVec);

	BlockIdx += moveNowVec;

	CBlock* moveBlock = CGame::GetMap()->GetBlock((int)BlockIdx.x, (int)BlockIdx.y);	// 進行方向にあるブロック

	// 移動先予定のブロックが存在しない場合警告を出す
	assert(moveBlock != nullptr);

	if (moveBlock->IsStop())
	{
		m_movePlanVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 停止

		// 操作可能にして突進をやめる
		m_bOperate = true;
		SetSkill(SKILL_IDLE);

		return;
	}
}