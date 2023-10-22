//=============================================================================
//
// Xファイル読み込み
// Author : 有田明玄
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルード
#include"main.h"
#include"Object.h"
#include"Command.h"
#include <vector>

//前方宣言
class CController;
class CShadow;
class CObjectX;
class CBullet;
class CBlock;
class CMotion;

//マクロ定義
#define MAX_GAUGE		(10)

class CPlayer :public CObject
{
private:
	static const std::string MOTION_PATH;	// モーションデータパス
	static const int   MAX_STOCK;			// 持てるアイテムの最大数
	static const float PLAYER_SPEED;		// 移動速度
	static const float ADD_SPEED;			// アイテムで加算するスピード
	static const float SKILL_BUFF_TIME;		// バフの効果時間(Lv1基準)
	static const int SKILL_WAVE_TIME;		// スキルの発動時間
	static const float THROW_DISTANCE;		// 投擲距離
	static const float RUSH_SPEED;			// 突進速度

public:
	enum PLAYER_STATE
	{
		PST_STAND,		// 立ち
		PST_DIE,		// 被弾状態
		PST_SPEED,		// 加速状態
		PST_PAINT,		// 塗り強化状態
		PST_KNOCKBACK,	// ノックバック強化状態
		PST_AREA,		// エリア生成状態
		PST_MAX
	};

	enum ITEM_STATE
	{
		ITEM_NONE,	// 無し
		ITEM_SPEED,	// 加速
		ITEM_PAINT,	// 塗り強化
		ITEM_MAX
	};

	enum STOCK_ITEM_STATE
	{
		STOCK_NONE,	// 無し
		STOCK_BOM,	// ボムを持っている状態
		STOCK_MAX
	};

	enum SKILL_STATE
	{
		SKILL_IDLE = 0,
		SKILL_RUSH,			// 突進
		SKILL_SPEED,		// 加速
		SKILL_BOM,			// ボム(遠距離攻撃)
		SKILL_WAVE,			// 衝撃波
		SKILL_MAX
	};

private:

	enum PLAYER_MOTION
	{
		//地上
		PM_NEUTRAL,		// ニュートラル
		PM_WALK,		// 移動
		PM_STAN,		// スタン
		PM_WIN,			// 勝利
		PM_LOSE,		// 敗北
		PM_SELECT,		// スキル選択
		PM_WAVE,		// ウェーブスキル発動時
		PM_MAX,	
		PM_INVALID = -1
	};


public:
	explicit CPlayer(int nPriority = 3);
	~CPlayer();
	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	//　プレイヤーのステート関数

	static CPlayer*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// プレイヤー生成
	static CPlayer*	Create(CBlock* block, D3DXVECTOR3 rot);	// プレイヤー生成

	// Setter
	void SetController(CController* inOperate);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };					// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };					// 向きの設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; };				// 移動の設定
	void SetSkillGauge(float skill) { m_fSkillGauge = skill; }		// スキルゲージの量の設定
	void SetTeleport(bool bTeleport) { m_bTeleport = bTeleport; }
	void SetResultMotion(int Rank);									// リザルト時のモーション再生

	void Stun(int inTime);	// 硬直の発生
	void StunNoMotion(int inTime);	// 硬直の発生

	// Getter
	D3DXVECTOR3		GetPos() { return m_pos; };
	PLAYER_MOTION	GetNowMotion() { return m_Motion; };
	D3DXMATRIX		GetMtx() { return m_mtxWorld; };				// マトリックスの取得
	float			GetSkillGauge() { return m_fSkillGauge; }		// スキルゲージの量の取得
	int				GetPlayerNumber() { return m_nPlayerNumber; }	// プレイヤーの番号の取得
	int				GetItemStock() { return m_nStockItem; }			// プレイヤーの持っているアイテムストック数
	bool			GetTeleport() { return m_bTeleport; }

private:
	void Updatepos();			// 座標の更新
	void Normalization();		// 正規化
	void BlockCollision();		// ブロックとの判定
	void TakeItem();			// アイテムを拾う
	void Item();				// アイテム処理
	void SlowlySubGauge();		// 徐々にゲージ減少
	void SubGauge();			// 一気にゲージ減少

	CBlock* OnBlock(float X,float Y);				// ブロックの情報を取得する
private:	// 静的メンバー変数
	static const UPDATE_FUNC mUpdateFunc[];
	static int		m_nNumPlayer;			// プレイヤーの数

private:	// ↓移動処理一覧↓
	void Move();	// 移動

	void TurnLookAtMoveing();	// 移動方向を見て曲がる
	void StopNoBlock();			// ブロックがない場所で停まる
	void TurnCenterBlock();		// ブロックの真ん中で曲がるようになる
	void KnockBack(CPlayer *pFastPlayer, CPlayer *pLatePlayer);			// ノックバック処理

private:	// ↓スキル処理一覧↓
	void Skill();			// スキル処理

	using SKILL_FUNC = void(CObject::*)();
	static const SKILL_FUNC m_SkillFunc[];
	void SetSkill(SKILL_STATE inState) { m_skillStateNow = inState; }

	const SKILL_FUNC* m_funcSkill;

	//　スキルのステート関数
	void Skill_Idel();
	void Skill_Speed();
	void Skill_Paint();
	void Skill_Knockback();
	void Skill_Bom();
	void Skill_Wave();
	void Skill_Rush();

	SKILL_STATE		m_skill;			// このキャラクターが仕様するスキル
	SKILL_STATE		m_skillStateNow;	// スキルステートの状態
	int				m_nSkillLv;			// プレイヤーのスキルLｖ
	int				m_nSkillBuffTime;	// スキル強化効果時間
	float			m_fSkillGauge;		// スキルゲージの量
	float			m_fSubGauge;		// スキルゲージを減算させる
	int				m_nSkillTimer;		// モーション再生からスキル発生までの時間
	int				m_nSkillCT;			// スキルのクールタイム

private:	// メンバー変数
	CController*	m_controller;			// 命令を出す人
	std::vector<CObjectX*>	m_apModel;		// モデルのインスタンス

	D3DXMATRIX		m_mtxWorld;		// ワールドマトリックス

	// 位置
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_posold;		// 前回の位置

	// 向き
	D3DXVECTOR3		m_rot;
	D3DXVECTOR3		m_rotDest;		// 目的の角度の保存

	// 移動
	D3DXVECTOR3		m_move;			// 移動量
	D3DXVECTOR3		m_moveVec;		// 移動ベクトル
	D3DXVECTOR3		m_movePlanVec;	// 移動予定ベクトル
	D3DXVECTOR2		m_direction;	// 方向

	// モーション
	PLAYER_MOTION	m_Motion;		// 現在のモーション
	CMotion*		m_motion;		// モーション

	// アイテム
	ITEM_STATE		m_ItemState;			// アイテムの状態
	int				m_nItemBuffTime;		// アイテム強化効果時間
	int				m_nStockItem;			// 持っているアイテムの数

	int				m_nPlayerNumber;		// 自分のプレイヤー番号
	int				m_nStunTime;			// スタン(操作不可能)時間
	bool			m_bKnockBack;			// ノックバックしているかどうか
	bool			m_bTeleport;			// テレポートしたかどうか
	bool			m_bMaxGauge;			// ゲージが最大までたまっているかどうか
	bool			m_bOperate;				// 操作可能かどうか
	PLAYER_STATE	m_State;				// プレイヤーの状態
	STOCK_ITEM_STATE	m_StockItemState;	// ストック式アイテムの状態
	CShadow*		m_pShadow;				// 影
	CBlock*			m_pOnBlock;				// プレイヤーの乗っているブロックへのポインタ

	//押し出し判定関連
	D3DXVECTOR3		m_aAxisSiz[PST_MAX];	// 押し出し判定の大きさ
};

#endif
