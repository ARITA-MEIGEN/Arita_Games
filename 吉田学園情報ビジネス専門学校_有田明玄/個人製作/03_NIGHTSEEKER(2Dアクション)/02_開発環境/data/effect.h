#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ʒu
	D3DXCOLOR col;		//�F
	float fRadius;		//���a(�傫��)
	int nLife;			//����
	bool bAdd;			//���Z���������邩�ǂ���
	bool bUse;			//�g�p���Ă��邩�ǂ����̔���
	int nType;			//�e�N�X�`���̎��
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, bool ADD, int nType);
#endif
