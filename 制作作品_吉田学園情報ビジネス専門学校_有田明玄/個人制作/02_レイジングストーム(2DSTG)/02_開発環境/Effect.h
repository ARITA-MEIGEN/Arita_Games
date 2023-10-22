//=============================================================================
//
// エフェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define EFFECT_HEIGHT	(35)		//プレイヤーの高さ
#define EFFECT_WIDTH	(40)		//プレイヤーの幅	
#define EFFECT_TEX		(4)			//テクスチャの枚数

//前方宣言

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CEffect : public CObject2D
{
public:
	CEffect();
	~CEffect()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 siz, float lot, D3DXVECTOR3 move, int nLife, D3DXCOLOR col);
	static HRESULT Load();
	static void Unload();

private:
	//メンバ関数
	static LPDIRECT3DTEXTURE9 m_apTexture[EFFECT_TEX];
	int m_Life;						//寿命
	D3DXVECTOR3 m_move;
	float m_alpha;					//アルファ値
};
#endif // !_OBJECT_H_


