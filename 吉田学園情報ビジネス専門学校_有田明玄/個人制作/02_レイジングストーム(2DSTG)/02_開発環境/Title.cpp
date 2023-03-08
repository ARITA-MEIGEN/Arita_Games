//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
//�C���N���[�h
#include"main.h"
#include"Bg.h"
#include"Title.h"
#include"Application.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"Fade.h"

//�ÓI�����o�ϐ�
CBg*CTitle::m_pBg = nullptr;
//====================================
//�R���X�g���N�^
//====================================
CTitle::CTitle()
{
}

//====================================
//�f�X�g���N�^
//====================================
CTitle::~CTitle()
{

}

//====================================
//������
//====================================
HRESULT CTitle::Init()
{
	//�e�N�X�`���̓ǂݍ���
	CBg::Load();
	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),CApplication::MODE_TITLE);

	return S_OK;
}

//====================================
//�I��
//====================================
void CTitle::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}
	//�e�N�X�`���̔j��
	CBg::Unload();
}

//====================================
//�X�V
//====================================
void CTitle::Update()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

		//�w��̃L�[�������ꂽ���ǂ���
	if (pKeyboard->GetTrigger(DIK_RETURN) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START)&& CFade::Get() == CFade::FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_TUTORIAL);
	}
}

//====================================
//�`��
//====================================
void CTitle::Draw()
{

}

//====================================
//�w�i�̎擾
//====================================
CBg * CTitle::GetBg()
{
	return m_pBg;
}