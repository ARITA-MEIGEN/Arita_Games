//=============================================================================
//
// �A�v���P�[�V����
// Author : �L�c����
//
//=============================================================================

// �C���N���[�h
#include "Application.h"
#include"renderer.h"
#include"Object2D.h"
#include"Object.h"
#include"Bg.h"
#include"Title.h"
#include"Tutorial.h"
#include"Game.h"
#include"Result.h"
#include"Ranking.h"
#include"Fade.h"
#include"Score.h"
#include"main.h"
#include"sound.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"

//�ÓI�����o�ϐ�
CRenderer*CApplication::m_pRenderer = nullptr;
DWORD CApplication::m_dwGameStartTime;		//�Q�[���J�n����
DWORD CApplication::m_dwGameTime;			//�Q�[���o�ߎ���
bool CApplication::m_bEndGame;				//�I���t���O
CTitle*CApplication::m_pTitle = nullptr;
CTutorial* CApplication::m_pTutorial = nullptr;
CGame*CApplication::m_pGame=nullptr;
CResult*CApplication::m_pResult = nullptr;
CApplication::MODE CApplication::m_mode;
CFade* CApplication::m_pFade = nullptr;
int CApplication::m_nScore;
int CApplication::m_StopTime = 0;	//���Ԓ�~�p
bool CApplication::m_bSlow=false;
int CApplication::m_nFrame = 0;		//���݂̃t���[��
CInputKeyboard*CApplication::m_pInputKeyboard = nullptr;
CInputJoyPad*CApplication::m_pInputJoyPad=nullptr;
CRanking*CApplication::m_pRank = nullptr;


//====================================
//�R���X�g���N�^
//====================================
CApplication::CApplication()
{
}

//====================================
//�f�X�g���N�^
//====================================
CApplication::~CApplication()
{

}

//====================================
//������
//====================================
HRESULT CApplication::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputJoyPad = new CInputJoyPad;
	m_pFade = new CFade;

	//�T�E���h����
	InitSound(hWnd);
	//�Q�[���J�n���Ԃ�ݒ�
	m_dwGameStartTime = timeGetTime();

	//����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//�����������Ɏ��s�����ꍇ
		return-1;
	}

	//�L�[�{�[�h�̐���
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return-1;
	}

	//�L�[�{�[�h�̐���
	m_pInputJoyPad->Init();

	//���[�h�̐ݒ�
	m_pFade->Init(MODE_TITLE);

	return S_OK;
}

//====================================
//�I��
//====================================
void CApplication::Uninit()
{
	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�W���C�p�b�h�̔j��
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Uninit();
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != nullptr)
	{
		// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		// �I������
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	UninitSound();
}

//====================================
//�X�V
//====================================
void CApplication::Update()
{
	//�o�ߎ��Ԃ̍X�V
	if (m_bEndGame == false)
	{
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}

	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyboard!=nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//�W���C�p�b�h�X�V
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Update();
	}

	//�����_���[�̍X�V
	if (m_pRenderer != nullptr&&m_StopTime <=0)
	{
		if (m_bSlow==true)
		{
			if (m_nFrame % SLOW_SPEED == 0)
			{
				m_pRenderer->Update();
			}
		}
		else
		{
			m_pRenderer->Update();
		}
	}

	//�t�F�[�h�̍X�V
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	switch (m_mode)
	{//��ʂ̍X�V
	case MODE_TITLE:	//�^�C�g�����
		m_pTitle->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	case MODE_GAME:		//�Q�[�����
		m_pGame->Update();
		break;

	case MODE_RESULT:	//���U���g���
		m_pResult->Update();
		break;

	case MODE_RANKING:
		m_pRank->Update();
		break;
	}
	m_nFrame++;
	m_StopTime--;
}

//====================================
//�`��
//====================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}

//====================================
//�����_���[�̎擾
//====================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//====================================
//�L�[�{�[�h�̎擾
//====================================
CInputKeyboard * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//====================================
//�W���C�p�b�h�̎擾
//====================================
CInputJoyPad * CApplication::GetInputJoypad()
{
	return m_pInputJoyPad;
}

//=============================================================================
// ���ԕ\��
//=============================================================================
#ifdef _DEBUG
void CApplication::DrawTime(LPD3DXFONT pFont)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR aStr[256];

	if (m_bEndGame==false)
	{
		sprintf(aStr, _T("\n�o�ߎ���: %.1f\n"), (float)m_dwGameTime / 1000.f);
	}

	// �e�L�X�g�`��
	pFont->DrawText(NULL, aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG

//======================================================
//���[�h�̐ݒ�
//======================================================
void CApplication::SetMode(MODE mode)
{
	//�V�������(���[�h)�̏���������
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		m_pTitle->Uninit();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		break;

	case MODE_GAME:		//�Q�[�����
		m_nScore = CGame::GetScore()->GetScore();	//�X�R�A�ۑ�
		m_pGame->Uninit();
		break;

	case MODE_RESULT:	//���U���g���
		m_pResult->Uninit();
		break;

	case MODE_RANKING:
		m_pRank->Uninit();
		break;
	}
	CApplication::SlowTime(false);		//�X���[����
	StopSound();
	m_mode = mode;	//���݂̉��(���[�h)��؂�ւ���
	CObject::ReleaseAll();

	//�V�������(���[�h)�̏���������
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		m_pTitle = nullptr;
		m_pTitle = new CTitle;
		m_pTitle->Init();
		PlaySound(SOUND_LABEL_TITLE);
		break;

	case MODE_TUTORIAL:
		m_pTutorial = nullptr;
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		break;

	case MODE_GAME:		//�Q�[�����
		m_pGame = nullptr;
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:	//���U���g���
		m_pResult = nullptr;
		m_pResult = new CResult;
		m_pResult->Init();
		CResult::GetScore()->SetScore(m_nScore);
		PlaySound(SOUND_LABEL_RESULT);
		break;

	case MODE_RANKING:
		m_pRank = nullptr;
		m_pRank = new CRanking;
		m_pRank->Init();
		m_pRank->Set(m_nScore);
		break;
	}
}

//======================================================
//���݂̃��[�h�̎擾
//======================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}

//======================================================
//���Ԓ�~�̐ݒ�
//======================================================
void CApplication::StopTime(int frame)
{
	m_StopTime = frame;
}

//======================================================
//�X���[�ݒ�
//======================================================
void CApplication::SlowTime(bool slow)
{//ON/OFF�؂�ւ�
	m_bSlow = slow;
}
