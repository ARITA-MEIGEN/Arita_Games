//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//�C���N���[�h
#include"Application.h"

//�O���錾
class CPlayer;
class CExplosion;
class CEnemy;
class CBg;
class CScore;
class CLife;				//�̗̓Q�[�W
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
	static CLife*m_Life;				//�̗̓Q�[�W
	static CMapdata*m_pMap;
	static CSpecial*m_pSpecial;			//�K�E�Z�Q�[�W
	static CScore*m_pScore;
	static GAME m_gamestate;			//�Q�[���̏��
};

#endif 

