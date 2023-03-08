//=================================================
// Content     (�v���C���[�̑���)(player.h)
// Author     : �L�c����
// Since      : (�쐬��2021/10/04)
//=================================================
#ifndef _PLAYER_H_			//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_			//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"	
#include"block.h"

//�}�N����`
#define MAX_KEYMEMORY		(10)		//�L�[�̍ő�L�^��(�R�}���h�Z�p)
#define MIN_SPEED			(0.1f)		//���C�ɂ��Œᑬ�x
#define DASH_SPEED			(0.9f)		//�_�b�V�����̑��x
#define NOMAL_SPEED			(0.5f)		//�ʏ펞�̑��x
#define COLLISION_PLAYER	(0.6f)		//�L�����N�^�[�̓����蔻�蒲���p
#define MAX_PATTERN			(4.0f);		//�e�N�X�`���̃p�^�[����
#define PLAYER_HEIGHT		(60.0f)		//�v���C���[�̍���
#define PLAYER_WIDTH		(35.0f)		//�v���C���[�̕�
#define TEX_X				(0.05f)		//�e�N�X�`���̑傫�������p
#define TEX_Y				(0.2f)		//�e�N�X�`���̑傫�������p
#define	FIRST_ATKTIME		(5)			//�ŏ��̃��[�V�����̎���
#define ALL_ATKTIME1		(20)		//�Z�̑S�̂̎���
#define MAX_PLIFE			(4000)		//�ő僉�C�t

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����(�_��)
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_ATTACK,		//�U�����
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3	posOld;			//�O��̈ʒu
	D3DXVECTOR3 move;			//�ړ���
	int nCntCounterAnim;		//�J�E���^�[
	int nCntPtnAnim;			//�p�^�[���ԍ�
	int nDirectionMove;			//����	�O�̎��͉E�@�P�̎��͍�����
	D3DXVECTOR3 rot;			//����
	bool bIsJumping;			//�W�����v�����ǂ���
	bool bIsDashing;			//�_�b�V�������ǂ���
	bool bDisp;					//�g�p�����ǂ���
	float fPtnflashing;			//�_�ŗp
	int nCntState;				//��ԊǗ��J�E���^�[
	int nLife;					//�̗�
	PLAYERSTATE state;			//�v���C���[�̏�Ԑݒ�
	Block*pBlock;				//���n���Ă���u���b�N�̃A�h���X��ۑ�
	int nCntAtk;				//�U����
	int nAtkTimer;				//�U���̎��ԊԊu
	bool bAtk;					//�U�����Ă邩�ǂ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);						//�v���C���[�̏���������
void UninitPlayer(void);					//�v���C���[�̏I������
void UpdatePlayer(void);					//�v���C���[�̍X�V����
void DrawPlayer(void);						//�v���C���[�̕`�揈��
void SetPlayer(D3DXVECTOR3 pos);			//�v���C���[�̐ݒu
Player *GetPlayer(void);					//�v���C���[�̏��̊l��
void CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height);	//�v���C���[�̓����蔻��
void HitPlayer(int nDamage);				//�v���C���[�ɍU���������������̏���
void CenterPlayer(D3DXVECTOR3 *pPos);		//�v���C���[�����S�ɗ������̏���

#endif 
