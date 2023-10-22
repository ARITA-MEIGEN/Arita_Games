//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================
#ifndef _COME_FUTURE_BLOCK_H_			// このマクロ定義がされてなかったら
#define _COME_FUTURE_BLOCK_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include"ObjectX.h"

//=============================================================================
// 構造体定義
//=============================================================================
class CComeFutureBlock : public CObjectX
{
private:
public:
	explicit CComeFutureBlock(int nPriority = 2);
	~CComeFutureBlock() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	static CComeFutureBlock *Create(D3DXVECTOR3 pos);

	// Setter
	void SetPlayerNumber(int number);

	// Getter
	int GetNumber() { return m_number; };

private:
	//メンバ変数
	int m_number;	// プレイヤーの番号
};
#endif
