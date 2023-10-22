//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"
#include"Enemy.h"

#define MAX_ENEMY	(128)

class CBoss;
//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CEnemyManager
{
public:
	CEnemyManager();											//�R���X�g���N�^
	~CEnemyManager();											//�f�X�g���N�^
	void Init();												//������
	void Uninit();												//�I��
	void Update();												//�X�V
	void SetEnemy(CEnemy::MOVEPATTERN moveptn, D3DXVECTOR3 pos,int frame);	//�G�̐ݒ�
	static CBoss* GetBoss();	//�G�̐ݒ�

private:
	//�����o�֐�
	static CBoss*m_pBoss;
	CEnemy::MOVEPATTERN m_aMoveptn[MAX_ENEMY];
	D3DXVECTOR3 m_aPos[MAX_ENEMY];
	int m_anFrame[MAX_ENEMY];
};
#endif // !_OBJECT_H_




