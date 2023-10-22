//=========================================
// 
// プレイヤーからの入力命令クラス
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "computerController.h"
#include "utility.h"

//-----------------------------------------
// コンストラクタ
//-----------------------------------------
CComputerController::CComputerController()
{
}

//-----------------------------------------
// デストラクタ
//-----------------------------------------
CComputerController::~CComputerController()
{
}

//-----------------------------------------
// 初期化
//-----------------------------------------
HRESULT CComputerController::Init()
{
	return S_OK;
}

//-----------------------------------------
// 終了
//-----------------------------------------
void CComputerController::Uninit()
{
}

//-----------------------------------------
// 更新
//-----------------------------------------
void CComputerController::Update()
{
}

//-----------------------------------------
// 移動
//-----------------------------------------
D3DXVECTOR3 CComputerController::Move()
{

	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int moveRandom = IntRandom(5,0);

	switch (moveRandom)
	{
	case 0:
		moveInput.x = 0.0f;
		moveInput.y = 0.0f;
		break;
	case 1:
		moveInput.x -= 1.0f;
		break;
	case 2:
		moveInput.z -= 1.0f;
		break;
	case 3:
		moveInput.x += 1.0f;
		break;
	case 4:
		moveInput.z += 1.0f;
		break;
	default:
		break;
	}

	return moveInput;
}

//-----------------------------------------
// スキル
//-----------------------------------------
bool CComputerController::Skill()
{
	return false;
}

//-----------------------------------------
// 投擲
//-----------------------------------------
bool CComputerController::Throw()
{
	return false;
}