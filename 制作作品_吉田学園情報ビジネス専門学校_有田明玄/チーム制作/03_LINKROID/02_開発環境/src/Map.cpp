//=============================================================================
//
// マップ生成
// Author:arita meigen
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "Map.h"
#include "file.h"
#include "utility.h"
#include "Item_Speed.h"
#include "Item_Paint.h"
#include "Item_Bom.h"
#include "area.h"
#include "go_future_block.h"
#include "come_future_block.h"
#include "future_signs.h"
#include "teleport.h"
#include "Player.h"

//-----------------------------------------------------------------------------
// 静的メンバー変数の宣言
//-----------------------------------------------------------------------------
const float CMap::BLOCK_WIDTH = 25.0f;	// ブロック同士の幅
int CMap::m_anRanking[MAX_PLAYER];		//	ランキング順位

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap()
{
	m_nItemPopCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap::~CMap()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMap::Init()
{
	m_itemPopRandMinTime = 120;
	m_itemPopRandMaxTime = 190;
	m_nItemPopCount = IntRandom(m_itemPopRandMaxTime, m_itemPopRandMinTime);

	m_areaPopRandMinTime = 250;
	m_areaPopRandMaxTime = 250;
	m_nAreaPopCount = IntRandom(m_areaPopRandMaxTime, m_areaPopRandMinTime);
	return S_OK;
}

//=============================================================================
// 生成
//=============================================================================
void CMap::Uninit()
{
	for (int i = 0; i < GetBlockCount(); i++)
	{
		m_pBlock[i]->Release();
	}
	m_pBlock.clear();
}

//=============================================================================
// 更新
//=============================================================================
void CMap::Update()
{
	PopItem();
	PopFutureArea();
}

//=============================================================================
// 生成
//=============================================================================
CMap * CMap::Create(int stgnumber)
{
	CMap* pMap = new CMap;

	if (pMap != nullptr)
	{
		if (stgnumber != -1)
		{
			pMap->m_StageNumber = (STAGE)stgnumber;	// 読み込むマップの番号を決める
		}

		pMap->Load();	// マップの読み込み
		pMap->Init();	// 初期化
	}

	return pMap;
}

//=============================================================================
// 読み込み
//=============================================================================
void CMap::Load()
{
	using json = nlohmann::json;

	//m_StageNumberの値に応じて読み込むマップを変える
	std::string path = "data/FILE//MAP/map";
	std::string str = std::to_string((m_StageNumber + 1));
	path = path + str + ".json";
	json map = LoadJson(path);

	m_pBlock.resize(map["MAP"].size() * map["MAP"][0].size());
	m_axisSizeX = map["MAP"][0].size();

	m_playerSpawnIdx.resize(4);

	for (int i = 0; i < (int)map["MAP"].size(); i++)
	{
		for (int j = 0; j < (int)map["MAP"][i].size(); j++)
		{
			float z = i * -BLOCK_WIDTH + map["MAP"].size() * 0.5f * BLOCK_WIDTH + 25.0f;
			float x = j * BLOCK_WIDTH - map["MAP"][i].size() * 0.5f * BLOCK_WIDTH;
			D3DXVECTOR3 randomPos(FloatRandom(1000.0f, -1000.0f), 0.0f, FloatRandom(1000.0f, -1000.0f));
			D3DXVECTOR3 randomPosVec;

			D3DXVec3Normalize(&randomPosVec, &randomPos);

			//D3DXVECTOR3 randomRot(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 randomRot(randomPosVec.x * -1.0f, 0.0f, randomPosVec.z * -1.0f);
			D3DXVECTOR3 createPos(x, 0.0f, z);

			CBlock* blockCreate = nullptr;

			switch ((int)map["MAP"][i][j])
			{
			case -1:
				blockCreate = CBlock::Create(randomPos);
				blockCreate->SetRot(randomRot);
				blockCreate->SetPlanPos(createPos);
				blockCreate->SetAllColorMaterial(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				blockCreate->SetStop(true);
				break;
			case 0:
				blockCreate = CBlock::Create(randomPos);
				blockCreate->SetRot(randomRot);
				blockCreate->SetPlanPos(createPos);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			{
				blockCreate = CBlock::Create(randomPos);
				blockCreate->SetRot(randomRot);
				blockCreate->SetPlanPos(createPos);
				D3DXVECTOR2 idx;
				idx.x = (float)j;
				idx.y = (float)i;
				m_playerSpawnIdx[(int)map["MAP"][i][j]-1] = idx;
			}
				break;
			case 5:
				blockCreate = CTeleport::Create(randomPos, 5);
				blockCreate->SetRot(randomRot);
				blockCreate->SetPlanPos(createPos);
				blockCreate->SetTeleport(true);
				break;
			default:
				break;
			}

			m_pBlock[i * map["MAP"][i].size() + j] = blockCreate;
		}
	}
}

//=============================================================================
// ランキング処理
//=============================================================================
void CMap::Ranking()
{
	int Score[MAX_PLAYER] = {};
	int Rank[MAX_PLAYER] = {};	//プレイヤーの番号を渡す

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Score[i] = GetCountBlockType(i);
	}

	//昇順に並び変える
	std::vector<int> rank = { Score[0], Score[1], Score[2],Score[3] };	//スコア
	std::sort(rank.begin(), rank.end());

	for (int i = 0; i < MAX_PLAYER; i++)
	{//並び変えたやつを代入
		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (rank[i] == Score[j])
			{//ランキングの数値とプレイヤーの数値が一致している場合プレイヤーの番号を代入する
				if (Rank[0] != j&& Rank[1] != j && Rank[2] != j && Rank[3] != j)
				{//他の順位とプレイヤーの番号を被らないようにする
					Rank[i] = j;
				}
			}
		}
	}

	//Rankの中身は昇順0が最下位

	//ランキングを代入
	for (int i = 0; i < MAX_PLAYER; i++)
	{//プレイヤーの番号順に代入
		m_anRanking[Rank[MAX_PLAYER-1-i]] = i;
		if (i>=1)
		{
			if (rank[MAX_PLAYER - 1 - i] == rank[MAX_PLAYER - 1 - i + 1])
			{
				m_anRanking[Rank[MAX_PLAYER - 1 - i]] = m_anRanking[Rank[MAX_PLAYER - 1 - i + 1]];
			}
		}
	}
}

//=============================================================================
// 終了時に画面外に散開させる処理
//=============================================================================
void CMap::OpenMap()
{
	int size = m_pBlock.size();
	for (int i = 0; i < size; i++)
	{
		//m_pBlock[i]->SetPlanPos(D3DXVECTOR3(FloatRandom(-1000.0f,)));
	}
}

//=============================================================================
// プレイヤーが塗ったブロックの数を数える
//=============================================================================
int CMap::GetCountBlockType(int nType)
{
//	CBlock* AllBlock;
	for (int i = 0; i < 4; i++)
	{//リセット
		m_nAllBlock[i] = 0;
	}

	for (int i = 0; i < GetBlockCount(); i++)
	{//タイプ分け

		if (m_pBlock[i]->GetNumber() < 0)
		{
			continue;
		}

		m_nAllBlock[m_pBlock[i]->GetNumber()]++;
	}
	return m_nAllBlock[nType];
}

//=============================================================================
// アイテムの出現
//=============================================================================
void CMap::PopItem()
{
	m_nItemPopCount--;
	if (m_nItemPopCount > 0)
	{
		return;
	}

	/* ↓出現間隔が0以下↓ */

	CBlock* popPlanBlock = m_pBlock[IntRandom(m_pBlock.size() - 1, 0)];

	if (popPlanBlock->IsStop() || popPlanBlock->GetTeleport())
	{
		return;
	}

	/* ↓ランダム指定のブロックが侵入不可ブロックではない↓ */

	if (popPlanBlock->GetOnItem() != nullptr)
	{
		return;
	}

	/* ↓ランダム指定のブロックにアイテムが乗っていない↓ */

	D3DXVECTOR3 pos = popPlanBlock->GetPos();
	pos.y += 20.0f;

	//アイテムの生成
	CItem* popItem = nullptr;

	int random = IntRandom(3, 0);

	switch (random)
	{
	case 0:
		popItem = CPaint::Create(pos);
		break;
	case 1:
		popItem = CSpeed::Create(pos);
		break;
	case 2:
		popItem = CBom::Create(pos);
		break;
	default:
		break;
	}

	popPlanBlock->SetOnItem(popItem);

	// 次回出現時間の設定
	m_nItemPopCount = IntRandom(m_itemPopRandMaxTime, m_itemPopRandMinTime);
}

//=============================================================================
// 未来エリアの出現
//=============================================================================
void CMap::PopFutureArea()
{
	m_nAreaPopCount--;
	if (m_nAreaPopCount > 0)
	{
		return;
	}

	/* ↓出現間隔が0以下↓ */

	CBlock* popPlanBlock = m_pBlock[IntRandom(m_pBlock.size() - 1, 0)];

	if (popPlanBlock->IsStop())
	{
		return;
	}

	/* ↓ランダム指定のブロックが侵入不可ブロックではない↓ */

	if (popPlanBlock->GetOnItem() != nullptr)
	{
		return;
	}

	/* ↓ランダム指定のブロックにアイテムが乗っていない↓ */

	D3DXVECTOR2 popBlockIndex = GetBlockIdx(popPlanBlock);

	int range = 3;

	//エリアの生成
	CArea* area = CArea::Create(popBlockIndex, range,120,180);

	auto atBigenFutrue = [this, range, popBlockIndex]()
	{
		for (int y = 0; y < range * 2 + 1; y++)
		{
			for (int x = 0; x < range * 2 + 1; x++)
			{
				CBlock* block = GetBlock((int)(x + popBlockIndex.x - range), (int)(y + popBlockIndex.y - range));

				if (block == nullptr)
				{
					continue;
				}

				if (block->IsStop())
				{
					continue;
				}

				/* ↓block がnullではないか、壁ではない↓ */

				//if (!(block->GetNumber() < 0))
				{
					CFutureSigns* futureBlock = CFutureSigns::Create(block->GetPos());
					futureBlock->SetCol(block->GetCol());
				}
			}
		}
	};

	area->SetFunctionAtSignsBegin(atBigenFutrue);

	// 予兆終了後行なって欲しい処理
	auto atFutrue = [this, range, popBlockIndex]()
	{
		for (int y = 0; y < range * 2 + 1; y++)
		{
			for (int x = 0; x < range * 2 + 1; x++)
			{
				CBlock* block = GetBlock((int)(x + popBlockIndex.x - range), (int)(y + popBlockIndex.y - range));

				if (block == nullptr)
				{
					continue;
				}

				if (block->IsStop())
				{
					if (block->GetOnPlayer() != nullptr)
					{
						block->GetOnPlayer()->Stun(60);
					}
					continue;
				}

				/* ↓block がnullではないか、壁ではない↓ */

				//if (!(block->GetNumber() < 0))
				{
					CGoFutureBlock* futureBlock = CGoFutureBlock::Create(block->GetPos());
					futureBlock->SetCol(block->GetCol());
				}

				block->SetPlayerNumber(-2);
			}
		}
	};

	area->SetFunctionAtSignsEnd(atFutrue);

	// 未来エリアに行く予定のブロックの色を取得しとく
	std::vector<CBlock*> areaBlock;
	std::map<CBlock*, int> areaBlockIndex;

	for (int y = 0; y < range * 2 + 1; y++)
	{
		for (int x = 0; x < range * 2 + 1; x++)
		{
			CBlock* block = GetBlock((int)(x + popBlockIndex.x - range), (int)(y + popBlockIndex.y - range));

			if (block == nullptr || block->IsStop())
			{
				continue;
			}

			/* ↓block がnullではないか、壁ではない↓ */

			areaBlock.push_back(block);
			areaBlockIndex[block] = block->GetNumber();
		}
	}

	// エリア死亡時(未来エリアに行ったブロックを元に戻す時)行なって欲しい処理
	auto atDead = [this, areaBlock, areaBlockIndex]()
	{
		std::map<CBlock*, int> BlockIndex = areaBlockIndex;
		int size = areaBlock.size();
		for (int i = 0; i < size; i++)
		{
			if (BlockIndex[areaBlock[i]] != -2)
			{
				areaBlock[i]->SetPlayerNumber(BlockIndex[areaBlock[i]]);
			}
			else
			{
				areaBlock[i]->SetPlayerNumber(-1);
			}

			//if (!(areaBlock[i]->GetNumber() < 0))
			{
				CComeFutureBlock* futureBlock = CComeFutureBlock::Create(areaBlock[i]->GetPos());
				futureBlock->SetCol(areaBlock[i]->GetCol());

				if (areaBlock[i]->GetOnPlayer() != nullptr)
				{
					areaBlock[i]->GetOnPlayer()->Stun(60); //範囲内のプレイヤーをスタン
				}
			}
		}
	};

	area->SetFunctionAtDied(atDead);

	// 次回出現時間の設定
	m_nAreaPopCount = IntRandom(m_areaPopRandMaxTime, m_areaPopRandMinTime);

}

//=============================================================================
// ブロックの取得
//=============================================================================
CBlock * CMap::GetBlock(const int x, const int y)
{
	size_t idx = (m_axisSizeX * y) + x;

	if (idx < 0 || idx >= m_pBlock.size())
	{
		return nullptr;
	}

	return m_pBlock[idx];
}

//=============================================================================
// ブロックの番号取得
//=============================================================================
D3DXVECTOR2 CMap::GetBlockIdx(CBlock * block)
{
	for (int i = 0; i < (int)m_pBlock.size(); i++)
	{
		CBlock* pBlock = m_pBlock[i];

		if (pBlock == nullptr)
		{
			continue;
		}

		if (pBlock == block)
		{
			D3DXVECTOR2 idx;
			idx.y = (float)(i / m_axisSizeX);
			idx.x = (float)(i % m_axisSizeX);
			return idx;
		}
	}

	return D3DXVECTOR2(0.0f,0.0f);
}
