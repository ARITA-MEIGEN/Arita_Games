//======================================================
//
// Item.cpp
// Author : 髙野馨將
//
//======================================================
#include "Item.h"
#include "Texture.h"
#include "Application.h"
#include "renderer.h"
#include "ObjectX.h"

//======================================================
// 定義
//======================================================
const float CItem::BUFF_TIME = 300;		// アイテムバフの効果時間
const int CItem::LIMIT_DISPLAY = 120;	// 点滅を始める時間

//======================================================
//コンストラクタ
//======================================================
CItem::CItem(int nPriority) : CObject3D(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CItem::~CItem()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CItem::Init(void)
{
	OnBillboard();

	//初期化
	m_effect = NONE;
	m_nLife = 0;
	m_bDisplay = true;
	CObject3D::Init();

	m_box = CObjectX::Create();
	m_box->BindModel(CObjectXOriginalList::GetInstance()->GetModelData("ITEM_BOX"));

	SetSizePlan(D3DXVECTOR3(25.0f,0.0f, 25.0f));
	SetRot(D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f));
	SetLife(450);
	SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f));

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CItem::Uninit(void)
{
	//終了
	CObject3D::Uninit();

	m_box->Uninit();
}

//======================================================
//更新処理
//======================================================
void CItem::Update(void)
{
	m_box->SetPos(GetPos());
	m_box->AddRot(D3DXVECTOR3(0.01f,0.01f,0.01f));
	m_box->SetCol(D3DXCOLOR(1.0f,0.0f,0.0f,0.65f));

	//表示時間の取得
	int nLife = GetLife();

	//表示時間の減算
	if (nLife >= 0)
	{
		nLife--;
	}

	if (nLife <= LIMIT_DISPLAY)
	{//表示時間が一定以下になったら点滅させる
		m_bDisplay = false;
	}

	//表示時間の設定
	SetLife(nLife);

	if (m_sizePlan.x > GetSiz().x)
	{
		D3DXVECTOR3 addSize = GetSiz() + D3DXVECTOR3(1.5f, 0.0f, 1.5f);

		if (addSize.x >= m_sizePlan.x)
		{
			addSize = m_sizePlan;
		}

		SetSiz(addSize);
	}

#if 1	// 上下移動
	D3DXVECTOR3 pos = GetPos();
	float add = sinf(nLife / 20.0f) * 0.25f;
	pos.y += add;

	SetPos(pos);
#endif // 0

	//更新
	CObject3D::Update();
}

//======================================================
//描画処理
//======================================================
void CItem::Draw(void)
{
	if (!m_bDisplay)
	{
		m_box->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
		if (GetLife() % 10 <= 5)
		{//点滅させる
		 //描画
			m_box->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f));
			CObject3D::Draw();
		}
	}
	else
	{
		//描画
		CObject3D::Draw();
	}
}