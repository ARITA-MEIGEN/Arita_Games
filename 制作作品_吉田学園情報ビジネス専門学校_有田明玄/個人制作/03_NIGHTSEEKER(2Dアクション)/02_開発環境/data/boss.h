#ifndef _BOSS_H_
#define _BOSS_H_

#include"main.h"
#include"block.h"

//�}�N����`
#define NUM_BOSS	(2)			//�{�X�̎��
#define MAX_BOSS	(256)		//�{�X�̍ő吔
#define BOSS_SIZE	(300.0f)		//�{�X�̑傫��
//�{�X�̏��
typedef enum
{
	BOSSSTATE_APPEAR = 0,	//�o�����(�_��)
	BOSSSTATE_NORMAL,		//�ʏ���
	BOSSSTATE_DAMAGE,		//�_���[�W���
	BOSSSTATE_DEATH,		//���S���
	BOSSSTATE_MAX

}BOSSSTATE;

//�{�X�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 move;			//�ړ���
	BOSSSTATE state;			//���
	float fLng;					//�v���C���[�Ƃ̋���(�Ίp���̒���)
	int nType;					//���
	int nCntAnim;				//�J�E���^�[������������
	int nPtnAnim;				//�p�^�[��No.������������
	int nCounterState;			//��ԊǗ��J�E���^�[
	int nMoveType;				//�ړ��̃p�^�[��
	int nDirectionMove;			//����	�O�̎��͉E�@�P�̎��͍�����
	int nLife;					//�̗�
	int nAtkUse;				//�U�������ǂ���
	int nAtk;					//�U����
	bool bUse;					//�g�p���Ă��邩�ǂ���
	Block*pBlock;				//�u���b�N�̃|�C���^
}BOSS;

//�v���g�^�C�v�錾
void InitBoss(void);									//�{�X�̏���������
void UninitBoss(void);									//�{�X�̏I������
void UpdateBoss(void);									//�{�X�̍X�V����
void DrawBoss(void);									//�{�X�̕`�揈��
void SetBoss(D3DXVECTOR3 pos);							//�{�X�̐ݒ菈��
void HitBoss(int nDamage);								//�{�X�̃q�b�g����
BOSS *GetBoss(void);									//�{�X�̊l������
//�{�X�̓����蔻��
void CollisionBoss(D3DXVECTOR3 *pPos, float Width, float Height);

#endif

