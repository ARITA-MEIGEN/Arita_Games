//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"
#include<iostream>

//�}�N����`
#define PLAYER_HEIGHT		(35)		//�v���C���[�̍���
#define PLAYER_WIDTH		(40)		//�v���C���[�̕�	
#define PLAYER_TEX			(2)			//�e�N�X�`���̖���
#define PLAYER_MOVE			(8.0f)		//�v���C���[�̈ړ���
#define PLAYER_MAXLIFE		(5)			//�ő�̗�
#define PLAYER_DEFAULTLIFE	(3)			//�����̗�
#define RED_RATE			(15)		//�A�˃��[�g��
#define BLUE_RATE			(80)		//�A�˃��[�g��
#define YELLOW_RATE			(125)		//�A�˃��[�g��
#define NEXT_TIME			(60)		//����ł��玟�̉�ʂɍs���܂ł̎���

//����֘A
#define JOYPAD_UP		(pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_UP) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).y <= -1.0f)		//��
#define JOYPAD_DOWN		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_DOWN) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).y >= 1.0f)		//��
#define JOYPAD_LEFT		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_LEFT) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).x <= -1.0f)		//��
#define JOYPAD_RIGHT	(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_RIGHT) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).x >= 1.0f)		//�E

//�ˌ�
#define JOYPAD_SHOT				(pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_X)||pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_Y))
//�ˌ�����
#define JOYPAD_SHOT_RELEASE		(pJoyPad->GetJoypadRelease(CInputJoyPad::JOYKEY_X)||pJoyPad->GetJoypadRelease(CInputJoyPad::JOYKEY_Y))

//�O���錾
class COption;

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CPlayer : public CObject2D
{
public:
	//�v���C���[�̏��
	enum PLAYERSTATE
	{
		PLAYERSTATE_APPEAR = 0,	//�o�����(�_��)
		PLAYERSTATE_NORMAL,		//�ʏ���
		PLAYERSTATE_DAMAGE,		//�_���[�W���
		PLAYERSTATE_DEATH,		//���S���
		PLAYERSTATE_MAX
	};

	CPlayer();
	~CPlayer()override;
	HRESULT Init(float Width, float Height)override;	//������
	void Uninit()override;								//�I��
	void Update()override;								//�X�V		
	void Draw()override;								//�`��
	static CPlayer *Create(D3DXVECTOR3 pos);			//����
	void Move(void);			//�ړ��֘A
	static HRESULT Load();		//�e�N�X�`���ǂݍ���
	static void Unload();		//�j��
	void Hit();					//�����蔻��
	static int GetLife();		//�̗͎擾
	void AutoShot();			//�A��
	void Shot(int number);		//�ˌ�
	void Offscreen();			//��ʊO
	void Fusion();				//���̊֘A
	void StateManagement();		//��ԊǗ�
	void Damage();				//�_���[�W����
	void Separation();			//����
	PLAYERSTATE GetState();		//�v���C���[�̏��


private:
	//�����o�֐�
	D3DXVECTOR3 m_Move;
	static int m_nLife;			//�̗͂�3�ȉ��̎��_���[�W���󂯂��1�̂Â����Ă���
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYER_TEX];
	COption*m_apOption[2];
	PLAYERSTATE m_state;
	int nCnt;
	int nCntState;
	float fPtntitle;
	int ShotTimer;
	int TriggerTimer;
	bool bFusion;		//���̊Ǘ�
	bool bShot;			//���̍U��
	int m_nRedCT;
	int m_nBlueCT;
	int m_nYellowCT;
	int m_nSpecial;		//�K�E
};
#endif // !_OBJECT_H_


