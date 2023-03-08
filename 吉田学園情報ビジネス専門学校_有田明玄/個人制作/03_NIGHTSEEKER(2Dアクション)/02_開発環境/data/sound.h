//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3
	SOUND_LABEL_BGM004,				// BGM4
	SOUND_LABEL_SE_EXPLOSION,		// ������
	SOUND_LABEL_SE_SWORDATTACK,		//���̍U����
	SOUND_LABEL_SE_HITSWORDATTACK,	//���������������̉�
	SOUND_LABEL_SE_HIT,				//�v���C���[���_���[�W���󂯂����̉�
	SOUND_LABEL_SE_START,			//�X�^�[�g
	SOUND_LABEL_SE_SELECT,			//�I��
	SOUND_LABEL_SE_BOSS,			//�{�X�o��
	SOUND_LABEL_SE_FIRE,			//�{�X�̍U��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
