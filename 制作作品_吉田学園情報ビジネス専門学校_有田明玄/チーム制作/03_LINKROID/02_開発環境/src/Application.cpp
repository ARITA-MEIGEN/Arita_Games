//=============================================================================
//
// アプリケーション
// Author : 有田明玄
//
//=============================================================================

// インクルード
#include "Application.h"
#include "renderer.h"
#include "main.h"
#include "input.h"
#include "DebugProc.h"
#include "Fade.h"
#include "sound.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Texture.h"
#include "ObjectList.h"
#include "Texture.h"
#include "SkillSelect.h"
#include "MapSelect.h"
#include "tutorial.h"

//====================================
//静的メンバ変数
//====================================
CApplication* CApplication::instance = nullptr;

//====================================
//初期化
//====================================
HRESULT CApplication::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	m_pRenderer = new CRenderer;

	//初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理に失敗した場合
		return-1;
	}

	//-------------------------------
	//キーボードとジョイパッドの生成
	//-------------------------------
	CInput::Create();
	if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//サウンド初期化
	// 音楽処理の初期化処理
	if (FAILED(CSound::GetInstance()->Init(hWnd)))
	{
		return E_FAIL;
	}

	// Textureの読込み
	m_pTexture = CTexture::GetInstance();
	m_pTexture->LoadAll();

	CObjectXOriginalList::GetInstance()->LoadAll();

	// モードの設定
	m_pFade = CFade::Create();

	// デバッグ用文字の生成
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	//スコアリセット
	ResetScore();

	return S_OK;
}

//====================================
//終了
//====================================
void CApplication::Uninit()
{
	//レンダリングクラスの破壊
	if (m_pRenderer != nullptr)
	{
		// 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// モードの終了
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// フェードの終了
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// デバッグ用文字の終了
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	// 入力処理の終了
	if (CInput::GetKey() != nullptr)
	{
		CInput::GetKey()->Uninit();
	}

	//サウンド処理の終了
	if (CSound::GetInstance() != nullptr)
	{// 終了処理
		CSound::GetInstance()->Uninit();
	}

	//テクスチャの終了
	if (CTexture::GetInstance() != nullptr)
	{// 終了処理
		CTexture::GetInstance()->UnloadAll();
		delete CTexture::GetInstance();
	}

	CObjectXOriginalList::GetInstance()->Uninit();
}

//====================================
//更新
//====================================
void CApplication::Update()
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスへのポインタ

	//ワイヤーフレーム
	if (CInput::GetKey()->Trigger(DIK_1))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (CInput::GetKey()->Trigger(DIK_2))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif // _DEBUG

	//レンダラー更新
	m_pRenderer->Update();

	//キーボードとジョイパッドの更新
	if (CInput::GetKey() != nullptr)
	{
		CInput::GetKey()->Update();
	}

	//モードごとの更新
	m_pMode->Update();

	//フェードの更新
	m_pFade->Update();
}

//====================================
//描画
//====================================
void CApplication::Draw()
{
	m_pRenderer->Draw();

	//モードごとの描画
	m_pMode->Draw();
}

//======================================================
//モードの設定
//======================================================
void CApplication::SetMode(MODE mode)
{
	//新しい画面(モード)の初期化処理
	if (m_pMode != nullptr)
	{
		CSound::GetInstance()->Stop();
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	m_mode = mode;	//現在の画面(モード)を切り替える
	CObjectList::GetInstance()->AllRelease();

	//新しい画面(モード)の初期化処理
	switch (m_mode)
	{
	case MODE_TITLE:	//タイトル画面
		m_pMode = new CTitle;
		m_pMode->Init();
		break;

	case MODE_TUTORIAL:	//マップ選択画面
		m_pMode = new CTutorial;
		m_pMode->Init();
		break;

	case MODE_MAP:	//マップ選択画面
		m_pMode = new CMapSelect;
		m_pMode->Init();
		break;

	case MODE_SKILL:	//スキル選択画面
		m_pMode = new CSkillSelect;
		m_pMode->Init();
		break;

	case MODE_GAME:		//ゲーム画面
		m_pMode = new CGame;
		m_pMode->Init();
		break;

	case MODE_RESULT:	//リザルト画面
		m_pMode = new CResult;
		m_pMode->Init();
		break;
	}
}