//=============================================================================
//
// 時間
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _POUSE_UI_H_
#define _POUSE_UI_H_

//インクルード
#include"Object.h"

// 前方宣言
class CObject2D;

class CPouseUI : public CObject
{
private:
	static const D3DXVECTOR2 BUTTON_SIZE;	//ボタンのサイズ

public:
	explicit CPouseUI();
	~CPouseUI();

	//プロトタイプ宣言
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw() { }

	static CPouseUI* Create();

	void NextBotton();
	void BackBotton();

	int Exit();
	int AnySelectIndex() { m_bottonIndex; }

private:

	CObject2D* m_bg;
	CObject2D* m_buttonBg;		// button背景
	CObject2D* m_exitButton;	// 出るbutton
	CObject2D* m_backButton;	// 戻るbutton
	CObject2D* m_replayButton;	// リプレイbutton
	int m_bottonIndex;
};
#endif

