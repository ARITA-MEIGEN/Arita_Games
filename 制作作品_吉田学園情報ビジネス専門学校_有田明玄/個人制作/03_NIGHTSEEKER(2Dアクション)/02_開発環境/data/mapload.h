//=================================================
// Content     (�v���C���[�̑���)(mapload.h)
// Author     : �L�c����
// Since      : (�쐬��2021/10/04)
//=================================================
#ifndef _MAPLOAD_H_			//���̃}�N����`������ĂȂ�������
#define _MAPLOAD_H_			//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"	


//�u���b�N�\���̂̒�`
typedef enum
{
	BLOCK_NONE = 0,
	BLOCK_BLOWN,
	BLOCK_MAX
}BLOCKTYPE;

//�v���g�^�C�v�錾
void InitMapLoad(void);				//�}�b�v�ǂݍ��݂̏���������
void UpdateMapLoad(void);			//�}�b�v�ǂݍ��݂̍X�V����

#endif 

