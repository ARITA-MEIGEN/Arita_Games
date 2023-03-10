//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//インクルード
#include"Application.h"


//前方宣言
class CPlayer;
class CBg;
class CLife;				//体力ゲージ
class CMapdata;


class CCamera;
class CLight;
class CFloor;
class CMesh;

class CGame
{
public:
	enum GAME
	{
		GAME_NONE = 0,
		GAME_NORMAL,
		GAME_END
	};

	CGame();
	~CGame();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CPlayer*GetPlayer();
	static void SetGame(GAME gamestate);

	//ゲッター
	static GAME GetGame();
	static CCamera * GetCamera();
	static CFloor*GetFloor();
	static CMesh*GetMesh();
	static CLight*GetLight();

private:
	static CPlayer*m_pPlayer;
	static CBg*m_pBg;
	static CLife*m_Life;				//体力ゲージ
	static CMapdata*m_pMap;
	static GAME m_gamestate;			//ゲームの状態

	static CCamera*m_pCamera;
	static CLight*m_pLight;
	static CFloor*m_pFloor;
	static CMesh*m_pMesh;
};

#endif