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
	SOUND_LABEL_TITLE = 0,			// �^�C�g�����
	SOUND_LABEL_STAGE001,			// BGM0
	SOUND_LABEL_STAGE001BOSS,		// BGM1
	SOUND_LABEL_STAGE002,			// BGM2
	SOUND_LABEL_RESULT,				// ���U���g���
	SOUND_LABEL_SE_REDBEAM,			// �ԃr�[��
	SOUND_LABEL_SE_BLUEMISSILE,		// �~�T�C��
	SOUND_LABEL_SE_FUSIONSHOT,		// ���̃r�[��
	SOUND_LABEL_SE_GAMESTART,		// �X�^�[�g
	SOUND_LABEL_SE_EXPLOSION001,	// ������(�v���C���[)
	SOUND_LABEL_SE_EXPLOSION002,	// ������(��e)
	SOUND_LABEL_SE_EXPLOSION003,	// ������(�G��)
	SOUND_LABEL_SE_EXPLOSION004,	// ������(�~�T�C�����e)
	SOUND_LABEL_SE_EXPLOSION005,	// ��e��(�Q�[���I�[�o�[)
	SOUND_LABEL_SE_UNION,			// ����
	SOUND_LABEL_SE_SEPARATION,		// ����
	SOUND_LABEL_SE_HEAL,			// ��
	SOUND_LABEL_SE_SIREN,			// �{�X��J�n
	SOUND_LABEL_SE_CHARGE,			// ��C�`���[�W
	SOUND_LABEL_SE_BOSSCANNON,		// ��C����
	SOUND_LABEL_SE_DELETEBULLET,	// �e���������Ƃ��̉�

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
