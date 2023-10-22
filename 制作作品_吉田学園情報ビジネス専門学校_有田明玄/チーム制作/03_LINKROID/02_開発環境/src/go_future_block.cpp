//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "go_future_block.h"
#include "Item.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGoFutureBlock::CGoFutureBlock(int priorty) :CObjectX(priorty)
{
	m_number = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGoFutureBlock::~CGoFutureBlock()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT  CGoFutureBlock::Init()
{
	CObjectX::Init();
	m_number = -1;

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void  CGoFutureBlock::Uninit()
{
	CObjectX::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void  CGoFutureBlock::Update()
{
	CObjectX::Update();

	D3DXVECTOR3 sizeMag = GetSizeMag();
	sizeMag -= D3DXVECTOR3(0.15f,-0.05f,0.15f);
	SetSizeMag(sizeMag);

	D3DXVECTOR3 pos = GetPos();
	pos.y += 10.0f;
	SetPos(pos);

	if (sizeMag.x <= 0.0f)
	{
		Uninit();
	}
}

//=============================================================================
// 生成
//=============================================================================
CGoFutureBlock* CGoFutureBlock::Create(D3DXVECTOR3 pos)
{
	CGoFutureBlock* pBlock = new CGoFutureBlock(5);

	if (pBlock != nullptr)
	{
		pBlock->Init();
		pBlock->BindModel(CObjectXOriginalList::GetInstance()->Load("BLOCK", "data/MODEL/box.x"));
		pBlock->SetPos(pos);
		pBlock->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pBlock;
}

//=============================================================================
// プレイヤー設定
//=============================================================================
void CGoFutureBlock::SetPlayerNumber(int number)
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