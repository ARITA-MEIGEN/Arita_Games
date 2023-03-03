//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
//インクルード
#include"main.h"
#include"Bg.h"
#include"Title.h"
#include"Application.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"Fade.h"

//静的メンバ変数
CBg*CTitle::m_pBg = nullptr;
//====================================
//コンストラクタ
//====================================
CTitle::CTitle()
{
}

//====================================
//デストラクタ
//====================================
CTitle::~CTitle()
{

}

//====================================
//初期化
//====================================
HRESULT CTitle::Init()
{
	//テクスチャの読み込み
	CBg::Load();
	//背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),CApplication::MODE_TITLE);

	return S_OK;
}

//====================================
//終了
//====================================
void CTitle::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}
	//テクスチャの破棄
	CBg::Unload();
}

//====================================
//更新
//====================================
void CTitle::Update()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

		//指定のキーが押されたかどうか
	if (pKeyboard->GetTrigger(DIK_RETURN) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) && CFade::Get() == CFade::FADE_NONE
		|| pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START)&& CFade::Get() == CFade::FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_TUTORIAL);
	}
}

//====================================
//描画
//====================================
void CTitle::Draw()
{

}

//====================================
//背景の取得
//====================================
CBg * CTitle::GetBg()
{
	return m_pBg;
}