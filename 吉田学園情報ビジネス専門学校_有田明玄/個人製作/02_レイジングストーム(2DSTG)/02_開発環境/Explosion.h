//=============================================================================
//
// 爆発
// Author : 有田明玄
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define EXPLOSION_TEX		(2)		//画像の枚数
#define EXPLOSION_PTN		(8)		//テクスチャのパターン数
#define EXPLOSION_TIME		(2)		//一枚ごとの表示時間

//前方宣言
//=============================================================================
// 構造体定義
//=============================================================================
class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz);

private:
	//メンバ関数
	static LPDIRECT3DTEXTURE9 m_apTexture[EXPLOSION_TEX];
	int m_nAnimTimer;		//時間　タイマー
	int m_nPtnAnim;			//テクスチャの枚数
};
#endif // !_EXPLOSION_H_



