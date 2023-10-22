//=================================================
// Content     (�`���[�g���A����ʏ���)(Tutorial.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/9)
//=================================================
#include"Tutorial.h"
#include"sound.h"
#include"fade.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"renderer.h"

LPDIRECT3DTEXTURE9 CTutorial::m_apTexture[NUM_TEXTR] = {};
//==========================================
//�C���X�g���N�^
//==========================================
CTutorial::CTutorial()
{
}
//==========================================
//�f�X�g���N�^
//==========================================
CTutorial::~CTutorial()
{
}

//==========================================
//����������
//==========================================
void CTutorial::Init(void)
{
	Load();
	for (int i = 0; i < NUM_TEXTR; i++)
	{
		m_apObject2D[i] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0);
		m_apObject2D[i]->BindTexture(m_apTexture[i]);
	}
	m_afAlpha[0] = 1.0f;
	m_afAlpha[1] = 0.0f;
	m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_afAlpha[0]));
	m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_afAlpha[1]));
	m_Next = false;
}

//==========================================
//�I������
//==========================================
void CTutorial::Uninit(void)
{
	for (int i = 0; i < NUM_TEXTR; i++)
	{
		m_apObject2D[i]->Uninit();
	}
	Unload();
	//�T�E���h�̒�~
	StopSound();
}

//==========================================
//�X�V����
//==========================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

	CFade::FADE pFade = CFade::Get();	//�t�F�[�h�̏�Ԃ��擾
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true && pFade == CFade::FADE_NONE)
	{
		//���[�h�ݒ�
		if (m_Next == false)
		{
			PlaySound(SOUND_LABEL_SE_GAMESTART);
			m_Next = true;
		}
	}

	if (m_Next == true)
	{
		m_afAlpha[0] -= 0.03f;
	}
	if (m_afAlpha[0] <= 0.0f)
	{
		m_afAlpha[1] += 0.03f;
	}
	if (m_afAlpha[1] >= 1.0f&&CFade::Get() == CFade::FADE_NONE)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN) && CFade::Get() == CFade::FADE_NONE
			|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) && CFade::Get() == CFade::FADE_NONE
			|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) && CFade::Get() == CFade::FADE_NONE
			|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) && CFade::Get() == CFade::FADE_NONE
			|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) && CFade::Get() == CFade::FADE_NONE
			|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) && CFade::Get() == CFade::FADE_NONE)
		{
			//���[�h�ݒ�
			PlaySound(SOUND_LABEL_SE_GAMESTART);
			CFade::Set(CApplication::MODE_GAME);
		}
	}
	for (int i = 0; i < NUM_TEXTR; i++)
	{//�F�̐ݒ�
		m_apObject2D[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_afAlpha[i]));
	}
}
//==========================================
//�`�揈��
//==========================================
void CTutorial::Draw(void)
{

}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
void CTutorial::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TUTORIAL2.png",
		&m_apTexture[1]);
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CTutorial::Unload()
{
	for (int i = 0; i <NUM_TEXTR; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}