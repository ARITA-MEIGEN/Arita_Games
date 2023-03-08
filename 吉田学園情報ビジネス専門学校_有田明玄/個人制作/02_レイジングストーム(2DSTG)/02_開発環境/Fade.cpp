//=================================================
// Content     (�t�F�[�h�̐ݒ�)(fade.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/29)
//=================================================
#include "fade.h"

//�ÓI�����o�ϐ�
 CFade::FADE CFade::m_fade;						
 CApplication::MODE CFade::m_modeNext;			
 D3DXCOLOR CFade::m_colorFade;					
//======================================================
//�R���X�g���N�^
//======================================================
CFade::CFade()
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CFade::~CFade()
{
}

//======================================================
//�t�F�[�h�̏���������
//======================================================
void CFade::Init(CApplication::MODE modeNext)
{
	m_aObject[0] = new CObject2D(CObject::OBJTYPE_FADE);
	m_aObject[0]->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_aObject[0]->SetPos(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0f));
	
	m_fade = FADE_IN;									//�t�F�[�h�C����Ԃ�
	m_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�����|���S��(�s����)�ɂ��Ă���
	m_aObject[0]->SetCol(m_colorFade);
	//���[�h�̐ݒ�
	CApplication::SetMode(m_modeNext);
}

//======================================================
//�t�F�[�h�̏I������
//======================================================
void CFade::Uninit(void)
{

}
//======================================================
//�t�F�[�h�̍X�V����
//======================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_colorFade.a -= 0.03f;			//�|���S���𓧖��ɂ��Ă���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_colorFade.a += 0.01f;	//�|���S����s�����ɂ��Ă���
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;			//�������Ă��Ȃ���Ԃ�

				//���[�h�ݒ�(���̃��[�h�Ɉڍs)
				CApplication::SetMode(m_modeNext);
			}
		}
	//���_�J���[�ݒ�
	m_aObject[0]->SetCol(m_colorFade);
	}
}
//======================================================
//�t�F�[�h�̕`�揈��
//======================================================
void CFade::Draw(void)
{

}
//======================================================
//�t�F�[�h�̐ݒ菈��
//======================================================
void CFade::Set(CApplication::MODE modeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;									//�t�F�[�h�A�E�g��Ԃ�
		m_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
	}
}
//======================================================
//�t�F�[�h�̊l������
//======================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}