//=============================================================================
//
// �K�E�Z�Q�[�W
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Special.h"
#include"renderer.h"
#include"Application.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CSpecial::m_apTexture[NUM_TEX_SP] = {};
float   CSpecial::m_nSpecial = 0.0f;
CObject2D*CSpecial::m_apObject2D[NUM_TEX_SP];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSpecial::CSpecial() :CObject(OBJTYPE_UI)
{
	SetObjType(OBJTYPE_UI);
	m_nSpecial = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpecial::~CSpecial()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSpecial::Init(float Width, float Height)
{
	for (int i = 0; i < NUM_TEX_SP; i++)
	{
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->BindTexture(m_apTexture[i]);	//�e�N�X�`���̐ݒ�
	}
		m_apObject2D[0]->Init(0.0f, Height);
		m_apObject2D[1]->Init(Width, Height);


	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void CSpecial::Uninit()
{
	CObject::Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CSpecial::Update()
{
	m_nSpecial += RECOVERY_QUANTITY;
	if (m_nSpecial>MAX_SPECIAL)
	{
		m_nSpecial = MAX_SPECIAL;
	}

	//�Q�[�W�̐L�k
	m_apObject2D[0]->SetPosR((float)m_nSpecial *( SPECIAL_WIDTH/MAX_SPECIAL));
}

//=============================================================================
// �`��
//=============================================================================
void CSpecial::Draw()
{

}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CSpecial::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SPGauge001.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SPgauge002.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CSpecial::Unload()
{
	for (int i = 0; i < NUM_TEX_SP; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �w�i����
//=============================================================================
CSpecial * CSpecial::Create(D3DXVECTOR3 pos)
{
	CSpecial*pSpecial;
	pSpecial = new CSpecial;
	if (pSpecial != nullptr)
	{//�|���S���̏���������
		pSpecial->Init(SPECIAL_WIDTH, SPECIAL_HEIGHT);
		for (int i = 0; i < NUM_TEX_SP; i++)
		{
			pSpecial->m_apObject2D[i]->SetPos(pos);
		}
		pSpecial->m_apObject2D[0]->SetPos(D3DXVECTOR3(pos.x- SPECIAL_WIDTH/2,pos.y,pos.z));

	}
	return pSpecial;
}

//=============================================================================
// ���Z
//=============================================================================
void CSpecial::AddSpecial(float Special)
{
	m_nSpecial += Special;
}

//=============================================================================
// �擾
//=============================================================================
float CSpecial::GetSpecial()
{
	return m_nSpecial;
}
