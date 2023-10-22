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
class CExplosion;
class CEnemy;
class CBg;
class CScore;
class CLife;				//体力ゲージ
class CMapdata;
class CSpecial;
class CBoss;

class CGame
{
public:
	enum GAME
	{
		GAME_NONE=0,
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
	static CExplosion*GetExplosion();
	static CEnemy*GetEnemy();
	static CBg*GetBg();
	static CScore*GetScore();
	static void SetGame(GAME gamestate);
	static GAME GetGame();

private:								
	static CPlayer*m_pPlayer;
	static CExplosion*m_pExplosion;
	static CEnemy*m_pEnemy;
	static CBg*m_pBg;
	static CLife*m_Life;				//体力ゲージ
	static CMapdata*m_pMap;
	static CSpecial*m_pSpecial;			//必殺技ゲージ
	static CScore*m_pScore;
	static GAME m_gamestate;			//ゲームの状態
};

#endif 

