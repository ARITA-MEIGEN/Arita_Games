//=========================================
//
// ランキング処理
// Auther：Arita Meigen
//
//=========================================
#ifndef _RANKING_UI_H_		// このマクロ定義がされてなかったら
#define _RANKING_UI_H_		// 二重インク―ルード防止のマクロ定義

#include "object2D.h"

class CScore;

#define FLASH_INTER		(20)		//点滅の間隔


//=========================================
// スコアクラスを定義
//=========================================
class CRankingUI
{
public:
	CRankingUI();							//コンストラクタ
	virtual ~CRankingUI() ;				//デストラクタ

	
	HRESULT Init() ;	//初期化
	void Update() ;		//更新
	void Uninit() ;		//終了

	//クリエイト処理
	static CRankingUI* Create();

	void Save();
	void Load();
	void Ranking();

	//セッター
	static void SetCurrentScore(int Time);

private:
	static const int nMaxRank = 5;
	D3DXVECTOR3 m_pos;					// 座標
	static int	m_Score;				// 
	int			m_nRankUpdate;			//更新ランクNo.
	CScore*		m_apScore[nMaxRank];	// スコアの最大数
	int			m_nflashcnt;			//点滅用
	int			m_nflashing;			//点滅用



};

#endif

