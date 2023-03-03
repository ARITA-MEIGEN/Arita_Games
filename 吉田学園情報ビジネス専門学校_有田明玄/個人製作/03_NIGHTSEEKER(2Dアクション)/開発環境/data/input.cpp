//=================================================
// Content     (キーボードの設定)(input.cpp)
// Author     : 有田明玄
// LastUpdate : (更新日2021/08/14)
// Since      : (作成日2021/07/06)
//=================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX		(256)					//キーの最大数

//グローバル変数		
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];			//キーボードのリピート情報
XINPUT_STATE g_joyKeyState;						//ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger;				//ジョイパッドのトリガー情報
D3DXVECTOR3 g_JoyStickPos;						//ジョイスティック
XINPUT_VIBRATION g_joyMoter;					//振動の設定
int g_nTime;									//振動の時間
int g_nStrength;								//振動の強さ
//==========================
//キーボードの初期化設定
//==========================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//==========================
//キーボードの終了処理
//==========================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//==========================
//キーボードの更新処理
//==========================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;
	//入力デバイスからデータを獲得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];						//キーのトリガー情報保存
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&g_aKeyState[nCntKey];						//キーのリリース情報保存	(g_aKeyStateTrigger[nCntKey] ^ aKeyState[nCntKey])&g_aKeyStateTrigger[nCntKey]
			//g_aKeyStateRepeat[nCntKey] = g_aKeyStateTrigger[nCntKey]^(g_aKeyState[nCntKey] & aKeyState[nCntKey]);				//キーのリピート情報保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																			//キーのプレス情報保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//キーのアクセス権獲得
	}
}
//==========================================
//キーボードプレス情報を取得
//==========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=========================================
//キーボードトリガー情報を取得
//=========================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================
//キーボードリリース情報を取得
//=========================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=========================================
//キーボードリピート情報を取得
//=========================================
bool GetKeyboardRepeat(int nKey)				
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}
//=========================================
//ジョイパッドの初期化処理
//=========================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinputのステートの設定(有効にする)
	XInputEnable(true);

	//ジョイパッドの振動制御の0クリア
	ZeroMemory(&g_joyMoter, sizeof(XINPUT_VIBRATION));

	//振動制御の初期化
	g_nStrength = 0;
	g_nTime = 0;

	return S_OK;
}
//=========================================
//ジョイパッドの終了処理
//=========================================
void UninitJoypad(void)
{
	//Xinputのステートの設定(無効にする)
	XInputEnable(false);
}
//=========================================
//ジョイパッドの更新処理
//=========================================
void Updatejoypad(void)
{
	XINPUT_STATE joykeyState;	//ジョイパッドの入力情報
	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joyKeyStateTrigger.Gamepad.wButtons = (g_joyKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons)&joykeyState.Gamepad.wButtons;	//キーのトリガー情報保存
		g_joyKeyState = joykeyState;	//ジョイパッドのプレス情報を保存
	}

	//ジョイパッドの振動
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
//ジョイパッドのプレス情報を取得
//=========================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons&(0x01 << key)) ? true : false;
}
//=========================================
//ジョイパッドのプレス情報を取得
//=========================================
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons&(0x01 << key)) ? true : false;
}
//=========================================
//ジョイパッドのスティック情報を取得
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
//コントローラーの振動制御
//=========================================
void Joypadvibration(int nTime,int nStrength)
{
	g_nTime = nTime;			//振動持続時間
	g_nStrength = nStrength;	//振動の強さ
}