#ifndef _ATTACK_H_	//���̃}�N����`������ĂȂ�������
#define _ATTACK_H_	//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu
	D3DXCOLOR col;		//�F
	int nCntAnim;		//�G�t�F�N�g�̃J�E���^�[
	int nPtnAnim;		//�A�j���[�V�����̔ԍ�
	float fRadiuswidth;	//����
	float fRadiusheight;//�c��
	bool bUse;			//�g�p���Ă��邩�ǂ����̔���
	int nDirection;		//����
}Attack;

//����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	D3DXCOLOR col;				//�F
	float fLength;				//�Ίp���̒���
	float fAngle;				//�Ίp���̊p�x
	int  nLife;					//����
	bool bCollision;			//�����蔻��̎g�p�̗L��
	bool bDisp;					//�g�p���Ă��邩�ǂ����̔���
}Weapon;

//�v���g�^�C�v�錾
void InitAttack(void);		//�U���G�t�F�N�g�̏���������
void UninitAttack(void);	//�U���G�t�F�N�g�̏I������
void UpdateAttack(void);	//�U���G�t�F�N�g�̍X�V����
void DrawAttack(void);		//�U���G�t�F�N�g�̕`�揈��

//�U���G�t�F�N�g�̐ݒ菈��
void SetAttack(float posx, float posy, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight,int nDirection);
//����̐ݒ菈��
void Setweapon(float posx, float posy, float posz, D3DXCOLOR col, int Life, bool collision);
//����̓����蔻��
bool CollisionWeapon(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height);


#endif
