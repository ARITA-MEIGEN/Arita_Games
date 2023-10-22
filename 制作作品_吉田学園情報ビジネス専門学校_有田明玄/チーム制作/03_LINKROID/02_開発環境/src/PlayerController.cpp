//=========================================
// 
// プレイヤーからの入力命令クラス
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "PlayerController.h"
#include "application.h"
#include "input.h"

//-----------------------------------------
// コンストラクタ
//-----------------------------------------
CPlayerController::CPlayerController(int inInputIndex)
{
	m_nInputIdx = inInputIndex;
}

//-----------------------------------------
// デストラクタ
//-----------------------------------------
CPlayerController::~CPlayerController()
{
}

//-----------------------------------------
// 初期化
//-----------------------------------------
HRESULT CPlayerController::Init()
{
	return S_OK;
}

//-----------------------------------------
// 終了
//-----------------------------------------
void CPlayerController::Uninit()
{
}

//-----------------------------------------
// 更新
//-----------------------------------------
void CPlayerController::Update()
{
}

//-----------------------------------------
// 移動
//-----------------------------------------
D3DXVECTOR3 CPlayerController::Move()
{
	CInput* input = CInput::GetKey();

	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (input == nullptr)
	{
		return moveInput;
	}

	//padの移動
	if (input->Press(KEY_UP, m_nInputIdx))
	{
		moveInput.z += 1.0f;
	}
	if (input->Press(KEY_LEFT, m_nInputIdx))
	{
		moveInput.x -= 1.0f;
	}
	if (input->Press(KEY_DOWN, m_nInputIdx))
	{
		moveInput.z -= 1.0f;
	}
	if (input->Press(KEY_RIGHT, m_nInputIdx))
	{
		moveInput.x += 1.0f;
	}

	//キーボードの移動
	if (input->Press(KEY_UP,-1))
	{
		moveInput.z += 1.0f;
	}
	if (input->Press(KEY_LEFT, -1))
	{
		moveInput.x -= 1.0f;
	}
	if (input->Press(KEY_DOWN, -1))
	{
		moveInput.z -= 1.0f;
	}
	if (input->Press(KEY_RIGHT, -1))
	{
		moveInput.x += 1.0f;
	}

	if (moveInput.x != 0.0f || moveInput.y != 0.0f)
	{
		D3DXVec3Normalize(&moveInput, &moveInput);
	}

	return moveInput;
}

//-----------------------------------------
// スキル
//-----------------------------------------
bool CPlayerController::Skill()
{
	CInput* pInput = CInput::GetKey();	//インプットの取得

	bool k = false;
	bool l = false;
	bool y = false;
	bool x = false;

	if (m_nInputIdx != -1)
	{
		y = pInput->Trigger(JOYPAD_Y, m_nInputIdx);
		x = pInput->Trigger(JOYPAD_X, m_nInputIdx);
	}
	else
	{
		k = pInput->Trigger(DIK_K);
		l = pInput->Trigger(DIK_K);
	}

	return k || l || y || x;
}

//-----------------------------------------
// 投擲
//-----------------------------------------
bool CPlayerController::Throw()
{
	CInput* pInput = CInput::GetKey();	//インプットの取得
	return 	(pInput->Trigger(DIK_G) || pInput->Trigger(JOYPAD_A, m_nInputIdx) || pInput->Trigger(JOYPAD_B, m_nInputIdx));
}
