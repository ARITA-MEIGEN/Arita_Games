//=============================================================================
//
// スコア
// Author : 有田明玄
//
//=============================================================================

#ifndef _SPECIAL_H_
#define _SPECIAL_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define SPECIAL_HEIGHT		(25.0f)		//ゲージの高さ
#define SPECIAL_WIDTH		(250.0f)	//ゲージの幅
#define MAX_SPECIAL			(100.0f)	//必殺技ゲージの最大
#define NUM_TEX_SP			(2)			//テクスチャの枚数
#define RECOVERY_QUANTITY	(0.03f)		//自然回復する量

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CSpecial : public CObject
{
public:
	CSpecial();
	~CSpecial()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CSpecial *Create(D3DXVECTOR3 pos);
	static void AddSpecial(float Special);
	static float GetSpecial();

private:
	//メンバ関数			
	static CObject2D*m_apObject2D[NUM_TEX_SP];
	static LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEX_SP];
	static float m_nSpecial;
	static int m_stack;
};

#endif

