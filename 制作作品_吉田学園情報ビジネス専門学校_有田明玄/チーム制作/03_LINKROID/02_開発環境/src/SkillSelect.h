//=============================================================================
//
// スキル選択
// Author : 髙野馨將
//
//=============================================================================
#ifndef _SKILLSELECT_H_
#define _SKILLSELECT_H_

//インクルード
#include "main.h"
#include "Application.h"
#include "Mode.h"
#include "Object2D.h"
#include "Game.h"
#include "Player.h"
#include <vector>

//前方宣言
class CPlayer;
class CCamera;
class CLight;
class CBg;

class CSkillSelect : public CMode
{
public:

	CSkillSelect();
	~CSkillSelect();

	HRESULT Init();			// 初期化
	void Uninit();			// 終了
	void Update();			// 更新
	void Draw();			// 描画

	static bool GetComputer(int nCntPlayer) { return m_isDecision[nCntPlayer]; }
	static int GetSelectSkill(int nCntPlayer) { return m_nSkill[nCntPlayer]; }
	static int GetEntryInput(int nCntPlayer) { return m_inputNumber[nCntPlayer]; }

private:
	void SetUpSelectUI(int inPlayerCnt);

	void Input();			// 入力
	void Texture();			// テクスチャを変える
	void Entry();			// エントリー
private:
	static int m_nSkill[MAX_PLAYER];				// 現在選択されているスキルの番号
	static std::vector<int> m_inputNumber;			// エントリーしたinput番号
	static bool m_isDecision[MAX_PLAYER];			// 決定中
	bool m_isPlayerCheck[MAX_PLAYER];				// 準備完了かどうか
	CObject2D* m_pObj2D[MAX_PLAYER];				// スキル選択の枠
	CObject2D* m_pSelectArrow[MAX_PLAYER][2][2];	// スキル選択中の矢印
	CPlayer* m_pPlayer[MAX_PLAYER];					// プレイヤー

	CBg* m_pBg;				// 背景
	CCamera* m_pCamera;		// カメラ
	CLight* m_pLight;		// 光源
	CPlayer::SKILL_STATE m_state;	// 状態
};

#endif