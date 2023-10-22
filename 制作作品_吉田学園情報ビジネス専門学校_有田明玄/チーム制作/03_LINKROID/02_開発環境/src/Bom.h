//=============================================================================
//
// bom.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CBlock;

#include "objectX.h"

//爆弾クラス
class CCreateBom : public CObjectX
{
public:
	explicit CCreateBom(int nPriority = 3);	// コンストラクタ
	~CCreateBom() override;					// デストラクタ

	HRESULT Init() override;		// 初期化処理
	void Uninit() override;			// 終了処理
	void Update() override;			// 更新処理
	void Explosion();				// 爆発処理

	static CCreateBom* Create(CBlock *pOnBlock, D3DXVECTOR3 pos, int nPlayerNumber, int nLife);			// 爆弾生成処理

private:
	CBlock*		m_pOnBlock;			// 乗っているブロックの情報
	int			m_nPlayerNumber;	// プレイヤーの番号
	int			m_nLife;			// 爆発までの時間
};

#endif