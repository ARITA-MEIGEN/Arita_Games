//=================================================
// Content     (�u���b�N�̐ݒ�)(Block.h)
// Author     : �L�c����
// Since      : (�쐬��2021/10/12)
//=================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

//�}�N����`
#define MAX_BLOCK		(5120)	//�u���b�N�̍ő吔

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̔��ˈʒu
	D3DXVECTOR3 posold;	//�O��̔��ˈʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//���
	bool death;			
	bool bUse;			//�g�p���Ă��邩�ǂ����̔���
}Block;

//�v���g�^�C�v�錾
void InitBlock(void);											        //�u���b�N�̏���������
void UninitBlock(void);													//�u���b�N�̏I������
void UpdateBlock(void);													//�u���b�N�̍X�V����
void DrawBlock(void);													//�u���b�N�̕`�揈��
void SetBlock(D3DXVECTOR3 pos, float Width, float Height,int Type);		//�u���b�N�̐ݒu
Block *GetBlock(void);													//�u���b�N�̏��̊l��
//�u���b�N�̓����蔻��
bool CollisionBlock(D3DXVECTOR3 *pPos,		//���݂̈ʒu
					D3DXVECTOR3 *pPosOld,	//�O��̈ʒu
					D3DXVECTOR3 *pMove,		//�ړ���
					float Width,			//��
					float fHeight,			//����
					Block**pBlock);			
#endif 

