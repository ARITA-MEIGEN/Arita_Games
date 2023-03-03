//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
//�C���N���[�h
#include"main.h"
#include"Bg.h"
#include"Result.h"
#include"Score.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"sound.h"
#include"Fade.h"

//�ÓI�����o�ϐ�
CBg*CResult::m_pBg = nullptr;
CScore*CResult::m_pScore=nullptr;

//====================================
//�R���X�g���N�^
//====================================
CResult::CResult()
{
}

//====================================
//�f�X�g���N�^
//====================================
CResult::~CResult()
{

}

//====================================
//������
//====================================
HRESULT CResult::Init()
{
	//�e�N�X�`���̓ǂݍ���
	CBg::Load();
	CScore::Load();
	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_RESULT);
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2-70.0f, SCREEN_HEIGHT / 2+30.5f, 0.0f), D3DXVECTOR2(RESULT_SCORE_WIDTH, RESULT_SCORE_HEIGHT));


	return S_OK;
}

//====================================
//�I��
//====================================
void CResult::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	//�e�N�X�`���̔j��
	CBg::Unload();
	CScore::Unload();
}

//====================================
//�X�V
//====================================
void CResult::Update()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

	////�����̃T�C�Y���z����f�J���Ȃ�o�O�ɑ΂��Ẳ��}���u
	//m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2 - 70.0f, SCREEN_HEIGHT / 2 + 30.5f, 0.0f), D3DXVECTOR2(RESULT_SCORE_WIDTH, RESULT_SCORE_HEIGHT));

	if ((pKeyboard->GetTrigger(DIK_RETURN) == true ||
		pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) == true && CFade::Get() == CFade::FADE_NONE)		//ENTER�L�[
	{//�G���^�[�Ń����L���O��
	 //���[�h�ݒ�
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_RANKING);
	}
}

//====================================
//�`��
//====================================
void CResult::Draw()
{

}

//====================================
//�w�i�̎擾
//====================================
CBg * CResult::GetBg()
{
	return m_pBg;
}

//====================================
//�X�R�A�̎擾
//====================================
CScore*CResult::GetScore()
{
	return m_pScore;
}
