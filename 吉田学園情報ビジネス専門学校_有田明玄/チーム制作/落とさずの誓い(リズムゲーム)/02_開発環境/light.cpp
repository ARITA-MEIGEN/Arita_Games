//**************************************************
// 
// light.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "light.h"
#include "application.h"
#include "utility.h"

//==================================================
// 静的メンバ変数
//==================================================
CLight* CLight::m_pLight[MAX_LIGHT] = {};

//--------------------------------------------------
// 全ての生成
//--------------------------------------------------
CLight** CLight::CreateAll()
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(0.2f, -0.8f, 0.4f);

		// ライトの生成
		m_pLight[0] = CLight::Create(0, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

		// ライトの生成
		m_pLight[1] = CLight::Create(1, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);

		// ライトの生成
		m_pLight[2] = CLight::Create(2, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	return m_pLight;
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CLight::ReleaseAll()
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (m_pLight[i] != nullptr)
		{// nullチェック
			// 終了
			m_pLight[i]->Uninit();
			delete m_pLight[i];
			m_pLight[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CLight* CLight::Get(int num)
{
	assert(num >= 0 && num < MAX_LIGHT);

	return m_pLight[num];
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CLight* CLight::Create(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec)
{
	CLight* pLight = new CLight;

	if (pLight == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pLight->Init();

	// 設定
	pLight->Set(index, type, col, vec);

	return pLight;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CLight::CLight()
{
	memset(&m_light, 0, sizeof(m_light));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CLight::~CLight()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CLight::Init()
{
	memset(&m_light, 0, sizeof(m_light));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CLight::Uninit()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CLight::Update()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CLight::Set(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	m_light.Type = type;
	m_light.Diffuse = col;

	D3DXVECTOR3 vecDir = vec;	// ライトの方向ベクトル

	// 正規化
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(index, &m_light);

	// ライトを有効にする
	pDevice->LightEnable(index, true);
}

//--------------------------------------------------
// 方向の取得
//--------------------------------------------------
D3DXVECTOR3 CLight::GetDir()
{
	return (D3DXVECTOR3)m_light.Direction;
}
