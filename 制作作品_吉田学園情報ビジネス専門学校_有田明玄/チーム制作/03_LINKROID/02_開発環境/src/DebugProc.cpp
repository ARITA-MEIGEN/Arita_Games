//=============================================================================
//
// 3Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"DebugProc.h"
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include"Application.h"
#include"renderer.h"

//静的メンバ変数
LPD3DXFONT CDebugProc::m_pFont = nullptr;
std::string CDebugProc::m_aStr = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CDebugProc::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
}

//=============================================================================
// 終了
//=============================================================================
void CDebugProc::Uninit()
{
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=============================================================================
// 文字列読み込み
//=============================================================================
void CDebugProc::Print(const char * pFormat, ...)
{
	// 変数
	char aStrCpy[0xfff] = {};

	// リストの作成
	va_list args;
	va_start(args, pFormat);
	vsprintf(&aStrCpy[0], pFormat, args);
	va_end(args);

	m_aStr += aStrCpy;
}

//=============================================================================
// 描画
//=============================================================================
void CDebugProc::Draw()
{
#ifndef _DEBUG
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	D3DXCOLOR col = {1.0f,0.0f,0.0f,1.0f};

	// テキスト描画
	m_pFont->DrawText(NULL, m_aStr.c_str(), -1, &rect, DT_LEFT, col);

	//テキストリセット
	m_aStr.clear();
#endif // _DEBUG

}
