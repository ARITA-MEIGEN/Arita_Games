//=============================================================================
//
// 空背景
// Author : YudaKaito
//
//=============================================================================
#ifndef _SKY_BG_H_
#define _SKY_BG_H_

#include "Object3D.h"

//空クラス
class CSkyBg : public CObject3D
{
public:

	explicit CSkyBg();			// コンストラクタ
	~CSkyBg() override;			// デストラクタ

	HRESULT Init() override;	// 初期化処理
	void Update() override;		// 更新処理

	static CSkyBg* Create();	// 生成処理

private:
	float m_uPos;
};

#endif