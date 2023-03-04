//**************************************************
// 
// obstacle_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBSTACLE_MANAGER_H_	// このマクロ定義がされてなかったら
#define _OBSTACLE_MANAGER_H_	// 二重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// クラス
//==================================================
class CObstacleManager : public CObject
{
	/* ↓定義↓ */
private:
	
	/* ↓静的メンバ関数↓ */
public:
	static CObstacleManager* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CObstacleManager();				// デフォルトコンストラクタ
	~CObstacleManager() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Game();	// ゲーム

	/* ↓メンバ変数↓ */
private:
	int m_time;		// 時間
	int m_pop;		// 出現数
	int m_interval;	// 間隔
	float m_move;	// 移動量
};

#endif // !_OBSTACLE_MANAGER_H_
