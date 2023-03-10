//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//インクルード
#include"main.h"
#include"Application.h"

//前方宣言
class CBg;

class CTitle
{
public:
	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CBg*GetBg();

private:
	static CBg*m_pBg;
};

#endif


