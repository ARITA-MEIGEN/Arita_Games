#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//�v���g�^�C�v�錾
void InitScore(void);		//�X�R�A�̏���������
void UninitScore(void);		//�X�R�A�̏I������
void UpdateScore(void);		//�X�R�A�̍X�V����
void DrawScore(void);		//�X�R�A�̕`�揈��
void SetScore(int nScore);	//�X�R�A�̐ݒ菈��
void AddScore(int nValue);	//�X�R�A�̉��Z����
int GetScore(void);			//�X�R�A�̓��_�̎擾

#endif 
