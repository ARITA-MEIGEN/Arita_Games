//=============================================================================
//
// ブロック生成
// Author:arita meigen
//
//=============================================================================
#ifndef _BLOCK_H_			// このマクロ定義がされてなかったら
#define _BLOCK_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include"ObjectX.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CPlayer;
class CItem;

//=============================================================================
// 構造体定義
//=============================================================================
class CBlock : public CObjectX
{
private:
	static const float SINK_LIMIT;	// 沈む制限
	static const float UP_LIMIT;	// 沈む制限
	static const float UP_POWER;	// 上がる力
	static const float DOWN_POWER;	// 下がる力
public:
	explicit CBlock();
	~CBlock() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void DeleteItem();
	static CBlock *Create(D3DXVECTOR3 pos);

	// Setter
	void SetPlayerNumber(int number);
	void SetStop(const bool isStop) { m_isStop = isStop; }
	void SetTeleport(const bool bTeleport) { m_bTeleport = bTeleport; }
	void SetOnItem(CItem* onItem) { m_onItem = onItem; }
	void SetOnPlayer(CPlayer* onPlayer) { m_onPlayer = onPlayer; }
	void SetSink(float power);
	void SetNumber(int inNumber) { m_number = inNumber; }

	void SetPlanPos(D3DXVECTOR3 inPos);

	void CancelPermitSink() { m_isSinkPermit = false; }

	void OnUpDownMove() { m_isMoveUpDown = true; m_move.y = 0.02f; }

	// Getter
	int GetNumber() { return m_number; };
	bool GetTeleport() { return m_bTeleport; };
	bool IsStop() { return m_isStop; };
	bool IsMovePermit() { return m_isMovePermit; }

	CPlayer* GetOnPlayer() { return m_onPlayer; };
	CItem* GetOnItem() { return m_onItem; };

private:
	void Move();	// 移動ギミック
	void ModifyRot();
	void UpDownMove();

private:
	//メンバ変数
	int m_number;	// プレイヤーの番号
	bool m_isStop;	// 進行不可
	bool m_bTeleport;		// テレポーターかどうか
	CPlayer* m_onPlayer;	// 乗ってるプレイヤー
	CItem* m_onItem;		// 乗ってるアイテム

	// 浮き沈み関係
	bool m_isSinkPermit;	// 沈むことを許可するか

	// 移動処理
	bool m_isMovePermit;	// 移動許可が降りてるか
	bool m_isMoveUpDown;	// 上下移動を行なうか否か
	int n_countUpDown;
	D3DXVECTOR3 m_posPlan;	// 移動予定
	D3DXVECTOR3 m_move;		// 移動ベクトル
};

#endif
