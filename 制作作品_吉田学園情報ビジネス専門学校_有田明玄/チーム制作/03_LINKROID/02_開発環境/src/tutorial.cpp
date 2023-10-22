//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include"main.h"
#include"tutorial.h"
#include"Application.h"
#include"input.h"
#include"Fade.h"
#include"Object3D.h"
#include"renderer.h"
#include"sound.h"
#include "camera.h"
#include "sky_bg.h"

#include "Block.h"
#include "Light.h"

//====================================
//コンストラクタ
//====================================
CTutorial::CTutorial()
{
}

//====================================
//デストラクタ
//====================================
CTutorial::~CTutorial()
{

}

//====================================
//初期化
//====================================
HRESULT CTutorial::Init()
{
	CSound::GetInstance()->Play(CSound::ELabel::LABEL_BGM_TITLE);

	m_camera = CCamera::Create();
	m_camera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_camera->SetPosV(D3DXVECTOR3(0.0f, 0.0f, -170.0f));

	m_count = 0;

	//ライトの設定
	m_light = new CLight;
	m_light->Init();

	//背景の生成
	{
		CSkyBg::Create();

		CObject3D* pori = CObject3D::Create(D3DXVECTOR3(0.0f, -250.0f, 0.0f), D3DXVECTOR3(4000.0f, 0.0f, 2000.0f), 2);
		pori->SetUV(0.0f, 20.0f, 0.0f, 20.0f);
		pori->SetTextureKey("TEST_FLOOR");
	}

	m_tutorialBg.push_back(CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1920.0f * 0.12f,0.0f, 1080.0f * 0.12f), 2));
	m_tutorialBg.push_back(CObject3D::Create(D3DXVECTOR3(250.0f, 0.0f, 0.0f), D3DXVECTOR3(1920.0f * 0.12f,0.0f, 1080.0f * 0.12f), 2));
	m_tutorialBg.push_back(CObject3D::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(1920.0f * 0.12f,0.0f, 1080.0f * 0.12f), 2));

	m_tutorialBg[0]->SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f,0.0f,0.0f));
	m_tutorialBg[1]->SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f,0.0f,0.0f));
	m_tutorialBg[2]->SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f,0.0f,0.0f));
	m_tutorialBg[0]->SetTextureKey("TUTORIAL0");
	m_tutorialBg[1]->SetTextureKey("TUTORIAL1");
	m_tutorialBg[2]->SetTextureKey("TUTORIAL2");

	return S_OK;
}

//====================================
//終了
//====================================
void CTutorial::Uninit()
{
	if (m_camera != nullptr)
	{
		m_camera->Uninit();
		delete m_camera;
		m_camera = nullptr;
	}

	if (m_light != nullptr)
	{
		m_light->Uninit();
		delete m_light;
		m_light = nullptr;
	}
}

//====================================
//更新
//====================================
void CTutorial::Update()
{

	if (m_count < 0)
	{
		m_count = 0;
	}

	if (m_count == 0)
	{
		if (m_camera->GetPosV().x - 0.0f > 0)
		{
			m_camera->AddPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
		}
		else
		{
			m_camera->AddPos(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
		}

		if (m_camera->GetPosV().x + 20.0f > 0.0f && m_camera->GetPosV().x - 20.0f < 0.0f)
		{
			m_camera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_camera->SetPosV(D3DXVECTOR3(0.0f, 0.0f, -170.0f));
			CInput* pInput = CInput::GetKey();
			if (CApplication::getInstance()->GetFade()->GetFade() == CFade::FADE_NONE)
			{
				if (pInput->Trigger(JOYPAD_LEFT) || pInput->Trigger(JOYPAD_B))	//左
				{
					m_count--;
				}
				else if (pInput->Trigger(JOYPAD_RIGHT) || pInput->Trigger(JOYPAD_A))	//右
				{
					m_count++;
				}
			}
		}
	}
	if (m_count == 1)
	{
		if (m_camera->GetPosV().x - 250.0f > 0)
		{
			m_camera->AddPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
		}
		else
		{
			m_camera->AddPos(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
		}

		if (m_camera->GetPosV().x + 20.0f > 250.0f && m_camera->GetPosV().x - 20.0f < 250.0f)
		{
			m_camera->SetPosR(D3DXVECTOR3(250.0f, 0.0f, 0.0f));
			m_camera->SetPosV(D3DXVECTOR3(250.0f, 0.0f, -170.0f));
			CInput* pInput = CInput::GetKey();
			if (CApplication::getInstance()->GetFade()->GetFade() == CFade::FADE_NONE)
			{
				if (pInput->Trigger(JOYPAD_LEFT) || pInput->Trigger(JOYPAD_B))	//左
				{
					m_count--;
				}
				else if (pInput->Trigger(JOYPAD_RIGHT) || pInput->Trigger(JOYPAD_A))	//右
				{
					m_count++;
				}
			}
		}
	}
	if (m_count == 2)
	{
		if (m_camera->GetPosV().x - 500.0f > 0)
		{
			m_camera->AddPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
		}
		else
		{
			m_camera->AddPos(D3DXVECTOR3(10.0f,0.0f,0.0f));
		}

		if (m_camera->GetPosV().x + 20.0f > 500.0f && m_camera->GetPosV().x - 20.0f < 500.0f)
		{
			m_camera->SetPosR(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
			m_camera->SetPosV(D3DXVECTOR3(500.0f, 0.0f, -170.0f));
			CInput* pInput = CInput::GetKey();
			if (CApplication::getInstance()->GetFade()->GetFade() == CFade::FADE_NONE)
			{
				if (pInput->Trigger(JOYPAD_LEFT) || pInput->Trigger(JOYPAD_B))	//左
				{
					m_count--;
				}
				else if (pInput->Trigger(JOYPAD_RIGHT) || pInput->Trigger(JOYPAD_A))	//右
				{
					m_count++;
				}
			}
		}
	}
	if (m_count >= 3)
	{
		CApplication::getInstance()->GetFade()->SetFade(CApplication::MODE_MAP);
	}
}

//====================================
//描画
//====================================
void CTutorial::Draw()
{
	m_camera->Set();
}
