//=============================================================================
//
// スコア
// Author : 有田明玄
//
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define SCORE_HEIGHT			(60.0f)		//スコアの大きさの高さ
#define SCORE_WIDTH				(30.0f)		//スコアの大きさの幅
#define RESULT_SCORE_HEIGHT		(120.0f)		//リザルトのスコアの大きさ
#define RESULT_SCORE_WIDTH		(60.0f)		//リザルトのスコアの大きさ
#define NUM_SCORE				(8)			//スコアの桁数分用意する

//前方宣言

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CScore : public CObject
{
public:
	CScore();
	~CScore()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CScore *Create(D3DXVECTOR3 pos);
	void SetPos(D3DXVECTOR3 pos,D3DXVECTOR2 siz);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore();
	void SetCol(D3DXCOLOR col);

private:
	//メンバ関数			
	static LPDIRECT3DTEXTURE9 m_apTexture;
	CObject2D*m_apObject2D[NUM_SCORE];
	int m_Score;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_siz;
	D3DXCOLOR m_col;
};

#endif // !_OBJECT_H_
