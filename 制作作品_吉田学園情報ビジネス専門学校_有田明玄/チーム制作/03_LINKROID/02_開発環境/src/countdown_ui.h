//=============================================================================
//
// 時間
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _COUNTDOWN_UI_H_
#define _COUNTDOWN_UI_H_

//インクルード
#include"Object2D.h"

class CCountDownUI : public CObject2D
{
public:
	explicit CCountDownUI();
	~CCountDownUI();

	//プロトタイプ宣言
	HRESULT Init();
	void Uninit();
	void Update();

	static CCountDownUI* Create(const int inTimer);

	//ゲッター
	int GetTimer() { return m_nTimer; };

private:
	void ScaleMoveDecoration();	// 数が減る度にスケールが変化する
private:
	int m_nTimer;
	int m_nCreateTimer;
};
#endif

