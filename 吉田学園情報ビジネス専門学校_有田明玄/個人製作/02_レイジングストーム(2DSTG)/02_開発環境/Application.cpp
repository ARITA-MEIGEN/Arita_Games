//=============================================================================
//
// アプリケーション
// Author : 有田明玄
//
//=============================================================================

// インクルード
#include "Application.h"
#include"renderer.h"
#include"Object2D.h"
#include"Object.h"
#include"Bg.h"
#include"Title.h"
#include"Tutorial.h"
#include"Game.h"
#include"Result.h"
#include"Ranking.h"
#include"Fade.h"
#include"Score.h"
#include"main.h"
#include"sound.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"

//静的メンバ変数
CRenderer*CApplication::m_pRenderer = nullptr;
DWORD CApplication::m_dwGameStartTime;		//ゲーム開始時刻
DWORD CApplication::m_dwGameTime;			//ゲーム経過時間
bool CApplication::m_bEndGame;				//終了フラグ
CTitle*CApplication::m_pTitle = nullptr;
CTutorial* CApplication::m_pTutorial = nullptr;
CGame*CApplication::m_pGame=nullptr;
CResult*CApplication::m_pResult = nullptr;
CApplication::MODE CApplication::m_mode;
CFade* CApplication::m_pFade = nullptr;
int CApplication::m_nScore;
int CApplication::m_StopTime = 0;	//時間停止用
bool CApplication::m_bSlow=false;
int CApplication::m_nFrame = 0;		//現在のフレーム
CInputKeyboard*CApplication::m_pInputKeyboard = nullptr;
CInputJoyPad*CApplication::m_pInputJoyPad=nullptr;
CRanking*CApplication::m_pRank = nullptr;


//====================================
//コンストラクタ
//====================================
CApplication::CApplication()
{
}

//====================================
//デストラクタ
//====================================
CApplication::~CApplication()
{

}

//====================================
//初期化
//====================================
HRESULT CApplication::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputJoyPad = new CInputJoyPad;
	m_pFade = new CFade;

	//サウンド生成
	InitSound(hWnd);
	//ゲーム開始時間を設定
	m_dwGameStartTime = timeGetTime();

	//初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理に失敗した場合
		return-1;
	}

	//キーボードの生成
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return-1;
	}

	//キーボードの生成
	m_pInputJoyPad->Init();

	//モードの設定
	m_pFade->Init(MODE_TITLE);

	return S_OK;
}

//====================================
//終了
//====================================
void CApplication::Uninit()
{
	//キーボードの破棄
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//ジョイパッドの破棄
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Uninit();
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}

	//レンダリングクラスの破壊
	if (m_pRenderer != nullptr)
	{
		// 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//フェードの破壊
	if (m_pFade != nullptr)
	{
		// 終了処理
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	UninitSound();
}

//====================================
//更新
//====================================
void CApplication::Update()
{
	//経過時間の更新
	if (m_bEndGame == false)
	{
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}

	//キーボードの更新
	if (m_pInputKeyboard!=nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//ジョイパッド更新
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Update();
	}

	//レンダラーの更新
	if (m_pRenderer != nullptr&&m_StopTime <=0)
	{
		if (m_bSlow==true)
		{
			if (m_nFrame % SLOW_SPEED == 0)
			{
				m_pRenderer->Update();
			}
		}
		else
		{
			m_pRenderer->Update();
		}
	}

	//フェードの更新
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	switch (m_mode)
	{//画面の更新
	case MODE_TITLE:	//タイトル画面
		m_pTitle->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	case MODE_GAME:		//ゲーム画面
		m_pGame->Update();
		break;

	case MODE_RESULT:	//リザルト画面
		m_pResult->Update();
		break;

	case MODE_RANKING:
		m_pRank->Update();
		break;
	}
	m_nFrame++;
	m_StopTime--;
}

//====================================
//描画
//====================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}

//====================================
//レンダラーの取得
//====================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//====================================
//キーボードの取得
//====================================
CInputKeyboard * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//====================================
//ジョイパッドの取得
//====================================
CInputJoyPad * CApplication::GetInputJoypad()
{
	return m_pInputJoyPad;
}

//=============================================================================
// 時間表示
//=============================================================================
#ifdef _DEBUG
void CApplication::DrawTime(LPD3DXFONT pFont)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR aStr[256];

	if (m_bEndGame==false)
	{
		sprintf(aStr, _T("\n経過時間: %.1f\n"), (float)m_dwGameTime / 1000.f);
	}

	// テキスト描画
	pFont->DrawText(NULL, aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG

//======================================================
//モードの設定
//======================================================
void CApplication::SetMode(MODE mode)
{
	//新しい画面(モード)の初期化処理
	switch (m_mode)
	{
	case MODE_TITLE:	//タイトル画面
		m_pTitle->Uninit();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		break;

	case MODE_GAME:		//ゲーム画面
		m_nScore = CGame::GetScore()->GetScore();	//スコア保存
		m_pGame->Uninit();
		break;

	case MODE_RESULT:	//リザルト画面
		m_pResult->Uninit();
		break;

	case MODE_RANKING:
		m_pRank->Uninit();
		break;
	}
	CApplication::SlowTime(false);		//スロー解除
	StopSound();
	m_mode = mode;	//現在の画面(モード)を切り替える
	CObject::ReleaseAll();

	//新しい画面(モード)の初期化処理
	switch (m_mode)
	{
	case MODE_TITLE:	//タイトル画面
		m_pTitle = nullptr;
		m_pTitle = new CTitle;
		m_pTitle->Init();
		PlaySound(SOUND_LABEL_TITLE);
		break;

	case MODE_TUTORIAL:
		m_pTutorial = nullptr;
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		break;

	case MODE_GAME:		//ゲーム画面
		m_pGame = nullptr;
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:	//リザルト画面
		m_pResult = nullptr;
		m_pResult = new CResult;
		m_pResult->Init();
		CResult::GetScore()->SetScore(m_nScore);
		PlaySound(SOUND_LABEL_RESULT);
		break;

	case MODE_RANKING:
		m_pRank = nullptr;
		m_pRank = new CRanking;
		m_pRank->Init();
		m_pRank->Set(m_nScore);
		break;
	}
}

//======================================================
//現在のモードの取得
//======================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}

//======================================================
//時間停止の設定
//======================================================
void CApplication::StopTime(int frame)
{
	m_StopTime = frame;
}

//======================================================
//スロー設定
//======================================================
void CApplication::SlowTime(bool slow)
{//ON/OFF切り替え
	m_bSlow = slow;
}
