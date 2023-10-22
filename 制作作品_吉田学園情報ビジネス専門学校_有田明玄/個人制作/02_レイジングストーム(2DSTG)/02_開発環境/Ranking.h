#ifndef _RANKING_H_
#define _RANKING_H_

#include"main.h"
#include"fade.h"

class CScore;
class CBg;
//マクロ定義
#define MAX_RANK			(5)		//ランク数
#define NUM_RANK			(2)		//ランキングのスコア以外の数

class CRanking
{
public:
	CRanking();
	~CRanking();
	//プロトタイプ宣言
	void Init(void);			//ランキングの初期化処理
	void Uninit(void);			//ランキングの終了処理
	void Update(void);			//ランキングの更新処理
	void Draw(void);			//ランキングの描画処理
	void Set(int nScore);		//ランキングの設定
	void Load();
	void Unload();
private:
	CBg*m_apBG;
	CObject2D*m_apUI;
	CScore*m_apScore[MAX_RANK];

	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nRankUpdate ;								//更新ランクNo.
	int m_nTimerRanking;								//ランキング画面表示タイマー
	float m_fPtnrank;							//プレイヤー点滅
	int m_nCntrank;									//点滅のカウント用
};



#endif
