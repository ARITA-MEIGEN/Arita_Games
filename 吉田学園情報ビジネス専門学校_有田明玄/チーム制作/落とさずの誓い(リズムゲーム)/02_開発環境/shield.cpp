//======================================================
//
// シールドの処理
// Author : Sato Teruto
//
//======================================================

//--------------------------
// インクルード
//--------------------------
#include "shield.h"
#include "input.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const float STD_SPEED = 15.0f;	// 移動量
const float POP_POS_Y = -150.0f;	// 出現のYの位置
const D3DXVECTOR3 POP_POS[] =
{// 出現の位置
	D3DXVECTOR3(-150.0f, POP_POS_Y, 100.0f),
	D3DXVECTOR3(150.0f, POP_POS_Y, 100.0f),
	D3DXVECTOR3(0.0f, POP_POS_Y, -70.0f),
};
const D3DXVECTOR3 POP_ROT[] =
{// 出現の位置
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
};
const int POP_MAX = sizeof(POP_POS) / sizeof(POP_POS[0]);	// 出現位置の最大数
}

//--------------------------------
// 静的メンバ変数宣言
//--------------------------------
bool CShield::bPop[3] = {};

//================================
// コンストラクタ
//================================
CShield::CShield()
{
	m_defaultPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//初期位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_index = 0;	//番号
}

//================================
// デストラクタ
//================================
CShield::~CShield()
{

}

//================================
// 初期化
//================================
void CShield::Init()
{
	CModel::Init();
}

//================================
// 終了
//================================
void CShield::Uninit()
{
	CModel::Uninit();
}

//================================
// 更新
//================================
void CShield::Update()
{
	CInput* pInput = CInput::GetKey();

	if (m_index == 0)
	{
		if ((pInput->Press(KEY_LEFT) || pInput->Press(JOYPAD_X)) && !bPop[1] && !bPop[2])
		{// 左
			//移動処理
			Move(m_index);
		}
		else
		{
			//移動リセット
			ResetMove(m_index);
		}
	}
	else if (m_index == 1)
	{
		if ((pInput->Press(KEY_RIGHT) || pInput->Press(JOYPAD_B)) && !bPop[0] && !bPop[2])
		{// 右
			Move(m_index);
		}
		else
		{
			ResetMove(m_index);
		}
	}
	else if (m_index == 2)
	{
		if ((pInput->Press(KEY_DOWN) || pInput->Press(JOYPAD_A)) && !bPop[0] && !bPop[1])
		{// 下
			Move(m_index);
		}
		else
		{
			ResetMove(m_index);
		}
	}

	CModel::Update();
}

//================================
// 描画
//================================
void CShield::Draw()
{
	CModel::Draw();
}

//================================
// 生成
//================================
void CShield::CreateAll()
{
	for (int i = 0; i < POP_MAX; i++)
	{
		CShield::Create(POP_POS[i], POP_ROT[i], i);
	}
}

//================================
// 生成
//================================
CShield* CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int index)
{
	CShield *pShield = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pShield = new CShield;	//生成

	if (pShield != nullptr)
	{//NULLチェック
		//初期化
		pShield->Init();

		//メンバ変数に代入
		pShield->m_defaultPos = pos;	//初期位置
		pShield->m_rot = rot;			//向き
		pShield->m_index = index;
		pShield->SetLabel(CFileXManager::LABEL_BAMBOO);	//モデル

		pShield->SetPos(pos);
		pShield->SetRot(rot);
		
	}

	return pShield;
}

//================================
// 移動処理
//================================
void CShield::Move(int index)
{
	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	bool bUp = Homing(&pos, pos, D3DXVECTOR3(m_defaultPos.x, 0.0f, m_defaultPos.z), STD_SPEED);

	// 位置の設定
	CModel::SetPos(pos);

	//出現している状態
	if (bUp == true)
	{
		bPop[index] = true;
	}
}

//================================
// 移動のリセット処理
//================================
void CShield::ResetMove(int index)
{
	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	bool bDown = Homing(&pos, pos, m_defaultPos, STD_SPEED);

	// 位置の設定
	CModel::SetPos(pos);

	//出現していない状態
	if (bDown == true)
	{
		bPop[index] = false;
	}
}

//================================
// 移動のリセット処理
//================================
int CShield::GetNumPop(int nIndex)
{
	if (bPop[nIndex] == true)
	{
		return nIndex;
	}

	return 3;
}