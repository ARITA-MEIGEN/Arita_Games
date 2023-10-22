//=========================================
//
// ランキング処理
// Auther：Arita Meigen
//
//=========================================

//------------------------
// インクルード
//------------------------
#include "ranking_ui.h"
#include "input.h"
#include <math.h>
#include "application.h"
#include "renderer.h"
#include <string>
#include "Score.h"
#include <vector>
#include <algorithm>

//------------------------
// 静的メンバ変数宣言
//------------------------
int	CRankingUI::m_Score;					// 時間

//=========================================
//コンストラクタ
//=========================================
CRankingUI::CRankingUI()
{

}

//=========================================
//デストラクタ
//=========================================
CRankingUI::~CRankingUI()
{

}

//=========================================
//オブジェクトの初期化処理
//=========================================
HRESULT CRankingUI::Init()
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(550.0f, 650.0f - 109.0f*nCnt, 0.0f));
	}
	m_nflashing = 0;
	m_nflashcnt = 0;
	Load();
	Ranking();
	Save();

	return S_OK;
}

//=========================================
//オブジェクトの更新処理
//=========================================
void CRankingUI::Update()
{

	if (m_nRankUpdate!=-1)
	{
		//色の設定
		m_apScore[m_nRankUpdate]->SetCor(D3DXCOLOR(1.0f, 0.0f, 0.0f, (float)m_nflashing));
		m_nflashcnt++;
		if (m_nflashcnt %FLASH_INTER ==0)
		{
			m_nflashing = m_nflashing^1;
		}
	}
	for (int i = 0; i < MAX_RANK; i++)
	{
		m_apScore[i]->Update();
	}
}

//=========================================
//オブジェクトの終了処理
//=========================================
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (m_apScore[i] != nullptr)
		{
			m_apScore[i]->Uninit();
			m_apScore[i] = nullptr;
		}
	}
}

//=========================================
//オブジェクトのクリエイト
//=========================================
CRankingUI* CRankingUI::Create()
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}

	return pRanking;
}

//=========================================
// 最新のスコアを取得
//=========================================
void CRankingUI::SetCurrentScore(int Time)
{
	m_Score = Time;
}

//=========================================
// 保存
//=========================================
void CRankingUI::Save()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "w");		//ファイル読み込み
	const int lenLine = 1024;							//1単語の最大数
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (fp != NULL)
		{
			fprintf(fp, "%d\n", m_apScore[i]->GetScore());	//読み込んだ文字ごとに設定する
		}
	}

	fclose(fp);
}

//=========================================
// 読み込み
//=========================================
void CRankingUI::Load()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "r");		//ファイル読み込み
	const int lenLine = 1024;							//1単語の最大数
	int nrScore = 0;									//読み込み用の文字列

	for (int i = 0; i < MAX_RANK; i++)
	{//ランキングの読み込み
		if (fp != NULL)
		{
			fscanf(fp, "%d", &nrScore);			//読み込んだ文字ごとに設定する
			m_apScore[i]->SetScore(nrScore);		//設定
		}
	}

	fclose(fp);
}

//=========================================
// ランキングの並び替え
//=========================================
void CRankingUI::Ranking()
{
	//ランク外にしておく
	m_nRankUpdate = -1;
	if (m_Score >= m_apScore[0]->GetScore())
	{//最下位と比較
		m_apScore[0]->SetScore(m_Score);

		//昇順に並び変える
		std::vector<int> rank = { m_apScore[0]->GetScore(), m_apScore[1]->GetScore(), m_apScore[2]->GetScore(),
			m_apScore[3]->GetScore(), m_apScore[4]->GetScore() };
		std::sort(rank.begin(), rank.end());
		for (int i = 0; i < MAX_RANK; i++)
		{//並び変えたやつを代入
			m_apScore[i]->SetScore(rank[i]);
			if (m_Score == rank[i])
			{
				m_nRankUpdate = i;
			}
		}
	}
}