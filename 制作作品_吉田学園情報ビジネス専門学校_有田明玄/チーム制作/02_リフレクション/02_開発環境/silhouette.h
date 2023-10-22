//==================================================
// silhouette.h
// Author: Buriya Kota
//==================================================
#ifndef _SILHOUETTE_H_
#define _SILHOUETTE_H_

//**************************************************
// インクルード
//**************************************************
#include "object2D.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************

//**************************************************
// 定数定義
//**************************************************

//**************************************************
// 構造体定義
//**************************************************

//**************************************************
// クラス
//**************************************************
class CSilhoette : public CObject2D
{
public:
	explicit CSilhoette(int nPriority = PRIORITY_FADE);
	~CSilhoette() override;

	HRESULT Init() override;
	void Draw(DRAW_MODE drawMode) override;

	static CSilhoette *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);

private:

};

#endif	// _SILHOUETTE_H_