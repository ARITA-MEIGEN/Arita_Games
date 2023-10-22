//=============================================================================
//
// item_speed.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _ITEM_SPEED_H_
#define _ITEM_SPEED_H_

#include "item.h"

//加速クラス
class CSpeed : public CItem
{
public:
	explicit CSpeed(int nPriority = 3);		// コンストラクタ
	~CSpeed() override;						// デストラクタ

	HRESULT Init(void) override;			// 初期化処理
	void Update(void) override;				// 更新処理

	static CSpeed* Create(const D3DXVECTOR3 pos);	// 生成処理

private:
};

#endif