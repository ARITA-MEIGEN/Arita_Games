//=========================================
// 
// computerがプレイヤーを操作するのクラス
// Author YudaKaito
// 
//=========================================
#ifndef _COMPUTER_CONTROLLER_H_
#define _COMPUTER_CONTROLLER_H_

#include "controller.h"

//-----------------------------------------
// 前方宣言
//-----------------------------------------
class CMap;

//-----------------------------------------
// コンピューターコントローラークラス
//-----------------------------------------
class CComputerController : public CController
{
public:
	CComputerController();
	~CComputerController() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	D3DXVECTOR3 Move() override;
	bool Skill() override;
	bool Throw() override;
private:

private:
	CMap* m_mapInfo;	// 盤面の状況情報
};
#endif // !_PLAYER_OPERATE_H_