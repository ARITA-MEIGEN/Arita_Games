//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================
#ifndef _AREA_H_		// このマクロ定義がされてなかったら
#define _AREA_H_		// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include"Object.h"
#include <functional>

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CObject3D;
class CAreaWarning;

//=============================================================================
// 構造体定義
//=============================================================================
class CArea : public CObject
{
public:
	explicit CArea(int nPriority = 3);
	~CArea();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw() {}
	static CArea* Create(D3DXVECTOR2 index, const unsigned int inRange, const unsigned int inSignsTime, const unsigned int inDiedTime);

	void SetFunctionAtSignsBegin(std::function<void()> inFunction) { m_functionAtSignsBegin = inFunction; }
	void SetFunctionAtSignsEnd(std::function<void()> inFunction) { m_functionAtSignsEnd = inFunction; }
	void SetFunctionAtDied(std::function<void()> inFunction) { m_functionAtDied = inFunction; }

private:
	//メンバ変数
	D3DXVECTOR2 m_centerIndex;	// 中心のブロック番号
	unsigned int m_range;		// 範囲
	unsigned int m_time;		// 時間
	unsigned int m_signsTime;	// 予兆時間

	std::function<void()> m_functionAtDied;			// 死亡時の処理
	std::function<void()> m_functionAtSignsBegin;	// 予兆始動時の処理
	std::function<void()> m_functionAtSignsEnd;		// 予兆終了時の処理

	CObject3D* m_floar;
	float m_length;
	D3DXVECTOR3 m_pos;

	CAreaWarning* m_warning;
	bool isBeginUpdate;
};

#endif
