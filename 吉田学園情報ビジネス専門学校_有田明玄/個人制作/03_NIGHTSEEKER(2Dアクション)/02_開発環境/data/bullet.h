//=================================================
// Content     (�e�ۂ̐ݒ�)(bullet.h)
// Author     : �L�c����
//=================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���ˈʒu
	D3DXVECTOR3 move;	//�ړ���
	float fWidth;		//����
	float fHeight;		//�c��
	int nLife;			//����
	int nDamage;		//�_���[�W��
	bool bUse;			//�g�p���Ă��邩�ǂ����̔���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);				//�e�̏���������
void UninitBullet(void);			//�e�̏I������
void UpdateBullet(void);			//�e�̍X�V����
void DrawBullet(void);				//�e�̕`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int Damage, float Width, float Height);	//�e�̐ݒu
void SetHorming(int CntBullet);		//�e�̃z�[�~���O�̐ݒ�
Bullet *GetBullet(void);			//�e�̏��̊l��
void CollisionBullet(D3DXVECTOR3 *pPos, float Width, float Height);	//�e�̓����蔻��

#endif 


