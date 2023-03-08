//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルード
#include"main.h"
#include"Object2D.h"
#include<iostream>

//マクロ定義
#define PLAYER_HEIGHT		(35)		//プレイヤーの高さ
#define PLAYER_WIDTH		(40)		//プレイヤーの幅	
#define PLAYER_TEX			(2)			//テクスチャの枚数
#define PLAYER_MOVE			(8.0f)		//プレイヤーの移動量
#define PLAYER_MAXLIFE		(5)			//最大体力
#define PLAYER_DEFAULTLIFE	(3)			//初期体力
#define RED_RATE			(15)		//連射レート赤
#define BLUE_RATE			(80)		//連射レート青
#define YELLOW_RATE			(125)		//連射レート黄
#define NEXT_TIME			(60)		//死んでから次の画面に行くまでの時間

//操作関連
#define JOYPAD_UP		(pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_UP) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).y <= -1.0f)		//上
#define JOYPAD_DOWN		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_DOWN) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).y >= 1.0f)		//下
#define JOYPAD_LEFT		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_LEFT) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).x <= -1.0f)		//左
#define JOYPAD_RIGHT	(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_RIGHT) == true || pJoyPad->GetJoypadStick(CInputJoyPad::JOYKEY_LSTICK).x >= 1.0f)		//右

//射撃
#define JOYPAD_SHOT				(pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_X)||pJoyPad-> GetJoypadPress(CInputJoyPad::JOYKEY_Y))
//射撃解除
#define JOYPAD_SHOT_RELEASE		(pJoyPad->GetJoypadRelease(CInputJoyPad::JOYKEY_X)||pJoyPad->GetJoypadRelease(CInputJoyPad::JOYKEY_Y))

//前方宣言
class COption;

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CPlayer : public CObject2D
{
public:
	//プレイヤーの状態
	enum PLAYERSTATE
	{
		PLAYERSTATE_APPEAR = 0,	//出現状態(点滅)
		PLAYERSTATE_NORMAL,		//通常状態
		PLAYERSTATE_DAMAGE,		//ダメージ状態
		PLAYERSTATE_DEATH,		//死亡状態
		PLAYERSTATE_MAX
	};

	CPlayer();
	~CPlayer()override;
	HRESULT Init(float Width, float Height)override;	//初期化
	void Uninit()override;								//終了
	void Update()override;								//更新		
	void Draw()override;								//描画
	static CPlayer *Create(D3DXVECTOR3 pos);			//生成
	void Move(void);			//移動関連
	static HRESULT Load();		//テクスチャ読み込み
	static void Unload();		//破棄
	void Hit();					//当たり判定
	static int GetLife();		//体力取得
	void AutoShot();			//連射
	void Shot(int number);		//射撃
	void Offscreen();			//画面外
	void Fusion();				//合体関連
	void StateManagement();		//状態管理
	void Damage();				//ダメージ処理
	void Separation();			//分離
	PLAYERSTATE GetState();		//プレイヤーの状態


private:
	//メンバ関数
	D3DXVECTOR3 m_Move;
	static int m_nLife;			//体力が3以下の時ダメージを受けると1体づつ消えていく
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYER_TEX];
	COption*m_apOption[2];
	PLAYERSTATE m_state;
	int nCnt;
	int nCntState;
	float fPtntitle;
	int ShotTimer;
	int TriggerTimer;
	bool bFusion;		//合体管理
	bool bShot;			//合体攻撃
	int m_nRedCT;
	int m_nBlueCT;
	int m_nYellowCT;
	int m_nSpecial;		//必殺
};
#endif // !_OBJECT_H_


