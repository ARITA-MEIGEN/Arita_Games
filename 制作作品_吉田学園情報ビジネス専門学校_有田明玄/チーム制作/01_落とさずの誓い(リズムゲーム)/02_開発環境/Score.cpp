//========================================================
//スコア画面の処理
//========================================================
#include "Score.h"
#include "input.h"
#include <math.h>
#include "application.h"
#include "renderer.h"
#include<string>
#include "domino.h"

//=========================================
//静的メンバ変数
//=========================================
bool CScore::m_bAddflag = false;

//=========================================
//コンストラクタ
//=========================================
CScore::CScore()
{
}

//=========================================
//デストラクタ
//=========================================
CScore::~CScore()
{

}

//=========================================
//オブジェクトの初期化処理
//=========================================
void CScore::Init()
{
	//// テクスチャの設定
	//CObject2D::SetTexture(CTexture::TEXTURE_NONE);

	for (int nCnt = 0; nCnt < MAX_DIGITS; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x - 50.0f * nCnt, m_pos.y, m_pos.z));
	}

	// クリアタイムを表示
	Set();
}

//=========================================
//オブジェクトの更新処理
//=========================================
void CScore::Update()
{
	if (m_bAddflag == true)
	{
		if (m_nScore<99)
		{
			Addpos();
		}
		m_bAddflag = false;
	}
	Set();
}

//=========================================
//オブジェクトの終了処理
//=========================================
void CScore::Uninit()
{
}

//=========================================
//オブジェクトの描画処理
//=========================================
void CScore::Draw()
{
}

//=========================================
//オブジェクトのクリエイト
//=========================================
CScore* CScore::Create(const D3DXVECTOR3 &pos)
{
	CScore* pCScore = nullptr;

	pCScore = new CScore;

	if (pCScore != nullptr)
	{
		pCScore->m_pos = pos;
		pCScore->Init();
	}

	return pCScore;
}

//=========================================
// スコアの設定処理
//=========================================
void CScore::Set()
{
	int aPosTexU[MAX_DIGITS];		//各桁の数字を格納

	for (int nCnt = 0; nCnt < MAX_DIGITS; nCnt++)
	{
		// 2桁目
		if (nCnt == 1)
		{// 分
		 // (m_Score % 10^X+1) / 10^X
			aPosTexU[nCnt] = (m_nScore/10) % 10;
			m_pNumber[nCnt]->Set(aPosTexU[nCnt]);
		}
		// 1桁目、0割が起きてしまうので↑と同時に処理できない・・・
		else if (nCnt == 0)
		{
			// (m_Score % 10^X+1) / 10^X
			aPosTexU[nCnt] = m_nScore%10;
			m_pNumber[nCnt]->Set(aPosTexU[nCnt]);
		}
	}
}

//=========================================
// スコアの色設定
//=========================================
void CScore::SetCor(D3DXCOLOR col)
{
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		m_pNumber[i]->SetCol(col);
	}
}
