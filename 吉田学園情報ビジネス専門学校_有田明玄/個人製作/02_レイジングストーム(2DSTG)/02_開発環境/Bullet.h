//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

class CEnemy;

//�}�N����`
#define BULLET_TEX				(5)			//�e�N�X�`���̖���
#define BULLET_WIDTH_RED		(20.0f)		//�Ԓe�̉���
#define BULLET_HEIGHT_RED		(70.0f)		//�Ԓe�̏c��
#define BULLET_WIDTH_BLUE		(20.0f)		//�e�̉���
#define BULLET_HEIGHT_BLUE		(40.0f)		//�e�̏c��
#define BULLET_WIDTH_YELLOW		(20.0f)		//���e�̉���
#define BULLET_HEIGHT_YELLOW	(70.0f)		//���e�̏c��
#define	BULLET_SIZ				(20.0f)		//�G�̒e�̑傫��
#define BULLET_LIFE				(500)		//�e�̎���
#define BEAM_WIDTH				(120.0f)	//���̃r�[���̉���
#define RED_SPEED				(20.0f)		//�ԃr�[���̑��x
#define BLUE_SPEED				(10.0f)		//�~�T�C�����x
#define YELLOW_SPEED			(5.0f)		//�h�������x
#define ENEMY_SPEED				(6.0f)		//�G�̒e��(���@�_��)
#define CANNON_SPEED			(6.0f)		//�G�̒e��(�Œ�C��)
#define RED_DAMAGE				(150)		//�Ԃ̈З�
#define BLUE_DAMAGE				(125)		//�̈З�
#define YELLOW_DAMAGE			(200)		//���̈З�
#define FUSION_DAMAGE			(50)		//���̂̈З�
#define DEFAULT_HIT				(1)			//�f�t�H���g�q�b�g��
#define YELLOW_HIT				(3)			//���h�����̃q�b�g��
#define DEFAULT_NEXTHIT			(1)			//�q�b�g���Ă���_���[�W���肪��������܂ł̎���


//�O���錾
//=============================================================================
// �\���̒�`
//=============================================================================
class CBullet : public CObject2D
{
public:
	enum EBULLETTYPE
	{
		BTYPE_REDBEAM = 0,		//�ԋ@�̗p
		BTYPE_BLUEMSSILE,		//�@�̗p
		BTYPE_YELLOWDRILL,		//���@�̗p
		BTYPE_FUSIONSHOT,		//���̋@�̗p
		ENEMY_BULLET,			//�G
		ENEMY_CANNON01,			//����1����
		ENEMY_CANNON02,			//����2����
		ENEMY_CANNON03,			//����3����
		ENEMY_CANNON04,			//����4����
		ENEMY_CANNON06,			//����6����
		ENEMY_CANNON07,			//����7����
		ENEMY_CANNON08,			//����8����
		ENEMY_CANNON09,			//����9����
		ENEMY_BEAMCANNON,		//�R�A�L���m���̃r�[��
		BTYPE_INVALID,			//���g�p
		BTYPE_MAX
	};

	CBullet();
	~CBullet()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CBullet *Create(D3DXVECTOR3 pos, EBULLETTYPE type);
	HRESULT Hit();
	void Lockon();		//�z�[�~���O�̃^�[�Q�b�g�ݒ�
	void SetHorming();
	void Offscreen();
	static void SetBeam(bool use);
	void FusionBeam();
	static void GetPlayerPos(D3DXVECTOR3 pos);


private:
	//�����o�֐�
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLET_TEX];
	D3DXVECTOR3 m_Move;
	int m_nMoveCnt;					//�s������p
	int m_Target;					//�~�T�C���̃^�[�Q�b�g
	EBULLETTYPE m_eType;			//�e�̎��
	static bool m_bUse;				//�����Ă邩�ǂ���
	static D3DXVECTOR3 m_playerpos;	//�v���C���[�̈ʒu
	bool m_bEnemy;					//�G�̒e���ǂ���
	int m_HitCount;					//�c��q�b�g��
	int m_NextHItTime;				//�_���[�W���肪��������܂ł̎���
};
#endif // !_OBJECT_H_



