//=============================================================================
//
// 時間
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _START_UI_H_
#define _START_UI_H_

//インクルード
#include"Object2D.h"

class CStartUI : public CObject2D
{
public:
	explicit CStartUI();
	~CStartUI();

	//プロトタイプ宣言
	HRESULT Init();
	void Update();

	static CStartUI* Create();

private:
private:
	int m_nDisplayTimer;
};
#endif

