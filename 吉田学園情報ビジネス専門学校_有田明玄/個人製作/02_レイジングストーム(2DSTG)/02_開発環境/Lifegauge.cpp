//=============================================================================
//
// �̗�
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Lifegauge.h"
#include"renderer.h"
#include"Application.h"
#include"Player.h"
#include"Score.h"
#include"Game.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CLife::m_apTexture[LIFE_TEX] = {};
CObject2D*CLife::m_apObject2D[LIFE_POLYGON] = {};
CObject2D*CLife::m_aLifeUI=nullptr;
int CLife::m_NumLife = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLife::CLife() :CObject(OBJTYPE_UI)
{
	SetObjType(OBJTYPE_UI);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife::~CLife()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CLife::Init(float Width, float Height)
{
	for (int i = 0; i <LIFE_POLYGON; i++)
	{//�̗͂̕`��
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->Init(Width, Height);
		m_apObject2D[i]->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
	}
	m_NumLife = 3;
	m_apObject2D[3]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_apObject2D[4]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_aLifeUI = new CObject2D(OBJTYPE_UI);
	m_aLifeUI->Init(LIFEUI_SIZ_X, LIFEUI_SIZ_Y);
	m_aLifeUI->BindTexture(m_apTexture[1]);	//�e�N�X�`���̐ݒ�

	SetPos();

	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void CLife::Uninit()
{
	for (int i = 0; i < m_NumLife - 1; i++)
	{
		if (m_apObject2D[i] != nullptr)
		{
			m_apObject2D[i] = nullptr;
		}
	}
	CObject::Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CLife::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void CLife::Draw()
{
	
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CLife::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LIFE.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LIFElogo.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CLife::Unload()
{
	for (int i = 0; i <LIFE_TEX; i++)
	{
		if (m_apTexture != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �̗͐���
//=============================================================================
CLife * CLife::Create()
{
	CLife*pLIFE;
	pLIFE = new CLife;
	if (pLIFE != nullptr)
	{// �|���S���̏���������
		pLIFE->Init(LIFE_SIZ, LIFE_SIZ);
	}
	return pLIFE;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CLife::SetPos()
{
	for (int i = 0; i < LIFE_POLYGON; i++)
	{
		m_apObject2D[i]->SetPos(D3DXVECTOR3(LIFE_POS_X +((LIFE_SIZ+ LIFE_INTERVAL)*i) , LIFE_POS_Y, 0.0f));
	}
	m_aLifeUI->SetPos(D3DXVECTOR3(LIFELOGO_POS_X, LIFELOGO_POS_Y, 0.0f));
}

//=============================================================================
//�̗͉�
//=============================================================================
void CLife::LifeRecovery()
{
	if (m_NumLife < LIFE_POLYGON)
	{
		m_apObject2D[m_NumLife]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); 
		m_NumLife++;
	}
	else
	{
		CGame::GetScore()->AddScore(5000);
	}
}

//=============================================================================
//�̗͌���
//=============================================================================
void CLife::LifeDecrease()
{
	if (m_NumLife >= 0)
	{
		m_apObject2D[m_NumLife - 1]->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		m_NumLife--;
	}

}

