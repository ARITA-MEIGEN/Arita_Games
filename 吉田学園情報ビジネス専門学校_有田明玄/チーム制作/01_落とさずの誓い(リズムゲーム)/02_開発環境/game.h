//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CScore;

//==================================================
// クラス
//==================================================
class CGame : public CMode
{
	/* 定義 */
public:

	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
	static CScore*GetScore() { return m_pScore; };
	void EndGame();
	int GetTime();

	/* ↓メンバ変数↓ */
private:
	static CScore* m_pScore;
	int m_time;	// タイム
};

#endif // !_GAME_H_
