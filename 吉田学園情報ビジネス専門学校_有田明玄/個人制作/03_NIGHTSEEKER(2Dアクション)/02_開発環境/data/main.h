#ifndef _MAIN_H_						//このマクロ定義がされてなかったら
#define _MAIN_H_						//二重インクルード防止のマクロ定義

#include<windows.h>
#include"d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION	(0x800)		//ビルド時の警告対処用マクロ
#include"dinput.h"						//入力処理に必要
#include"xaudio2.h"						//サウンド処理に必要
#include"Xinput.h"						//ジョイパッド処理に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//d3d9.libの拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")		//システム時刻取得に必要
#pragma comment(lib,"dInput8.lib")		//入力処理に必要
#pragma comment(lib,"xinput.lib")		//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME			"WindowClass"							//ウィンドウクラスの名前
#define	WINDOW_CLASSNAME	"NIGHTSEEKER"							//ウィンドウの名前
#define	SCREEN_WIDTH	(1280)										//ウィンドウの幅
#define	SCREEN_HEIGHT	(720)										//ウィンドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換用係数(1.0fで固定)
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTOLIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_RANKING,	//ランキングの画面
	MODE_MAX
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
void DrawFPS(void);

#endif 




