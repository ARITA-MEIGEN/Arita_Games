//=========================================
//
// スコア処理
// Auther：冨所知生
//
//=========================================
#ifndef _SCORE_H_		// このマクロ定義がされてなかったら
#define _SCORE_H_		// 二重インク―ルード防止のマクロ定義

#include "object2D.h"
#include "number.h"

#define MAX_DIGITS		(2)			// スコアの桁数
#define MAX_RANK		(5)			//表示するランキングの最大数

//=========================================
// スコアクラスを定義
//=========================================
class CScore
{
public:
	CScore();							//コンストラクタ
	virtual ~CScore() ;			//デストラクタ

	//初期化処理
	void Init() ;

	//更新処理
	void Update(void) ;

	//描画処理
	void Draw(void) ;

	//終了処理
	void Uninit(void) ;

	//クリエイト処理
	static CScore* Create(const D3DXVECTOR3 &pos);

	//スコアの加算
	void Addpos() { m_nScore++; };

	//スコアの設定
	void Set();
	void SetCor(D3DXCOLOR col);
	void SetScore(int Score) { m_nScore = Score; };
	int GetScore() { return m_nScore; };
	static void AddFrag() { m_bAddflag = true; };

	//void Ranking();

private:
	D3DXVECTOR3 m_pos;					// 座標
	CNumber*	m_pNumber[MAX_DIGITS];	// ナンバー
	int			m_nScore;				// スコア
	int			m_nRankUpdate;			//更新ランクNo.
	int			m_nTimerRanking;		//ランキング画面表示タイマー
	float		m_fPtnrank;				//プレイヤー点滅
	int			m_nCntrank;				//点滅のカウント用
	static bool	m_bAddflag;				//加算フラグ

};

#endif
