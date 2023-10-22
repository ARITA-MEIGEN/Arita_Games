//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define ENEMY_HEIGHT	(50.0f)		//�v���C���[�̍���
#define ENEMY_WIDTH		(50.0f)		//�v���C���[�̕�
#define CANNON_HEIGHT	(100.0f)	//�Œ�C��̗���
#define CANNON_WIDTH	(100.0f)	//�Œ�C��̉���
#define ENEMY_TEX		(5)			//�e�N�X�`���̖���
#define BOSS001_TEX		(5)			//�ŏ��̃{�X�̃e�N�X�`���̖���
#define DEFAULT_BULLETRATE	(70)	//�A�˃��[�g


//�O���錾

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CEnemy : public CObject2D
{
public:
	enum MOVEPATTERN
	{//�s���p�^�[���̐ݒ�
		MOVE_000 = 0,	//�E�֒����ړ�	
		MOVE_001,		//���֒����ړ�
		MOVE_002,		//���E�ɂ��˂��˂��Ȃ��牺�ɍs��(�ŏ��͉E�Ɉړ�)
		MOVE_003,		//���E�ɂ��˂��˂��Ȃ��牺�ɍs��(�ŏ��͍��Ɉړ�)
		MOVE_004,		//�㉺�ɂ��˂��˂��Ȃ��獶����E��(�ŏ��͉���)
		MOVE_005,		//�㉺�ɂ��˂��˂��Ȃ���E���獶��(�ŏ��͉���)
		MOVE_006,		//���ォ��E����
		MOVE_007,		//�E�ォ�獶����
		MOVE_008,		//�w�i�ƈꏏ�ɏォ�牺�֍~��Ă���(�\������)
		MOVE_009,		//�w�i�ƈꏏ�ɏォ�牺�֍~��Ă���(X������)
		MOVE_010,		//�w�i�ƈꏏ�ɏォ�牺�֍~��Ă���ʏ�
		MOVE_BOSS_BASE,
		MOVE_BOSS_CANNON,		//�Œ�C��
		MOVE_BOSS_ATCANNON,		//���@�_��
		MOVE_BOSS_CORE,
		MOVE_BOSS_CORECANNON,
		MOVE_BONUS,		//�{�[�i�X�G�@�U�����Ȃ�
		MOVE_INVALID,	//���ݒ�
		MOVE_MAX
	};

	//�v���C���[�̏��
	enum ENEMYSTATE
	{
		ENEMYSTATE_APPEAR = 0,	//�o����ԁ@��ʓ��ɓo�ꂷ��܂Ŗ��G
		ENEMYSTATE_NORMAL,		//�ʏ���
		ENEMYSTATE_DAMAGE,		//�_���[�W���
		ENEMYSTATE_DEATH,		//���S���
		ENEMYSTATE_NONE,		//�g���Ă��Ȃ�
		ENEMYSTATE_MAX
	};

	CEnemy();														//�R���X�g���N�^
	~CEnemy()override;												//�f�X�g���N�^
	HRESULT Init(float Width, float Height)override;				//������
	void Uninit()override;											//�I��
	void Update()override;											//�X�V
	void Draw()override;											//�`��
	static HRESULT Load();											//�f�[�^��ǂݍ���
	static void Unload();											//�ǂݍ��񂾃f�[�^��j��
	static CEnemy *Create(MOVEPATTERN moveptn, D3DXVECTOR3 pos);	//����
	void SetMove();													//�s���p�^�[���̐ݒ�
	void SetMovePtn(MOVEPATTERN moveptn);							//�s���p�^�[���̎w��
	void StateManagement();
	void Damage(int damage);										//�_���[�W����
	void Offscreen();												//��ʊO����
	ENEMYSTATE GetState();											//��Ԏ擾
	void Shot();													//�ˌ�
	void Lockon();
	MOVEPATTERN GetMovePtn();

private:
	//�����o�֐�
	static int m_nEnemy;											//�G�̐�
	D3DXVECTOR3 m_move;												//�ړ���
	MOVEPATTERN m_Moveptn;											//�s���p�^�[��
	int m_nCnt;
	int m_nCntState;
	float m_fPtntitle;
	ENEMYSTATE m_state;												//�G�̏��
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_TEX];				//�e�N�X�`���̐�
	static LPDIRECT3DTEXTURE9 m_apBossTexture[BOSS001_TEX];			//�e�N�X�`���̐�
	bool m_bCharge;													//�`���[�W���o�̕t�^
	int m_nLife;													//�̗�
};
#endif // !_OBJECT_H_



