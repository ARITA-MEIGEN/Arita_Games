//=============================================================================
//
// 時間
// Author : 有田明玄
//
//=============================================================================

#ifndef _TIME_H_
#define _TIME_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define	DEFAULT_TIME (3)

class CTimer
{
public:
	explicit CTimer(int nPriority = 3);
	~CTimer();
	//プロトタイプ宣言
	HRESULT			Init();
	void			Uninit();
	void			Update();
	void			Draw();
	static CTimer* Create(const int inTimer);

	void SetPos(const D3DXVECTOR3& inPos);

	//ゲッター
	int GetTimer() { return m_nTimer; };

private:

	D3DXVECTOR3 m_pos;
	CObject2D* m_apNumber[2];

	int m_nTimer;
	int m_nCreateTimer;
};
#endif

