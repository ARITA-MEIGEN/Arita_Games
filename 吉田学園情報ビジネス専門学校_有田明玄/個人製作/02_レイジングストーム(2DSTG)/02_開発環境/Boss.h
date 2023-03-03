//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================

#ifndef _BOSS_H_
#define _BOSS_H_

//�C���N���[�h
#include"main.h"

//�}�N����`
#define MAX_CANNON		(4)
#define MAX_ATCANNON	(4)
#define MAX_CORE		(4)
#define MAX_BOSSLIFE	(5)
#define NEXT_BOSS_TIME	(60)		//����ł��玟�̉�ʂɍs���܂ł̎���


//�O���錾
class CEnemy;
//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CBoss :CObject
{
public:
	enum BOSSSTATE
	{
		BOSSSTATE_APPEAR = 0,	//�o����ԁ@��ʓ��ɓo�ꂷ��܂Ŗ��G
		BOSSSTATE_NORMAL,		//�������
		BOSSSTATE_DEATH,		//���S���
		BOSSSTATE_NONE,			//�g���Ă��Ȃ�
		BOSSSTATE_MAX
	};

	CBoss();												//�R���X�g���N�^
	~CBoss();												//�f�X�g���N�^
	HRESULT Init(float Width, float Height);				//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	static CBoss *Create();									//����
	void CoreDamage();										//�R�A���j�󂳂ꂽ�Ƃ��̃_���[�W����
	void StateManager();									//��ԊǗ�
	void InScreen();		
	void SetPos();
	static CBoss::BOSSSTATE GetState();						
	int GetLife();

private:
	//�����o�֐�
	CObject2D*m_pBossbase;
	CEnemy*m_apBossCannon[MAX_CANNON];						//�Œ�C��
	CEnemy*m_apBossATCannon[MAX_ATCANNON];					//���@�_��
	CEnemy*m_pBossCoreCannon;								//�R�A����o��r�[���L���m��
	CEnemy*m_apBossCore[MAX_CORE];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nLife;											//�̗�
    static BOSSSTATE m_BossState;
	int m_time;

};
#endif // !_OBJECT_H_




