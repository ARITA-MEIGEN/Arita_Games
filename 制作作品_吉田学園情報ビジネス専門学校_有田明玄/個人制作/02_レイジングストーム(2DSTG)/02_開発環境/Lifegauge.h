//=============================================================================
//
// UI
// Author : 有田明玄
//
//=============================================================================

#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define LIFE_TEX		(2)						//UIの数に応じてテクスチャを増やす
#define LIFE_POLYGON	(5)						//ポリゴン数
#define LIFE_SIZ		(25.0f)					//ポリゴンの大きさ
#define LIFEUI_SIZ_X	(75.0f)					//ポリゴンの大きさ
#define LIFEUI_SIZ_Y	(40.0f)					//ポリゴンの大きさ
#define LIFE_INTERVAL	(10.0f)					//体力同士の間隔
#define LIFE_POS_X		(300.0f)				//初期位置
#define LIFE_POS_Y		(30.0f)					//初期位置
#define LIFELOGO_POS_X	(LIFE_POS_X -60.0f)		//初期位置
#define LIFELOGO_POS_Y	(LIFE_POS_Y)			//初期位置


//前方宣言

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CLife : public CObject
{
public:
	CLife();
	~CLife()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CLife *Create();
	static void SetPos();
	static void LifeRecovery();
	static void LifeDecrease();

private:
	//メンバ関数			
	static LPDIRECT3DTEXTURE9 m_apTexture[LIFE_TEX];
	static CObject2D*m_apObject2D[LIFE_POLYGON];
	static CObject2D*m_aLifeUI;
	static int m_NumLife;
};

#endif // !_OBJECT_H_

