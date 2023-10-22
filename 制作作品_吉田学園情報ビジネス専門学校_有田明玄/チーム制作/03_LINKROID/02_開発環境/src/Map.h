//=============================================================================
//
// マップ生成
// Author:arita meigen
//
//=============================================================================
#ifndef _MAP_H_				// このマクロ定義がされてなかったら
#define _MAP_H_				// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "Block.h"
#include "Game.h"
#include <vector>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  前方宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
class CMap
{
public:
	static const float BLOCK_WIDTH;	// ブロック同士の幅

	enum STAGE
	{
		STAGE_01=0,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_MAX
	};

	explicit CMap();
	~CMap();
	HRESULT Init();
	void Uninit();
	void Update();
	static CMap *Create(int stgnumber);
	void Load();
	void Ranking();	//ランキング
	void OpenMap();	// 終了時に画面外に散開させる処理

	//ゲッター
	CBlock* GetBlock(const int number) { return (int)m_pBlock.size() > number ? m_pBlock[number] : nullptr; };
	CBlock* GetBlock(const int x, const int y);
	D3DXVECTOR2 GetBlockIdx(CBlock* block);
	CBlock* GetPlayerSpawnBlock(const int index) { return GetBlock((int)m_playerSpawnIdx[index].x, (int)m_playerSpawnIdx[index].y); }
	int GetBlockCount() { return (int)m_pBlock.size(); };
	int CMap::GetCountBlockType(int nType);
	static int GetRanking(int number) { return m_anRanking[number]; };

private:
	void PopItem();
	void PopFutureArea();
private:
	//メンバ関数
	STAGE m_StageNumber;
	std::vector<CBlock*> m_pBlock;
	int m_nAllBlock[5];
	std::vector<D3DXVECTOR2> m_playerSpawnIdx;
	int m_axisSizeX;
	static int m_anRanking[MAX_PLAYER];	//	ランキング順位

	// Item関連
	int m_nItemPopCount;
	int m_itemPopRandMinTime;	// アイテム再出現時間の最低値
	int m_itemPopRandMaxTime;	// アイテム再出現時間の最大値

	// Area関連
	int m_nAreaPopCount;
	int m_areaPopRandMinTime;	// エリア再出現時間の最低値
	int m_areaPopRandMaxTime;	// エリア再出現時間の最大値

};

#endif