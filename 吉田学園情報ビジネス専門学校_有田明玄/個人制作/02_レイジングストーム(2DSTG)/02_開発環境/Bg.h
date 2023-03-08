//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

#ifndef _BG_H_
#define _BG_H_

//インクルード
#include"main.h"
#include"Object2D.h"
#include"Application.h"

//マクロ定義
#define NUM_TEXBG		(7)			//背景のテクスチャの枚数
#define NUM_TITLEBG		(2)			//背景のテクスチャの枚数
#define NUM_GAMEBG		(3)			//ゲームの背景のテクスチャの枚数
#define NUM_RESULTBG	(1)			//リザルトの背景のテクスチャの枚数
#define BG_SPEED		(-0.0008f)	//背景の速度
#define BG_FLASH		(0.02f)		//タイトルロゴの点滅速度
#define MAX_BG			(3)			//ポリゴンの数

//=============================================================================
// 構造体定義
//=============================================================================
class CBg : public CObject
{
public:
	CBg();
	~CBg()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CBg *Create(D3DXVECTOR3 pos, CApplication::MODE Bgptn);
	void SetPos(D3DXVECTOR3 pos);
	void Mode();
	void Colchange();	//色変更


private:
	//メンバ関数			
	static LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXBG];
	 CObject2D*m_apObject2D[MAX_BG];
	 CApplication::MODE m_BgPtn;		//背景パターン
	 D3DXVECTOR3 m_Pos;
	 D3DXVECTOR3 m_Move;
	 float m_fAlpha;
	 bool m_bflash;	//アルファ値調整用

};
#endif // !_OBJECT_H_


