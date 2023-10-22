//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "come_future_block.h"
#include "Item.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------

//=============================================================================
// コンストラクタ
//=============================================================================
CComeFutureBlock::CComeFutureBlock(int priorty) :CObjectX(priorty)
{
	m_number = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CComeFutureBlock::~CComeFutureBlock()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CComeFutureBlock::Init()
{
	CObjectX::Init();
	m_number = -1;

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CComeFutureBlock::Uninit()
{
	CObjectX::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CComeFutureBlock::Update()
{
	CObjectX::Update();

	D3DXVECTOR3 sizeMag = GetSizeMag();
	sizeMag += D3DXVECTOR3(0.075f, -0.075f, 0.075f);
	SetSizeMag(sizeMag);

	D3DXVECTOR3 pos = GetPos();
	pos.y -= 5.5f;
	SetPos(pos);

	if (sizeMag.x >= 1.0f)
	{
		Uninit();
	}
}

//=============================================================================
// 生成
//=============================================================================
CComeFutureBlock* CComeFutureBlock::Create(D3DXVECTOR3 pos)
{
	CComeFutureBlock* pBlock = new CComeFutureBlock(5);

	if (pBlock != nullptr)
	{
		pBlock->Init();
		pBlock->BindModel(CObjectXOriginalList::GetInstance()->Load("BLOCK", "data/MODEL/box.x"));
		D3DXVECTOR3 inpos = pos;
		inpos.y += 80.0f;
		pBlock->SetPos(inpos);
		pBlock->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pBlock->SetSizeMag(D3DXVECTOR3(0.0f, 1.5f, 0.0f));

	}
	return pBlock;
}

//=============================================================================
// プレイヤー設定
//=============================================================================
void CComeFutureBlock::SetPlayerNumber(int number)
{
	m_number = number;

	switch (m_number)
	{
	case -1:
		SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case 0:
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case 2:
		SetCol(D3DXCOLOR(0.55f, 0.55f, 0.0f, 1.0f));
		break;
	case 3:
		SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}
