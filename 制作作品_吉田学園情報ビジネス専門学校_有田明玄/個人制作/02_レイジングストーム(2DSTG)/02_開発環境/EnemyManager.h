//=============================================================================
//
// 2Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//インクルード
#include"main.h"
#include"Object2D.h"
#include"Enemy.h"

#define MAX_ENEMY	(128)

class CBoss;
//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CEnemyManager
{
public:
	CEnemyManager();											//コンストラクタ
	~CEnemyManager();											//デストラクタ
	void Init();												//初期化
	void Uninit();												//終了
	void Update();												//更新
	void SetEnemy(CEnemy::MOVEPATTERN moveptn, D3DXVECTOR3 pos,int frame);	//敵の設定
	static CBoss* GetBoss();	//敵の設定

private:
	//メンバ関数
	static CBoss*m_pBoss;
	CEnemy::MOVEPATTERN m_aMoveptn[MAX_ENEMY];
	D3DXVECTOR3 m_aPos[MAX_ENEMY];
	int m_anFrame[MAX_ENEMY];
};
#endif // !_OBJECT_H_




