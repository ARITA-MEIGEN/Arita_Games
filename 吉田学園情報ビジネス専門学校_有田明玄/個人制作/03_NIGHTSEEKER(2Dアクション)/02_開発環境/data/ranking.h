#ifndef _RANKING_H_
#define _RANKING_H_

#include"main.h"
#include"fade.h"
#include"input.h"

//�}�N����`
#define MAX_RANK			(5)		//�����N��
#define MAX_SCORE			(8)		//�X�R�A�̌���
#define NUM_RANK			(2)		//�����L���O�̃X�R�A�ȊO�̐�

//�v���g�^�C�v�錾
void InitRanking(void);				//�����L���O�̏���������
void UninitRanking(void);			//�����L���O�̏I������
void UpdateRanking(void);			//�����L���O�̍X�V����
void DrawRanking(void);				//�����L���O�̕`�揈��
void ResetRanking(void);			//�����L���O�̃��Z�b�g
void SetRanking(void);				//�����L���O�̐ݒ�
void SaveRanking(void);				//�����L���O�̕ۑ�
void LoadRanking(void);				//�����L���O�̓ǂݍ���


#endif