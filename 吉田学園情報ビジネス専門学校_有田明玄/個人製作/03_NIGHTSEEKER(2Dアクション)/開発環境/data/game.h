#ifndef _GAME_H_	//���̃}�N����`������ĂȂ�������
#define _GAME_H_	//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE=0,	//�������Ă��Ȃ����
	GAMESTATE_NORMAL,	//�ʏ���
	GAMESTATE_BOSS,		//�{�X��
	GAMESTATE_CLEAR,	//�Q�[���N���A���
	GAMESTATE_FAILED,	//�Q�[���I�[�o�[���
	GAMESTATE_PAUSE,	//��~���
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UpdateGame(void);
void UninitGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);

#endif