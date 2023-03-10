//=============================================================================
//
// アイテム
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Item.h"
#include"renderer.h"
#include"Application.h"

//静的メンバ変数宣言	
int CItem::m_nItem = 0;								//敵の数
LPDIRECT3DTEXTURE9 CItem::m_apTexture[ITEM_TEX] = {};	//テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem() :CObject2D(4)
{
	m_nItem++;
	SetObjType(OBJTYPE_ITEM);
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
	m_nItem--;
	SetObjType(OBJTYPE_INVALID);	//未使用にする　
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CItem::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	CObject2D::BindTexture(m_apTexture[0]);	//テクスチャの設定
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CItem::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CItem::Update()
{
	CObject2D::Update();
	D3DXVECTOR3 pos = GetPos();
	pos.y += 1.0f;
	SetPos(pos);
}

//=============================================================================
// 描画
//=============================================================================
void  CItem::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CItem::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item000.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CItem::Unload()
{
	for (int i = 0; i < ITEM_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();	
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 敵生成
//=============================================================================
CItem* CItem::Create(ITEMTYPE nType,D3DXVECTOR3 pos)
{
	CItem*pItem;
	pItem = new CItem;
	if (pItem != nullptr)
	{
		pItem->SetPos(pos);
		pItem->m_ItemType = nType;
		pItem->Init(ITEM_WIDTH, ITEM_HEIGHT);
	}
	return pItem;
}
