//======================================================
//
// シールドヘッダー
// Author : Sato Teruto
//
//======================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_	//二重インクルード防止

//-----------------------------
// インクルード
//-----------------------------
#include "model.h"

//================================
// シールドクラスの定義
//================================
class CShield : public CModel
{
public:
	CShield();		//コンストラクタ
	~CShield();		//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// ゲッター
	//------------------
	static int GetNumPop(int nIndex);

	//------------------
	// 静的メンバ関数
	//------------------
	static void CreateAll();
	static CShield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int index);

private:
	void Move(int index);		//移動
	void ResetMove(int index);	//移動リセット

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_defaultPos;	//初期位置
	D3DXVECTOR3 m_rot;			//向き
	int m_index;				//番号

	//------------------
	// 静的メンバ変数
	//------------------
	static bool bPop[3];	//出現状態
};

#endif