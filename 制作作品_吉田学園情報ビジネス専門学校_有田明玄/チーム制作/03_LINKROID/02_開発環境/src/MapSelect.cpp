//=============================================================================
//
// マップ選択
// Author : 髙野馨將
//
//=============================================================================

//インクルード
#include"main.h"
#include"MapSelect.h"
#include"input.h"
#include"Fade.h"
#include"Application.h"
#include"renderer.h"
#include"sound.h"
#include"Map.h"
#include"Game.h"
#include"Player.h"
#include"CameraGame.h"
#include"Light.h"
#include"Object3D.h"

//====================================
// 定数
//====================================
int CMapSelect::m_nMapNumber = 0;

//====================================
//コンストラクタ
//====================================
CMapSelect::CMapSelect()
{
}

//====================================
//デストラクタ
//====================================
CMapSelect::~CMapSelect()
{
}

//====================================
//初期化
//====================================
HRESULT CMapSelect::Init()
{
	CSound::GetInstance()->Play(CSound::ELabel::LABEL_BGM_TITLE);

	//初期化
	m_bMapChange = false;

	//初期化
	for (int nCnt = 0; nCnt < CMap::STAGE_MAX; nCnt++)
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH * 0.5f + (100.0f * nCnt) - (100.0f * CMap::STAGE_MAX * 0.5f), 600.0f, 0.0f);
		m_pObj2DPolygon[nCnt] = CObject2D::Create(pos, D3DXVECTOR2(75.0f, 75.0f), 6);
		CObject2D* main = CObject2D::Create(pos, D3DXVECTOR2(60.0f, 60.0f), 6);
		main->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//カメラの設定
	m_pCamera = CCameraGame::Create();

	//ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();

	//背景
	CObject3D* pori = CObject3D::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(4000.0f, 0.0f, 2000.0f), 2);
	pori->SetUV(0.0f,20.0f,0.0f,20.0f);
	pori->SetTextureKey("TEST_FLOOR");

	//マップ生成
	m_pMap = CMap::Create(m_nMapNumber);

	return S_OK;
}

//====================================
//終了
//====================================
void CMapSelect::Uninit()
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

	//マップの終了
	if (m_pMap != nullptr)
	{
		delete m_pMap;
	}
}

//====================================
//更新
//====================================
void CMapSelect::Update()
{
	//更新処理
	m_pCamera->Update();
	m_pLight->Update();

	//入力処理
	Input();

	if (m_bMapChange)
	{
		//選択処理
		Select();
	}

	for (int nCnt = 0; nCnt < CMap::STAGE_MAX; nCnt++)
	{//今選択してるマップと同じ番号のポリゴンを白くする
		if (nCnt == m_nMapNumber)
		{
			m_pObj2DPolygon[nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_pObj2DPolygon[nCnt]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		}
	}
}

//====================================
//描画
//====================================
void CMapSelect::Draw()
{
	m_pCamera->Set();
}

//====================================
//入力
//====================================
void CMapSelect::Input()
{
	//インプットの情報を取得
	CInput* pInput = CInput::GetKey();

	//フェードしていなければ
	if (CApplication::getInstance()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//左入力で左を選択
		if (m_nMapNumber >= (CMap::STAGE_01 + 1))
		{//左端ではないなら左へ
			if (pInput->Trigger(JOYPAD_LEFT) || pInput->Trigger(DIK_O))
			{
				m_nMapNumber--;
				m_bMapChange = true;
			}
		}

		//右入力で右を選択
		if (m_nMapNumber <= (CMap::STAGE_MAX - 2))
		{//右端ではないなら右へ
			if (pInput->Trigger(JOYPAD_RIGHT) || pInput->Trigger(DIK_P))
			{
				m_nMapNumber++;
				m_bMapChange = true;
			}
		}

		if ((pInput->Trigger(DIK_RETURN)) || (pInput->Trigger(JOYPAD_B)))		//ENTERキー
		{//エンターでスキル選択に
		 //モード設定
			CApplication::getInstance()->GetFade()->SetFade(CApplication::MODE_SKILL);
		}
	}
}

//====================================
//選択
//====================================
void CMapSelect::Select()
{
	//マップの終了
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = nullptr;
	}
	//表示されているマップを変える
	m_pMap = CMap::Create(m_nMapNumber);

	//マップの変更を止める
	m_bMapChange = false;
}