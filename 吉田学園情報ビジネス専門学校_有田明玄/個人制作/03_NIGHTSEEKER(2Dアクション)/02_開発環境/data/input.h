#ifndef _INPUT_H_
#define _INPUT_H_	//��d�C���N���[�h�h�~�p

#include "main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP=0,	//�\���L�[(��)
	JOYKEY_DOWN,	//�\���L�[(��)
	JOYKEY_LEFT,	//�\���L�[(��)
	JOYKEY_RIGHT,	//�\���L�[(�E)
	JOYKEY_START,	//�X�^�[�g�{�^��
	JOYKEY_BACK,	//�o�b�N�{�^��
	JOYKEY_LPUSH,	//L�X�e�B�b�N��������
	JOYKEY_RPUSH,	//R�X�e�B�b�N��������
	JOYKEY_LB,		//L�{�^��
	JOYKEY_RB,		//R�{�^��
	JOYKEY_NONE1,	//�����Ȃ�
	JOYKEY_NONE2,	//�����Ȃ�
	JOYKEY_A,		//A�{�^��
	JOYKEY_B,		//B�{�^��
	JOYKEY_X,		//X�{�^��
	JOYKEY_Y,		//Y�{�^��
	JOYKEY_LSTICK,	//���X�e�B�b�N
	JOYKEY_RSTICK,	//�E�X�e�B�b�N
	JOYKEY_NONE5,	//�����Ȃ�
	JOYKEY_NONE6,	//�����Ȃ�
	JOYKEY_NONE7,	//�����Ȃ�
	JOYKEY_NONE8,	//�����Ȃ�
	JOYKEY_NONE9,	//�����Ȃ�
	JOYKEY_NONE10,	//�����Ȃ�
	JOYKEY_NONE11,	//�����Ȃ�
	JOYKEY_NONE12,	//�����Ȃ�
	JOYKEY_NONE13,	//�����Ȃ�
	JOYKEY_NONE14,	//�����Ȃ�
	JOYKEY_NONE15,	//�����Ȃ�
	JOYKEY_NONE16,	//�����Ȃ�
	JOYKEY_NONE17,	//�����Ȃ�
	JOYKEY_NONE18,	//�����Ȃ�
	//�����炭�ȉ����[�v
	JOYKEY_NONE19,	//�����Ȃ� �s����m�FJOYKEY_UP�Ɠ�������
	JOYKEY_NONE20,	//�����Ȃ� �s����m�FJOYKEY_DOWN�Ɠ�������
	JOYKEY_TEST		//�e�X�g�p
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏���������
void UninitKeyboard(void);								//�L�[�{�[�h�̏I������
void UpdateKeyboard(void);								//�L�[�{�[�h�̍X�V����
bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�v���X�����擾
bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�g���K�[�����擾
bool GetKeyboardRelease(int nKey);						//�L�[�{�[�h�����[�X�����擾
bool GetKeyboardRepeat(int nKey);						//�L�[�{�[�h���s�[�g�����擾
HRESULT InitJoypad(void);								//�W���C�p�b�h�̏���������
void UninitJoypad(void);								//�W���C�p�b�h�̏I������
void Updatejoypad(void);								//�W���C�p�b�h�̍X�V����
bool GetJoypadPress(JOYKEY key);						//�W���C�p�b�h�̃v���X���
bool GetJoypadTrigger(JOYKEY key);						//�W���C�p�b�h�̃g���K�[���
D3DXVECTOR3 GetJoypadStick(JOYKEY key);					//�W���C�p�b�h�̃X�e�B�b�N���
void Joypadvibration(int nTime, int nStrength);			//�W���C�p�b�h�̐U���ݒ�

#endif