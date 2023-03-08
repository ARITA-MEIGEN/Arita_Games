//=============================================================================
//
// アプリケーション
// Author : 有田明玄
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include"main.h"
#include"sound.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputJoyPad;
class CGame;
class CTitle;
class CResult;
class CFade;
class CMapdata;
class CTutorial;
class CRanking;

//マクロ定義
#define SCREEN_WIDTH	(1280)		// スクリーンの幅
#define SCREEN_HEIGHT	(720)		// スクリーンの高さ
#define SLOW_SPEED		(3)			// スロー演出の際何Fごとにレンダラーが更新されるかどうか

// プロトタイプ宣言
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};

	//メンバ関数
	CApplication();
	~CApplication();
	HRESULT Init(HWND hWnd, bool bWindow,HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer*GetRenderer();
	static CInputKeyboard*GetInputKeyboard();
	static CInputJoyPad*GetInputJoypad();
	static DWORD m_dwGameStartTime;				//ゲーム開始時刻
	static DWORD m_dwGameTime;					//ゲーム経過時間
	static void DrawTime(LPD3DXFONT pFont);		//経過時間の描画
	static void SetMode(MODE mode);
	static MODE GetMode();
	static void StopTime(int frame);
	static void SlowTime(bool slow);

private:
	//メンバ変数
	static CRenderer*m_pRenderer;
	static CInputKeyboard*m_pInputKeyboard;
	static CInputJoyPad*m_pInputJoyPad;
	static MODE m_mode;
	static bool m_bEndGame;		//終了フラグ
	//画面
	static CTitle*m_pTitle;
	static CTutorial*m_pTutorial;
	static CGame*m_pGame;
	static CResult*m_pResult;
	static CRanking*m_pRank;

	static CFade*m_pFade;		//フェード
	static int m_nScore;		//スコア保存用
	static CMapdata*m_nMap;		//マップデータ読み込み
	static int m_StopTime;		
	static bool m_bSlow;
	static int m_nFrame;		//現在のフレーム

};

#endif // !_APPLICATION_H_
