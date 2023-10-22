//=============================================================================
//
// item_paint.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _ITEM_PAINT_H_
#define _ITEM_PAINT_H_

#include "item.h"

//加速クラス
class CPaint : public CItem
{
public:
	explicit CPaint(int nPriority = 3);		// コンストラクタ
	~CPaint() override;						// デストラクタ

	HRESULT Init(void) override;			// 初期化処理
	void Update(void) override;				// 更新処理

	static CPaint* Create(const D3DXVECTOR3 pos);	// 生成処理

private:
};

#endif