#ifndef _INPUT_H_
#define _INPUT_H_	//二重インクルード防止用

#include "main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP=0,	//十字キー(上)
	JOYKEY_DOWN,	//十字キー(下)
	JOYKEY_LEFT,	//十字キー(左)
	JOYKEY_RIGHT,	//十字キー(右)
	JOYKEY_START,	//スタートボタン
	JOYKEY_BACK,	//バックボタン
	JOYKEY_LPUSH,	//Lスティック押し込み
	JOYKEY_RPUSH,	//Rスティック押し込み
	JOYKEY_LB,		//Lボタン
	JOYKEY_RB,		//Rボタン
	JOYKEY_NONE1,	//反応なし
	JOYKEY_NONE2,	//反応なし
	JOYKEY_A,		//Aボタン
	JOYKEY_B,		//Bボタン
	JOYKEY_X,		//Xボタン
	JOYKEY_Y,		//Yボタン
	JOYKEY_LSTICK,	//左スティック
	JOYKEY_RSTICK,	//右スティック
	JOYKEY_NONE5,	//反応なし
	JOYKEY_NONE6,	//反応なし
	JOYKEY_NONE7,	//反応なし
	JOYKEY_NONE8,	//反応なし
	JOYKEY_NONE9,	//反応なし
	JOYKEY_NONE10,	//反応なし
	JOYKEY_NONE11,	//反応なし
	JOYKEY_NONE12,	//反応なし
	JOYKEY_NONE13,	//反応なし
	JOYKEY_NONE14,	//反応なし
	JOYKEY_NONE15,	//反応なし
	JOYKEY_NONE16,	//反応なし
	JOYKEY_NONE17,	//反応なし
	JOYKEY_NONE18,	//反応なし
	//おそらく以下ループ
	JOYKEY_NONE19,	//反応なし 不具合を確認JOYKEY_UPと同じ挙動
	JOYKEY_NONE20,	//反応なし 不具合を確認JOYKEY_DOWNと同じ挙動
	JOYKEY_TEST		//テスト用
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化処理
void UninitKeyboard(void);								//キーボードの終了処理
void UpdateKeyboard(void);								//キーボードの更新処理
bool GetKeyboardPress(int nKey);						//キーボードプレス情報を取得
bool GetKeyboardTrigger(int nKey);						//キーボードトリガー情報を取得
bool GetKeyboardRelease(int nKey);						//キーボードリリース情報を取得
bool GetKeyboardRepeat(int nKey);						//キーボードリピート情報を取得
HRESULT InitJoypad(void);								//ジョイパッドの初期化処理
void UninitJoypad(void);								//ジョイパッドの終了処理
void Updatejoypad(void);								//ジョイパッドの更新処理
bool GetJoypadPress(JOYKEY key);						//ジョイパッドのプレス情報
bool GetJoypadTrigger(JOYKEY key);						//ジョイパッドのトリガー情報
D3DXVECTOR3 GetJoypadStick(JOYKEY key);					//ジョイパッドのスティック情報
void Joypadvibration(int nTime, int nStrength);			//ジョイパッドの振動設定

#endif