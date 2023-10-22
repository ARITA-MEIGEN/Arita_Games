//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================
#ifndef _FUTURE_SIGNS_H_			// このマクロ定義がされてなかったら
#define _FUTURE_SIGNS_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include"ObjectX.h"

//=============================================================================
// 構造体定義
//=============================================================================
class CFutureSigns : public CObjectX
{
private:
public:
	explicit CFutureSigns(int nPriority = 2);
	~CFutureSigns() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	static CFutureSigns *Create(D3DXVECTOR3 pos);

	// Setter
	void SetPlayerNumber(int number);

	// Getter
	int GetNumber() { return m_number; };

private:
	//メンバ変数
	int m_number;	// プレイヤーの番号
	int m_time;
};
#endif
