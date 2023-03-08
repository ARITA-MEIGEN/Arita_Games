//=============================================================================
//
// プレイヤー
// Author : 有田明玄
//
//=============================================================================

#ifndef _MAPDATA_H_
#define _MAPDATA_H_

//インクルード
#include"Application.h"

//マクロ定義
#define NUM_STAGE	(1)								//ステージ数
#define FILE_MAPDATA	"data\\TXT\\stage01.txt"	//読み込むファイル名
#define DEBUG_MAPDATA	"data\\TXT\\test.txt"		//読み込むファイル名


//前方宣言
class CEnemyManager;
//=============================================================================
// 構造体定義
//=============================================================================
class CMapdata
{
public:
	enum OBJ
	{
		OBJ_ENEMY=0,
		OBJ_ITEM,
	};
	CMapdata();
	~CMapdata();
	void Update();
	void Load();

private:
	//メンバ関数
	OBJ m_type;			//オブジェクトの種類
	D3DXVECTOR3 m_pos;	//出現座標
	int m_frame;		//出現時間
	int m_ptn;			//出現パターン
	bool bEnd;			//終了フラグ
	static CEnemyManager*m_pEManager;	//敵管理

};
#endif 



