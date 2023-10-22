//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include "Object.h"
#include"Application.h"
#include"renderer.h"

//�ÓI�����o�ϐ��錾
 CObject*CObject::m_apObject[MAX_TYPE][MAX_POLYGON];
 int CObject::m_nNumAll=0;
//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
	m_nNumAll--;
}

//=============================================================================
//�S�Ă̏I��
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
//�S�Ă̍X�V
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
// �S�Ă̕`��
//=============================================================================
void CObject::DrawAll()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
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
// �I�u�W�F�N�g�̎擾
//=============================================================================
CObject* CObject::GetObj(int m_nNumber,int nType)
{
	return m_apObject[nType][m_nNumber];
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̎擾
//=============================================================================
CObject::EObjType CObject::GetObjType(int m_nNumber, int nType)
{
	return m_apObject[nType][m_nNumber]->m_ObjType;
}

//=============================================================================
//�S�̂̎擾
//=============================================================================
int CObject::NumAll()
{
	return m_nNumAll;
}

//=============================================================================
// �P�̂̏I������
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
// ��ނ̐ݒ�
//=============================================================================
void CObject::SetObjType(EObjType Type)
{
	m_ObjType = Type;
}
