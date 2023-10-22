//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//include
#include "main.h"
#include "Application.h"
#include "Mode.h"
#include "Object2D.h"
#include"ObjectX.h"

#define	MAX_PLAYER	(4)		//プレイヤー人数

//前方宣言
class CPlayer;
class CCamera;
class CLight;

class CResult : public CMode
{
public:
	CResult();
	~CResult();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void ResultCamera();	//リザルト用カメラ演出

	//ゲッター
	//static CObject2D*GetBg() { return m_pBg; };
private:
	CCamera* m_pCamera;					// カメラ
	CLight* m_pLight;					// 光源
	CObject2D* m_apRank[MAX_PLAYER];	// 順位表示UI
	CPlayer* m_pPlayer[MAX_PLAYER];		// プレイヤー
	CObjectX* m_pCylinder[MAX_PLAYER];	// ランキング用の柱

	static const float RANK_WIDTH;		// ランキングのUIの設置間隔
	static const float RANK_HEIGHT;		// ランキングのUIの設置間隔

	static const float PLAYER_WIDTH;	// プレイヤーのUIの設置間隔
	static const float TOP_HEIGHT;		// 1stの高さ
	static const float PLAYER_HEIGHT;	// プレイヤー間の順位ごとの高さの間隔

};

#endif // !_OBJECT_H_



