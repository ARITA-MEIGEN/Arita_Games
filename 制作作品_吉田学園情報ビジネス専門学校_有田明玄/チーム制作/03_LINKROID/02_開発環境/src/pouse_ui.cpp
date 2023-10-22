#include "pouse_ui.h"
#include "Object2D.h"
#include "ObjectList.h"
#include "Application.h"
#include "input.h"

//***************************
//定数の定義
//***************************
const D3DXVECTOR2 CPouseUI::BUTTON_SIZE = D3DXVECTOR2(500.0f, 150.0f);	//ボタンのサイズ

CPouseUI::CPouseUI()
{
}

CPouseUI::~CPouseUI()
{
}

HRESULT CPouseUI::Init()
{
	CObjectList::GetInstance()->Pause(true);

	m_bg = nullptr;
	m_backButton = nullptr;
	m_exitButton = nullptr;
	m_replayButton = nullptr;
	m_bottonIndex = 0;
	AttachActivityAtPouse();

	{
		m_bg = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), 6);
		m_bg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f));
		m_bg->AttachActivityAtPouse();
	}

	D3DXVECTOR3 buttonShiftPos(300.0f, 100.0f, 0.0f);

	{
		m_buttonBg = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f) + buttonShiftPos, D3DXVECTOR2(550.0f, 500.0f), 6);
		m_buttonBg->AttachActivityAtPouse();
	}
	{
		m_backButton = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.25f, 0.0f) + buttonShiftPos, BUTTON_SIZE, 6);
		m_backButton->SetTextureKey("TEXT_BACK");
		m_backButton->AttachActivityAtPouse();
	}
	{
		m_exitButton = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f) + buttonShiftPos, BUTTON_SIZE, 6);
		m_exitButton->SetTextureKey("TEXT_TITLE");
		m_exitButton->AttachActivityAtPouse();
	}
	{
		m_replayButton = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.75f, 0.0f) + buttonShiftPos, BUTTON_SIZE, 6);
		m_replayButton->SetTextureKey("TEXT_RETRY");
		m_replayButton->AttachActivityAtPouse();
	}
	return E_NOTIMPL;
}

void CPouseUI::Uninit()
{
	CObject::Release();

	m_bg->Uninit();
	m_buttonBg->Uninit();
	m_exitButton->Uninit();
	m_backButton->Uninit();
	m_replayButton->Uninit();
	CObjectList::GetInstance()->Pause(false);
}

void CPouseUI::Update()
{
	// 選択してない項目のα値を下げる。
	switch (m_bottonIndex)
	{
	case 0:
		m_backButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_exitButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		m_replayButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		break;
	case 1:
		m_backButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		m_exitButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_replayButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		break;
	case 2:
		m_backButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		m_exitButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		m_replayButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
}

CPouseUI * CPouseUI::Create()
{
	CPouseUI* ui = new CPouseUI;

	assert(ui != nullptr);

	ui->Init();

	return ui;
}

void CPouseUI::NextBotton()
{
	m_bottonIndex++;

	if (m_bottonIndex > 2)
	{
		m_bottonIndex = 0;
	}
}

void CPouseUI::BackBotton()
{
	m_bottonIndex--;

	if (m_bottonIndex < 0)
	{
		m_bottonIndex = 2;
	}
}

// 出る
int CPouseUI::Exit()
{
	Uninit();
	return m_bottonIndex;
}
