//================================================
//
//ステータス表示 [StatusUI.cpp]
//Author : Kishimoto Eiji
//
//================================================
#include "StatusUI.h"
#include "SkillGauge.h"
#include "texture.h"
#include "game.h"
#include "Player.h"
#include "ObjectList.h"

//======================================================
// 定数
//======================================================
const D3DXVECTOR3 CStatusUI::GAUGE_LOCAL_POS	(-10.0f,0.0f,0.0f);
const D3DXVECTOR2 CStatusUI::GAUGE_SIZE			(0.0f,0.0f);

const D3DXVECTOR3 CStatusUI::CHARACTER_BG_LOCAL_POS	(-40.0f,-30.0f,0.0f);
const D3DXVECTOR2 CStatusUI::CHARACTER_BG_SIZE		(80.0f, 80.0f);

const D3DXVECTOR3 CStatusUI::SKILL_ICON_BG_LOCAL_POS(0.0f, 0.0f, 0.0f);
const D3DXVECTOR2 CStatusUI::SKILL_ICON_BG_SIZE(45.0f, 45.0f);

const D3DXVECTOR3 CStatusUI::ITEM_ICON_LEFT_LOCAL_POS(35.0f, -30.0f, 0.0f);
const D3DXVECTOR3 CStatusUI::ITEM_ICON_ADD_POS(45.0f, 0.0f, 0.0f);
const D3DXVECTOR2 CStatusUI::ITEM_ICON_SIZE(40.0f, 40.0f);

//======================================================
//生成
//======================================================
CStatusUI *CStatusUI::Create(const D3DXVECTOR3& inPos,int nPlayerNum)
{
	CStatusUI* pStatusUI = new CStatusUI;	// 生成

	if (pStatusUI == nullptr)
	{//NULLチェック
		assert(false);
	}

	pStatusUI->SetPlayerNum(nPlayerNum);	// プレイヤー番号の設定
	pStatusUI->Init();	// 初期化
	pStatusUI->SetPos(inPos);

	return pStatusUI;
}

//======================================================
//コンストラクタ
//======================================================
CStatusUI::CStatusUI(int nPriority) :
	CObject(nPriority),
	m_pGauge(nullptr),
	m_pCharaBg(nullptr),
	m_pSkillIconBg(nullptr),
	m_nPlayerNum(0)
{
}

//======================================================
//デストラクタ
//======================================================
CStatusUI::~CStatusUI()
{
}

//======================================================
//初期化
//======================================================
HRESULT CStatusUI::Init()
{
	{
		m_pGaugeBg = CObject2D::Create(m_pos, D3DXVECTOR2(250.0f, 50.0f), CObjectList::EPriority::LEVEL_2D_UI);	//生成
		m_pGaugeBg->SetTextureKey("SKILL_GAUGE");
		m_pGaugeBg->SetCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}

	{//ゲージ
		//座標の算出(X:間隔に1つ分のゲージサイズを足している,Y:画面の下端に合わせている)
	
		//生成
		m_pGauge = CGauge::Create(m_pos, D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_nPlayerNum);

		switch (m_nPlayerNum)
		{//プレイヤー番号に応じたゲージの色を設定
		case 0:
			m_pGauge->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	//赤
			break;

		case 1:
			m_pGauge->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));	//青
			break;

		case 2:
			m_pGauge->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));	//黄
			break;

		case 3:
			m_pGauge->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	//緑
			break;

		default:
			break;
		}
	}

	{//キャラクター背景
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		m_pCharaBg = CObject2D::Create(pos, CHARACTER_BG_SIZE, CObjectList::EPriority::LEVEL_2D_UI);	//生成
		m_pCharaBg->SetTextureKey("CHARACTER_BG");					//テクスチャの設定
	}

	{//スキルアイコン背景
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		m_pSkillIconBg = CObject2D::Create(pos, SKILL_ICON_BG_SIZE, CObjectList::EPriority::LEVEL_2D_UI);	//生成
		m_pSkillIconBg->SetTextureKey("SKILL_ICON_BG");					//テクスチャの設定
	}

	{// アイテム
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < 3; i++)
		{
			m_pItemIcon[i] = CObject2D::Create(pos, ITEM_ICON_SIZE, CObjectList::EPriority::LEVEL_2D_UI);
			m_pItemIcon[i]->SetTextureKey("SKILL_ICON_BOMB");					// テクスチャの設定
			m_pItemIcon[i]->SetCol(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));
		}
	}

	return S_OK;
}

//======================================================
//終了
//======================================================
void CStatusUI::Uninit()
{
	//ゲージ
	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	//キャラクター背景
	if (m_pCharaBg != nullptr)
	{
		m_pCharaBg->Uninit();
		m_pCharaBg = nullptr;
	}

	//スキルアイコン背景
	if (m_pSkillIconBg != nullptr)
	{
		m_pSkillIconBg->Uninit();
		m_pSkillIconBg = nullptr;
	}
}

void CStatusUI::Update()
{
	CObject::Update();

	if (m_myPlayer != nullptr)
	{
		int stock = m_myPlayer->GetItemStock();

		for (int i = 0; i < 3; i++)
		{
			m_pItemIcon[i]->SetCol(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));
		}
		for (int i = 0; i < stock; i++)
		{
			m_pItemIcon[i]->SetCol(D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f));
		}
	}
}

//======================================================
// 位置設定
//======================================================
void CStatusUI::SetPos(const D3DXVECTOR3 & inPos)
{
	m_pos = inPos;
	m_pGauge->SetPos(m_pos + GAUGE_LOCAL_POS);					// スキルゲージ
	D3DXVECTOR3 pos = GAUGE_LOCAL_POS;
	pos.x += 250.0f * 0.5f;
	m_pGaugeBg->SetPos(m_pos + pos);
	m_pCharaBg->SetPos(m_pos + CHARACTER_BG_LOCAL_POS);			// キャラクター背景
	m_pSkillIconBg->SetPos(m_pos + SKILL_ICON_BG_LOCAL_POS);	// スキルアイコン背景

	for (int i = 0; i < 3; i++)
	{
		m_pItemIcon[i]->SetPos(m_pos + ITEM_ICON_LEFT_LOCAL_POS);
		m_pItemIcon[i]->AddPos(ITEM_ICON_ADD_POS * i);
	}
}

//======================================================
//プレイヤー番号の設定
//======================================================
void CStatusUI::SetPlayerNum(int nPlayerNum)
{
	m_nPlayerNum = nPlayerNum;
}