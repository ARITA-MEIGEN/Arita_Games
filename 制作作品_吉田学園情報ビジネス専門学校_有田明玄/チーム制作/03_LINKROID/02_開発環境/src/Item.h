//=============================================================================
//
// item.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "Object3D.h"

class CObjectX;

//アイテムクラス
class CItem : public CObject3D
{
public:
	static const float BUFF_TIME;	// アイテムバフの効果時間
private:
	static const int LIMIT_DISPLAY;	// 点滅を始める時間

public:
	enum ITEM_EFFECT
	{
		NONE,	// 無し
		SPEED,	// 加速
		PAINT,	// 塗り強化
		BOM,	// ボムを持っている状態
		MAX
	};

	explicit CItem(int nPriority = 3);	// コンストラクタ
	~CItem() override;					// デストラクタ

	HRESULT Init(void) override;		// 初期化処理
	void Uninit(void) override;			// 終了処理
	void Update(void) override;			// 更新処理
	void Draw(void) override;			// 描画処理

	void SetSizePlan(const D3DXVECTOR3& inSize) { m_sizePlan = inSize; }	// 大きさ予定の設定
	void SetLife(int nLife) { m_nLife = nLife; }							// 表示時間の設定
	void SetEffect(ITEM_EFFECT effect) { m_effect = effect; }				// エフェクトの設定

	int GetLife(void) { return m_nLife; }							// 表示時間の取得
	ITEM_EFFECT GetEffect(void) { return m_effect; }				// エフェクトの取得

private:
	//メンバ変数
	bool m_bDisplay;		// 表示するかどうか
	int m_nLife;			// 表示時間
	ITEM_EFFECT m_effect;	// 効果

	// 出現演出用
	D3DXVECTOR3 m_sizePlan;	// 大きさ予定
	CObjectX* m_box;
};

#endif