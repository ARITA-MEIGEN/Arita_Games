//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include"main.h"
#include"Bg.h"
#include"Result.h"
#include"Score.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"sound.h"
#include"Fade.h"

//静的メンバ変数
CBg*CResult::m_pBg = nullptr;
CScore*CResult::m_pScore=nullptr;

//====================================
//コンストラクタ
//====================================
CResult::CResult()
{
}

//====================================
//デストラクタ
//====================================
CResult::~CResult()
{

}

//====================================
//初期化
//====================================
HRESULT CResult::Init()
{
	//テクスチャの読み込み
	CBg::Load();
	CScore::Load();
	//背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_RESULT);
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2-70.0f, SCREEN_HEIGHT / 2+30.5f, 0.0f), D3DXVECTOR2(RESULT_SCORE_WIDTH, RESULT_SCORE_HEIGHT));


	return S_OK;
}

//====================================
//終了
//====================================
void CResult::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	//テクスチャの破棄
	CBg::Unload();
	CScore::Unload();
}

//====================================
//更新
//====================================
void CResult::Update()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

	////文字のサイズが想定よりデカくなるバグに対しての応急処置
	//m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2 - 70.0f, SCREEN_HEIGHT / 2 + 30.5f, 0.0f), D3DXVECTOR2(RESULT_SCORE_WIDTH, RESULT_SCORE_HEIGHT));

	if ((pKeyboard->GetTrigger(DIK_RETURN) == true ||
		pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) == true && CFade::Get() == CFade::FADE_NONE)		//ENTERキー
	{//エンターでランキングに
	 //モード設定
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_RANKING);
	}
}

//====================================
//描画
//====================================
void CResult::Draw()
{

}

//====================================
//背景の取得
//====================================
CBg * CResult::GetBg()
{
	return m_pBg;
}

//====================================
//スコアの取得
//====================================
CScore*CResult::GetScore()
{
	return m_pScore;
}
