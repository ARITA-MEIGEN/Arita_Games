//=============================================================================
//
// item_bom.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _ITEM_BOM_H_
#define _ITEM_BOM_H_

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CBlock;

#include "item.h"

//爆弾クラス
class CBom : public CItem
{
public:
	explicit CBom(int nPriority = 3);	// コンストラクタ
	~CBom() override;					// デストラクタ

	HRESULT Init() override;		// 初期化処理
	void Update() override;			// 更新処理

	static CBom* Create(const D3DXVECTOR3 pos);	// アイテム生成処理

private:
	CBlock *m_pOnBlock;
};

#endif