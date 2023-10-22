//======================================================
//
// bom.cpp
// Author : 髙野馨將
//
//======================================================
#include "Bom.h"
#include "Block.h"
#include "Game.h"
#include "Map.h"

//======================================================
//コンストラクタ
//======================================================
CCreateBom::CCreateBom(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CCreateBom::~CCreateBom()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CCreateBom::Init(void)
{
	//初期化
	CObjectX::Init();
	
	SetSizeMag(D3DXVECTOR3(1.5f,1.5f,1.5f));

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CCreateBom::Uninit(void)
{
	CObjectX::Uninit();
}

//======================================================
//更新処理
//======================================================
void CCreateBom::Update(void)
{
	//更新
	CObjectX::Update();

	//爆発までの時間の減算
	if (m_nLife > 0)
	{
		m_nLife--;
	}

	if (m_nLife <= 0)
	{//爆発させる
		Explosion();
		Uninit();
	}
}

//======================================================
//爆弾生成処理
//======================================================
CCreateBom *CCreateBom::Create(CBlock *pOnBlock, D3DXVECTOR3 pos, int nPlayerNumber, int nLife)
{
	//動的確保
	CCreateBom *pBom = new CCreateBom;

	if (pBom != nullptr)
	{
		//情報の設定
		pBom->Init();
		pBom->BindModel(CObjectXOriginalList::GetInstance()->GetModelData("BOM"));
		pBom->SetPos(pos);
		pBom->AddPos(D3DXVECTOR3(0.0f,20.0f,0.0f));
		pBom->m_nLife = nLife;
		pBom->m_nPlayerNumber = nPlayerNumber;
		pBom->m_pOnBlock = pOnBlock;
	}

	return pBom;
}

//======================================================
//爆発処理
//======================================================
void CCreateBom::Explosion(void)
{
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < CGame::GetMap()->GetBlockCount(); i++)
	{
		CBlock* pBlock = CGame::GetMap()->GetBlock(i);

		if (pBlock == nullptr)
		{
			continue;
		}

		//3×3の範囲を塗る
		for (int nCntY = 0; nCntY < 3; nCntY++)
		{
			for (int nCntX = 0; nCntX < 3; nCntX++)
			{
				//乗っているブロックの番号を取得
				D3DXVECTOR2 BlockIdx = CGame::GetMap()->GetBlockIdx(m_pOnBlock);
				//範囲内のブロックを塗る
				BlockIdx = D3DXVECTOR2(BlockIdx.x - 1.0f, BlockIdx.y - 1.0f);			//左上に設定する
				D3DXVECTOR2 Idx = D3DXVECTOR2(BlockIdx.x + nCntX, BlockIdx.y + nCntY);
				CBlock* Block = CGame::GetMap()->GetBlock((int)Idx.x, (int)Idx.y);

				if (Block != nullptr)
				{//ブロックを塗る
				 //Block->SetOnPlayer(this);	//プレイヤーの
					Block->SetPlayerNumber(m_nPlayerNumber);
				}
			}
		}
	}
}