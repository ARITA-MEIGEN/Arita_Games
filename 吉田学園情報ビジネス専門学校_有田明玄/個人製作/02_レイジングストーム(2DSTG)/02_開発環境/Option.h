//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

#ifndef _OPTION_H_
#define _OPTION_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define OPTION_HEIGHT	(35)		//プレイヤーの高さ
#define OPTION_WIDTH	(40)		//プレイヤーの幅	
#define OPTION_TEX		(2)			//テクスチャの枚数
#define OPTION_MEMPOS	(60)		//記憶する位置座標の数
#define MAX_OPTION		(2)			//オプションの最大数

//前方宣言

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class COption : public CObject2D
{
public:
	COption();
	~COption()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static COption *Create(D3DXVECTOR3 pos);
	static HRESULT Load();						//テクスチャの読み込み
	static void Unload();						//テクスチャの破棄
	static void MemPos(D3DXVECTOR3 posold);		//プレイヤーの座標を保存する
	static void ResetPos(D3DXVECTOR3 posold);

private:
	//メンバ関数
	static D3DXVECTOR3 m_PlayerPosOld[OPTION_MEMPOS];			//プレイヤーの座標を保存
	static LPDIRECT3DTEXTURE9 m_apTexture[OPTION_TEX];	
	int m_nId;						//識別番号
	static int  m_nNumOption;		//全体の数
};
#endif // !_OBJECT_H_


