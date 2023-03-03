#ifndef _FADE_H_
#define _FADE_H_

#include "Application.h"
#include"Object2D.h"

class CFade
{
public:
	enum FADE
	{//�t�F�[�h�̏��
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX,
	};

	CFade();
	~CFade();
	//�v���g�^�C�v�錾
	void Init(CApplication::MODE modeNext);				//�t�F�[�h�̏���������
	void Uninit(void);									//�t�F�[�h�̏I������
	void Update(void);									//�t�F�[�h�̍X�V����
	void Draw(void);									//�t�F�[�h�̕`�揈��
	static void Set(CApplication::MODE modeNext);		//�t�F�[�h�̐ݒ菈��
	static FADE Get(void);								//�t�F�[�h�̊l������

private:
	//�O���[�o���ϐ�
	CObject2D*m_aObject[1];							//�t�F�[�h�p�|���S��
	static FADE m_fade;								//�t�F�[�h�̏��
	static CApplication::MODE m_modeNext;			//���̉��(���[�h)
	static D3DXCOLOR m_colorFade;					//�|���S��(�t�F�[�h)�̐F
};

#endif

