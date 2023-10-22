//=============================================================================
//
// マップ選択
// Author : 髙野馨將
//
//=============================================================================
#ifndef _MAPSELECT_H_
#define _MAPSELECT_H_

//インクルード
#include "main.h"
#include "Application.h"
#include "Mode.h"
#include "Object2D.h"
#include "Game.h"
#include "Map.h"

//前方宣言
class CCamera;
class CLight;

class CMapSelect : public CMode
{
public:

	CMapSelect();
	~CMapSelect();

	HRESULT Init();			// 初期化
	void Uninit();			// 終了
	void Update();			// 更新
	void Draw();			// 描画

	void Input();			// 入力
	void Select();			// 選択処理

	static int GetMapNumber() { return m_nMapNumber; }

private:
	static int m_nMapNumber;						// 現在選択されているマップの番号
	bool m_bMapChange;								// マップを変更したかどうか
	CObject2D* m_pObj2DPolygon[(CMap::STAGE_MAX)];	// マップ選択
	CCamera* m_pCamera;								// カメラ
	CLight* m_pLight;								// 光源
	CMap* m_pMap;									// マップ
};

#endif