//=============================================================================
//
// skill_gauge.h
// Author:髙野馨將
//
//=============================================================================
#ifndef _SKILL_GAUGE_H_
#define _SKILL_GAUGE_H_

#include "object2D.h"

//スキルゲージUIクラス
class CGauge : public CObject2D
{
public:
	//定義
	static const D3DXVECTOR2 GAUGE_SIZE;	//ゲージ一つ分の大きさ
	static const float MAX_SIZE;			//ゲージの最大値
	static const float SPACE_SIZE;			//ゲージ同士の間隔の大きさ

	explicit CGauge(int nPriority = CObjectList::LEVEL_2D_UI);	//オーバーライドされたコンストラクタ
	~CGauge() override;				//デストラクタ

	//メンバ関数
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

	//静的メンバ関数
	static CGauge *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int number); //生成

private:
	//メンバ変数
	int m_nSkillNumber;			//スキルゲージの番号
};

#endif