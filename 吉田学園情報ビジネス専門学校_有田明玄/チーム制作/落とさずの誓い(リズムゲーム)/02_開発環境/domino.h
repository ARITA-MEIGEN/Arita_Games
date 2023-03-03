//**************************************************
// 
// domino.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _DOMINO_H_	//このマクロ定義がされてなかったら
#define _DOMINO_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "model.h"

//==================================================
// クラス
//==================================================
class CDomino : public CModel
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ関数↓ */
private:
	static float m_move;	// 移動量
	static int m_count;		// カウント

	/* ↓静的メンバ関数↓ */
public:
	static int GetCount();	// 取得
	static void SetCount(int score);	// 設定
	static void AddCount();	// 加算
	static float GetMove();
	static void AddMove();		// 速度の加算
	static void CreateAll();	// 全ての生成
	static CDomino* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CDomino();				// デフォルトコンストラクタ
	~CDomino() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
};

#endif // !_DOMINO_H_
