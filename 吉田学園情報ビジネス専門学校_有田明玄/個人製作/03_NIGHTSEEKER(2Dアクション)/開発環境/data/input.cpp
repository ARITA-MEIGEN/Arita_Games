//=================================================
// Content     (�L�[�{�[�h�̐ݒ�)(input.cpp)
// Author     : �L�c����
// LastUpdate : (�X�V��2021/08/14)
// Since      : (�쐬��2021/07/06)
//=================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX		(256)					//�L�[�̍ő吔

//�O���[�o���ϐ�		
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];			//�L�[�{�[�h�̃��s�[�g���
XINPUT_STATE g_joyKeyState;						//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger;				//�W���C�p�b�h�̃g���K�[���
D3DXVECTOR3 g_JoyStickPos;						//�W���C�X�e�B�b�N
XINPUT_VIBRATION g_joyMoter;					//�U���̐ݒ�
int g_nTime;									//�U���̎���
int g_nStrength;								//�U���̋���
//==========================
//�L�[�{�[�h�̏������ݒ�
//==========================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//==========================
//�L�[�{�[�h�̏I������
//==========================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//==========================
//�L�[�{�[�h�̍X�V����
//==========================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���l��
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];						//�L�[�̃g���K�[���ۑ�
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&g_aKeyState[nCntKey];						//�L�[�̃����[�X���ۑ�	(g_aKeyStateTrigger[nCntKey] ^ aKeyState[nCntKey])&g_aKeyStateTrigger[nCntKey]
			//g_aKeyStateRepeat[nCntKey] = g_aKeyStateTrigger[nCntKey]^(g_aKeyState[nCntKey] & aKeyState[nCntKey]);				//�L�[�̃��s�[�g���ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																			//�L�[�̃v���X���ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//�L�[�̃A�N�Z�X���l��
	}
}
//==========================================
//�L�[�{�[�h�v���X�����擾
//==========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=========================================
//�L�[�{�[�h�g���K�[�����擾
//=========================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================
//�L�[�{�[�h�����[�X�����擾
//=========================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=========================================
//�L�[�{�[�h���s�[�g�����擾
//=========================================
bool GetKeyboardRepeat(int nKey)				
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}
//=========================================
//�W���C�p�b�h�̏���������
//=========================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g�̐ݒ�(�L���ɂ���)
	XInputEnable(true);

	//�W���C�p�b�h�̐U�������0�N���A
	ZeroMemory(&g_joyMoter, sizeof(XINPUT_VIBRATION));

	//�U������̏�����
	g_nStrength = 0;
	g_nTime = 0;

	return S_OK;
}
//=========================================
//�W���C�p�b�h�̏I������
//=========================================
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�(�����ɂ���)
	XInputEnable(false);
}
//=========================================
//�W���C�p�b�h�̍X�V����
//=========================================
void Updatejoypad(void)
{
	XINPUT_STATE joykeyState;	//�W���C�p�b�h�̓��͏��
	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joyKeyStateTrigger.Gamepad.wButtons = (g_joyKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons)&joykeyState.Gamepad.wButtons;	//�L�[�̃g���K�[���ۑ�
		g_joyKeyState = joykeyState;	//�W���C�p�b�h�̃v���X����ۑ�
	}

	//�W���C�p�b�h�̐U��
	g_joyMoter.wLeftMotorSpeed = (WORD)g_nStrength;
	g_joyMoter.wRightMotorSpeed = (WORD)g_nStrength;
	XInputSetState(0, &g_joyMoter);

	if (g_nTime>0)
	{
		g_nTime--;
	}
	else
	{
		g_nStrength = 0;
		g_nTime = 0;
	}
}
//=========================================
//�W���C�p�b�h�̃v���X�����擾
//=========================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons&(0x01 << key)) ? true : false;
}
//=========================================
//�W���C�p�b�h�̃v���X�����擾
//=========================================
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons&(0x01 << key)) ? true : false;
}
//=========================================
//�W���C�p�b�h�̃X�e�B�b�N�����擾
//=========================================
D3DXVECTOR3 GetJoypadStick(JOYKEY key)
{
	switch (key)
	{
	case JOYKEY_LSTICK:
		g_JoyStickPos = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbLX / 20000.0f, -g_joyKeyState.Gamepad.sThumbLY / 20000.0f, 0.0f);
		break;
	case JOYKEY_RSTICK:
		g_JoyStickPos = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbRX / 20000.0f, -g_joyKeyState.Gamepad.sThumbRY / 20000.0f, 0.0f);
		break;
	}
	return g_JoyStickPos;
}
//=========================================
//�R���g���[���[�̐U������
//=========================================
void Joypadvibration(int nTime,int nStrength)
{
	g_nTime = nTime;			//�U����������
	g_nStrength = nStrength;	//�U���̋���
}