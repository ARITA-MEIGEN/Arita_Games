//**************************************************
// 
// obstacle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBSTACLE_H_	//このマクロ定義がされてなかったら
#define _OBSTACLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "model.h"

//==================================================
// クラス
//==================================================
class CObstacle : public CModel
{
	/* ↓定義↓ */
public:
	
	/* ↓静的メンバ関数↓ */
public:
	static CObstacle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& rot);	// 生成

	/* ↓メンバ関数↓ */
public:
	CObstacle();			// デフォルトコンストラクタ
	~CObstacle() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetMove(const D3DXVECTOR3& move);	// 移動量の設定
	const D3DXVECTOR3& GetMove() const;		// 移動量の取得

private:
	void Shield(const D3DXVECTOR3& pos);	// シールドとの判定

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	bool m_collision;	// 当たり判定
};

#endif // !_OBSTACLE_H_
