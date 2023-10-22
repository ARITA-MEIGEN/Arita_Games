//===================================================
//
// フェードヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _FADE_H_
#define _FADE_H_	

//-------------------------------
// インクルード
//--------------------------------
#include "object.h"
#include "application.h"
#include "object2d.h"

//================================
// フェードクラスの定義
//================================
class CFade
{
public:
	//フェードの状態
	enum FADE
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX
	};

	CFade();	//コンストラクタ
	~CFade();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(CApplication::MODE modeNext);
	void Uninit();
	void Update();
	void Draw();
	void SetFade(CApplication::MODE modeNext);	//画面遷移
	void SetFade();								//画面遷移無し
	 FADE GetFade(void) { return m_fade; };
	 static CFade* Create();

	void CreateFade();
	void FadeIn();
	void FadeOut();

private:
	//------------------
	// メンバ変数
	//------------------
	FADE	  m_fade;	//フェードの状態
	D3DXCOLOR m_col;	//ポリゴン(フェード)の色
	CApplication::MODE m_modeNext;	//次の画面(モード)
	CObject2D*m_pObject;			//フェード用ポリゴン
	bool	m_bModeChange;			//切り替えるかどうか

};

#endif