//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include"main.h"
#include"Result.h"
#include"input.h"
#include"Fade.h"
#include"Application.h"
#include"renderer.h"
#include"sound.h"
#include"Map.h"
#include"Player.h"
#include"CameraResult.h"
#include"Light.h"
#include"Object3D.h"
#include"sky_bg.h"

//-----------------------------------------------------------------------------
//静的変数宣言
//-----------------------------------------------------------------------------
const float CResult::RANK_WIDTH = 200.0f;		// ランキングの設置間隔
const float CResult::PLAYER_WIDTH = 120.0f;		// プレイヤーの設置間隔
const float CResult::TOP_HEIGHT = 350.0f;			// 1位の高さ
const float CResult::PLAYER_HEIGHT = 70.0f;	//  プレイヤー間の順位ごとの高さの間隔
const float CResult::RANK_HEIGHT= 110.0f;		// ランキングのUIの設置間隔

//====================================
//コンストラクタ
//====================================
CResult::CResult()
{
}

//====================================
//デストラクタ
//====================================
CResult::~CResult()
{

}

//====================================
//初期化
//====================================
HRESULT CResult::Init()
{
	CSound::GetInstance()->Play(CSound::ELabel::LABEL_BGM_TITLE);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();
	//テクスチャの読み込み
	std::string textureKey[4];
	textureKey[0] = "RESULET_000";
	textureKey[1] = "RESULET_001";
	textureKey[2] = "RESULET_002";
	textureKey[3] = "RESULET_003";


	//カメラの設定
	m_pCamera = CCameraResult::Create();

	//ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();


	//背景の生成
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//ランキング
		m_apRank[i] = new CObject2D(CObject::OBJTYPE_UI);
		m_apRank[i]->Init();
		m_apRank[i]->SetSiz(D3DXVECTOR2((float)100, (float)50));
		m_apRank[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	
		//プレイヤー生成
		m_pPlayer[i] = CPlayer::Create({ -(PLAYER_WIDTH*1.5f) + (PLAYER_WIDTH * i),0.0f,0.0f }, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//土台生成
		m_pCylinder[i]= CObjectX::Create();
		m_pCylinder[i]->BindModel(CObjectXOriginalList::GetInstance()->Load("ENTYU", "data/MODEL/entyu000.x"));
		m_pCylinder[i]->SetPos(D3DXVECTOR3{m_pPlayer[i]->GetPos().x,m_pPlayer[i]->GetPos().y - 1500.0f,m_pPlayer[i]->GetPos().z });
	}

	//背景の生成
	{
		CSkyBg::Create();

		CObject3D* pori = CObject3D::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(4000.0f, 0.0f, 2000.0f), 2);
		pori->SetUV(0.0f, 20.0f, 0.0f, 20.0f);
		pori->SetTextureKey("TEST_FLOOR");
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{//プレイヤーの番号から順位を獲得
		m_apRank[i]->SetTextureKey(textureKey[CMap::GetRanking(i)]);
	}

	return S_OK;
}

//====================================
//終了
//====================================
void CResult::Uninit()
{
	CSound::GetInstance()->Stop();
	//カメラの設定
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
	}

	//ライトの設定
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
	}
}

//====================================
//更新
//====================================
void CResult::Update()
{
	CInput* pInput = CInput::GetKey();

	m_pCamera->Update();
	m_pLight->Update();

	if (CApplication::getInstance()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if ((pInput->Trigger(DIK_RETURN)) == true || (pInput->Trigger(JOYPAD_B)))		//ENTERキー
		{//エンターでランキングに
		 //モード設定
			CApplication::getInstance()->GetFade()->SetFade(CApplication::MODE_TITLE);
		}
	}
	ResultCamera();
}

//====================================
//描画
//====================================
void CResult::Draw()
{
	m_pCamera->Set();
}

//====================================
//リザルトカメラ
//====================================
void CResult::ResultCamera()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (m_pPlayer[i]->GetPos().y < TOP_HEIGHT - CMap::GetRanking(i) * PLAYER_HEIGHT)//高さ
		{//プレイヤーを上に移動
			m_pCylinder[i]->SetPos(D3DXVECTOR3{ m_pCylinder[i]->GetPos().x, m_pCylinder[i]->GetPos().y + 1.0f , m_pCylinder[i]->GetPos().z });
			m_pPlayer[i]->SetPos({ m_pPlayer[i]->GetPos().x,  m_pCylinder[i]->GetPos().y + m_pCylinder[i]->GetSize().y ,m_pPlayer[i]->GetPos().z });
		}
		
		else
		{//順位表示
			m_apRank[i]->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH / 2 - (RANK_WIDTH * 1.5f) + RANK_WIDTH * i, 110.0f + CMap::GetRanking(i) * RANK_HEIGHT, 0.0f));
			m_apRank[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			
			m_pPlayer[i]->SetResultMotion(CMap::GetRanking(i));
		}
	}
}