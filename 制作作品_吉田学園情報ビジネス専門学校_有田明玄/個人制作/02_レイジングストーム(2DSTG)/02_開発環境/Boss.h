//=============================================================================
//
// 2Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _BOSS_H_
#define _BOSS_H_

//インクルード
#include"main.h"

//マクロ定義
#define MAX_CANNON		(4)
#define MAX_ATCANNON	(4)
#define MAX_CORE		(4)
#define MAX_BOSSLIFE	(5)
#define NEXT_BOSS_TIME	(60)		//死んでから次の画面に行くまでの時間


//前方宣言
class CEnemy;
//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CBoss :CObject
{
public:
	enum BOSSSTATE
	{
		BOSSSTATE_APPEAR = 0,	//出現状態　画面内に登場するまで無敵
		BOSSSTATE_NORMAL,		//生存状態
		BOSSSTATE_DEATH,		//死亡状態
		BOSSSTATE_NONE,			//使っていない
		BOSSSTATE_MAX
	};

	CBoss();												//コンストラクタ
	~CBoss();												//デストラクタ
	HRESULT Init(float Width, float Height);				//初期化
	void Uninit();											//終了
	void Update();											//更新
	void Draw();											//描画
	static CBoss *Create();									//生成
	void CoreDamage();										//コアが破壊されたときのダメージ処理
	void StateManager();									//状態管理
	void InScreen();		
	void SetPos();
	static CBoss::BOSSSTATE GetState();						
	int GetLife();

private:
	//メンバ関数
	CObject2D*m_pBossbase;
	CEnemy*m_apBossCannon[MAX_CANNON];						//固定砲台
	CEnemy*m_apBossATCannon[MAX_ATCANNON];					//自機狙い
	CEnemy*m_pBossCoreCannon;								//コアから出るビームキャノン
	CEnemy*m_apBossCore[MAX_CORE];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nLife;											//体力
    static BOSSSTATE m_BossState;
	int m_time;

};
#endif // !_OBJECT_H_




