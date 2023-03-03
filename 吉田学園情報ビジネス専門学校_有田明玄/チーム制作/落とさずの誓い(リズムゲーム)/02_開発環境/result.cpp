//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "result.h"
#include "input.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "mode.h"
#include "mesh_field.h"
#include "domino.h"
#include "menu.h"
#include "result.h"
#include "sound.h"
#include "object3D.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	{// 背景
		m_pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(26000.0f, 0.0f, 1800.0f);
		m_pObj->SetPos(D3DXVECTOR3(320.0f, 0.0f, 0.0f));

		// サイズの設定
		m_pObj->SetSize(size);

		// テクスチャの設定
		m_pObj->SetTexture(CTexture::LAVEL_TATAMI);
	}

	//和風フレーム
	CObject2D* pFrame = CObject2D::Create();

	D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

	// 位置の設定
	pFrame->SetPos(pos);

	//サイズの設定
	pFrame->SetSize(size);

	//テクスチャの設定
	pFrame->SetTexture(CTexture::LABEL_Frame_Japan);

	CDomino::CreateAll();

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	CDomino::AddMove();

	D3DXVECTOR3 pos = m_pObj->GetPos();

	pos.x += CDomino::GetMove();

	m_pObj->SetPos(pos);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CResult::Draw()
{
}
