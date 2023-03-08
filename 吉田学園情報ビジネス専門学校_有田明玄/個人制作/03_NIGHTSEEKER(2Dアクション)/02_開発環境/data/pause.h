#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"	
#include"input.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//�|�[�Y�̏��
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,		//�R���e�B�j���[�_��
	PAUSE_MENU_RETRY,			//���g���C�_��
	PAUSE_MENU_QUIT,			//�^�C�g���_��
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);	//�w�i�̏���������
void UninitPause(void);//�w�i�̏I������
void UpdatePause(void);//�w�i�̍X�V����
void DrawPause(void);	//�w�i�̕`�揈��

#endif 
