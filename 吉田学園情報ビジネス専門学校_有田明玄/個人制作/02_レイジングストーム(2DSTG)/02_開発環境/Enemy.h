//=============================================================================
//
// 2Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define ENEMY_HEIGHT	(50.0f)		//プレイヤーの高さ
#define ENEMY_WIDTH		(50.0f)		//プレイヤーの幅
#define CANNON_HEIGHT	(100.0f)	//固定砲台の立幅
#define CANNON_WIDTH	(100.0f)	//固定砲台の横幅
#define ENEMY_TEX		(5)			//テクスチャの枚数
#define BOSS001_TEX		(5)			//最初のボスのテクスチャの枚数
#define DEFAULT_BULLETRATE	(70)	//連射レート


//前方宣言

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CEnemy : public CObject2D
{
public:
	enum MOVEPATTERN
	{//行動パターンの設定
		MOVE_000 = 0,	//右へ直線移動	
		MOVE_001,		//左へ直線移動
		MOVE_002,		//左右にくねくねしながら下に行く(最初は右に移動)
		MOVE_003,		//左右にくねくねしながら下に行く(最初は左に移動)
		MOVE_004,		//上下にくねくねしながら左から右へ(最初は下へ)
		MOVE_005,		//上下にくねくねしながら右から左へ(最初は下へ)
		MOVE_006,		//左上から右下に
		MOVE_007,		//右上から左下に
		MOVE_008,		//背景と一緒に上から下へ降りてくる(十字放火)
		MOVE_009,		//背景と一緒に上から下へ降りてくる(X字放火)
		MOVE_010,		//背景と一緒に上から下へ降りてくる通常
		MOVE_BOSS_BASE,
		MOVE_BOSS_CANNON,		//固定砲台
		MOVE_BOSS_ATCANNON,		//自機狙い
		MOVE_BOSS_CORE,
		MOVE_BOSS_CORECANNON,
		MOVE_BONUS,		//ボーナス敵　攻撃しない
		MOVE_INVALID,	//未設定
		MOVE_MAX
	};

	//プレイヤーの状態
	enum ENEMYSTATE
	{
		ENEMYSTATE_APPEAR = 0,	//出現状態　画面内に登場するまで無敵
		ENEMYSTATE_NORMAL,		//通常状態
		ENEMYSTATE_DAMAGE,		//ダメージ状態
		ENEMYSTATE_DEATH,		//死亡状態
		ENEMYSTATE_NONE,		//使っていない
		ENEMYSTATE_MAX
	};

	CEnemy();														//コンストラクタ
	~CEnemy()override;												//デストラクタ
	HRESULT Init(float Width, float Height)override;				//初期化
	void Uninit()override;											//終了
	void Update()override;											//更新
	void Draw()override;											//描画
	static HRESULT Load();											//データを読み込み
	static void Unload();											//読み込んだデータを破棄
	static CEnemy *Create(MOVEPATTERN moveptn, D3DXVECTOR3 pos);	//生成
	void SetMove();													//行動パターンの設定
	void SetMovePtn(MOVEPATTERN moveptn);							//行動パターンの指定
	void StateManagement();
	void Damage(int damage);										//ダメージ処理
	void Offscreen();												//画面外処理
	ENEMYSTATE GetState();											//状態取得
	void Shot();													//射撃
	void Lockon();
	MOVEPATTERN GetMovePtn();

private:
	//メンバ関数
	static int m_nEnemy;											//敵の数
	D3DXVECTOR3 m_move;												//移動量
	MOVEPATTERN m_Moveptn;											//行動パターン
	int m_nCnt;
	int m_nCntState;
	float m_fPtntitle;
	ENEMYSTATE m_state;												//敵の状態
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_TEX];				//テクスチャの数
	static LPDIRECT3DTEXTURE9 m_apBossTexture[BOSS001_TEX];			//テクスチャの数
	bool m_bCharge;													//チャージ演出の付与
	int m_nLife;													//体力
};
#endif // !_OBJECT_H_



