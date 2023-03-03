//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include "Object.h"
#include"Application.h"
#include"renderer.h"

//静的メンバ変数宣言
 CObject*CObject::m_apObject[MAX_TYPE][MAX_POLYGON];
 int CObject::m_nNumAll=0;
//=============================================================================
// コンストラクタ
//=============================================================================
 CObject::CObject(int nPriority /*=3*/)
 {
	 for (int i = 0; i < MAX_POLYGON; i++)
	 {
		 if (m_apObject[nPriority][i] == nullptr)
		 {
			 m_apObject[nPriority][i] = this;
			 m_nID = i;
			 m_nNumAll++;
			 m_nPriority = nPriority;
			 break;
		 }
	 }
 }

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
	m_nNumAll--;
}

//=============================================================================
//全ての終了
//=============================================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_TYPE; i++)
	{
		for (int j = 0; j < MAX_POLYGON; j++)
		{
			if (m_apObject[i][j] != nullptr&&m_apObject[i][j]->m_nPriority!= OBJTYPE_FADE)
			{
				m_apObject[i][j]->Uninit();
			}
		}
	}
}

//=============================================================================
//全ての更新
//=============================================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_TYPE; i++)
	{
		for (int j = 0; j < MAX_POLYGON; j++)
		{
			if (m_apObject[i][j] != nullptr)
			{
				m_apObject[i][j]->Update();
			}
		}
	}
}

//=============================================================================
// 全ての描画
//=============================================================================
void CObject::DrawAll()
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CApplication::GetRenderer()->GetDevice();

	for (int i = 0; i < MAX_TYPE; i++)
	{
		for (int j = 0; j < MAX_POLYGON; j++)
		{
			if (m_apObject[i][j] != nullptr)
			{
				m_apObject[i][j]->Draw();
			}
		}
	}
}

//=============================================================================
// オブジェクトの取得
//=============================================================================
CObject* CObject::GetObj(int m_nNumber,int nType)
{
	return m_apObject[nType][m_nNumber];
}

//=============================================================================
// オブジェクトの種類の取得
//=============================================================================
CObject::EObjType CObject::GetObjType(int m_nNumber, int nType)
{
	return m_apObject[nType][m_nNumber]->m_ObjType;
}

//=============================================================================
//全体の取得
//=============================================================================
int CObject::NumAll()
{
	return m_nNumAll;
}

//=============================================================================
// 単体の終了処理
//=============================================================================
void CObject::Release()
{
	if (m_apObject[m_nPriority][m_nID] != nullptr)
	{
		int nId = m_nID;
		int nPri = m_nPriority;
		delete m_apObject[nPri][nId];
		m_apObject[nPri][nId] = nullptr;
	}
}

//=============================================================================
// 種類の設定
//=============================================================================
void CObject::SetObjType(EObjType Type)
{
	m_ObjType = Type;
}
