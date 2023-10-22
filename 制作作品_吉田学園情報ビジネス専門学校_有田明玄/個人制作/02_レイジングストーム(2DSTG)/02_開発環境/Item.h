//=============================================================================
//
// アイテム
// Author : 有田明玄
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

//インクルード
#include"main.h"
#include"Object2D.h"

//マクロ定義
#define ITEM_HEIGHT		(50.0f)		//アイテムの高さ
#define ITEM_WIDTH		(50.0f)		//アイテムの幅
#define ITEM_TEX		(1)			//テクスチャの枚数

//=============================================================================
// 構造体定義
//=============================================================================
// 頂点データ
class CItem : public CObject2D
{
public:
	enum ITEMTYPE
	{
		ITEM_HEALING = 0,
		ITEM_SCOREUP,
		ITEM_MAX
	};

	CItem();												//コンストラクタ
	~CItem()override;										//デストラクタ
	HRESULT Init(float Width, float Height)override;		//初期化
	void Uninit()override;									//終了
	void Update()override;									//更新
	void Draw()override;									//描画
	static HRESULT Load();									//データを読み込み
	static void Unload();									//読み込んだデータを破棄
	static CItem *Create(ITEMTYPE nType,D3DXVECTOR3 pos);	//生成

private:
	//メンバ関数
	int m_move;
	ITEMTYPE m_ItemType;
	static int m_nItem;
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEM_TEX];
};
#endif // !_OBJECT_H_




