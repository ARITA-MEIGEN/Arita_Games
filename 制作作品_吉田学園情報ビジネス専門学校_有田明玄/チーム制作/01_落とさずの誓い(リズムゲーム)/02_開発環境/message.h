//===================================================
//
// メッセージヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "object2d.h"

//================================
// メッセージクラス
//================================
class CMessage : public CObject2D
{
public:
	CMessage();				//コンストラクタ
	~CMessage() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ変数
	//------------------
	static CMessage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// 定数
	//------------------
	static const int nDeathTime = 120;

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXCOLOR m_col;	//色
	int m_nCntTime;		//時間カウント
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif