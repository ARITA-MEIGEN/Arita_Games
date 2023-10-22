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

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CRenderer;
class CTexture;
class CDebugProc;
class CMode;
class CFade;

static const int MAX_POLYGON = 1920;	// ポリゴンの最大数
static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

// プロトタイプ宣言
class CApplication
{
public:

	enum MODE
	{//ゲームモード
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_MAP,
		MODE_SKILL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	};

	// 生成済みのインスタンスがなければ新規作成:
	static CApplication* getInstance()
	{
		if (instance == nullptr) instance = new CApplication(); return instance;
	}

	//メンバ関数
	~CApplication() = default;
	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	// Setter
	void SetMode(MODE mode);

	// Getter
	CRenderer*GetRenderer() { return m_pRenderer; };
	CDebugProc* GetDebugProc() { return m_pDebugProc; };
	CFade* GetFade() { return m_pFade; }

	// 変更予定
	void SetWinner(int win) { m_nWinner = win; };	// 勝ったプレイヤーの番号
	void AddScore(int player) { CApplication::getInstance()->m_nScore[player]++; };	// スコアの加点
	void ResetScore() { CApplication::getInstance()->m_nScore[0] = 0, CApplication::getInstance()->m_nScore[1] = 0; };	// スコアのRESET
	int GetWinner() { return m_nWinner; };
	int GetScore(int player) { return CApplication::getInstance()->m_nScore[player]; };	// スコアの取得
	MODE GetModeState() { return m_mode; }

private:
	CApplication() = default;

	static CApplication* instance;

	//メンバ変数
	CRenderer* m_pRenderer;
	CTexture* m_pTexture;		// テクスチャ情報
	CDebugProc* m_pDebugProc;	// デバッグ表示
	MODE m_mode;
	CFade* m_pFade;
	int m_nWinner;
	int m_nScore[2];

	//画面
	CMode* m_pMode;
};
#endif // !_APPLICATION_H_
