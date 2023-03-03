#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"
#include"block.h"

//�}�N����`
#define NUM_ENEMY	(5)			//�G�̎��
#define MAX_ENEMY	(256)		//�G�̍ő吔
#define ENEMY_SIZE	(50.0f)		//�G�̑傫��
//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX

}ENEMYSTATE;

//�G�\���̂̒�`
typedef struct
{
	int nCntAnim;				//�J�E���^�[������������
	int nPtnAnim;				//�p�^�[��No.������������
	float fLng;					//�v���C���[�Ƃ̋���(�Ίp���̒���)
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	int nMoveType;				//�ړ��̃p�^�[��
	int nType;					//���
	D3DXVECTOR3 move;			//�ړ���
	ENEMYSTATE state;			//���
	int nCounterState;			//��ԊǗ��J�E���^�[
	int nLife;					//�̗�
	int nBullettimer;			//�e�̔��ˊԊu
	int nAtk;					//�U����
	bool bUse;					//�g�p���Ă��邩�ǂ���
	Block*pBlock;				//�u���b�N�̃|�C���^
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);									//�G�̏���������
void UninitEnemy(void);									//�G�̏I������
void UpdateEnemy(void);									//�G�̍X�V����
void DrawEnemy(void);									//�G�̕`�揈��
void SetEnemy(D3DXVECTOR3 pos, int type);				//�G�̐ݒ菈��
void HitEnemy(int nCntEnemy, int nDamage);				//�G�̃q�b�g����
Enemy *GetEnemy(void);									//�G�̊l������
void CollisionEnemy(D3DXVECTOR3 *pPos, float Width, float Height);	//�����蔻��
#endif
