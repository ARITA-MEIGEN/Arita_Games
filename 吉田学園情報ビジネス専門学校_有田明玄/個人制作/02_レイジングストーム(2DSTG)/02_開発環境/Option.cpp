//=============================================================================
//
// �I�v�V����
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Option.h"
#include"renderer.h"
#include"Application.h"
#include"Bullet.h"
#include"Explosion.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 COption::m_apTexture[OPTION_TEX] = {};
D3DXVECTOR3 COption::m_PlayerPosOld[OPTION_MEMPOS];
int COption::m_nNumOption = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
COption::COption():CObject2D(OBJTYPE_OPTION)
{
	SetObjType(OBJTYPE_OPTION);
	m_nId = m_nNumOption;
	m_nNumOption++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
COption::~COption()
{
	SetObjType(OBJTYPE_INVALID);
	m_nNumOption--;
}

//=============================================================================
// ������
//=============================================================================
HRESULT  COption::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	CObject2D::BindTexture(m_apTexture[m_nId]);	//�e�N�X�`���̐ݒ�
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  COption::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  COption::Update()
{
	SetPos(m_PlayerPosOld[10*(m_nId+1)]);
	CObject2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void  COption::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// �I�v�V��������
//=============================================================================
COption* COption::Create(D3DXVECTOR3 pos)
{
	COption*pOption;
	pOption = new COption;
	if (pOption != nullptr)
	{// �|���S���̏���������
		pOption->Init(OPTION_WIDTH, OPTION_HEIGHT);
	}
	return pOption;
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT COption::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_WHITE001.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOW001.png",
		&m_apTexture[1]);


	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void COption::Unload()
{
	for (int i = 0; i < OPTION_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �ʒu���̋L��
//=============================================================================
void COption::MemPos(D3DXVECTOR3 posold)
{
	if (posold != m_PlayerPosOld[0])
	{//�v���C���[���ړ����Ă���ꍇ
		D3DXVECTOR3 mempos[2];	//����ւ��p

		mempos[0] = m_PlayerPosOld[0];
		m_PlayerPosOld[0] = posold;
		for (int i = 0; i < OPTION_MEMPOS-1; i++)
		{//���W��ۑ�
			mempos[(i+1)%2] = m_PlayerPosOld[i+1];
			m_PlayerPosOld[i+1] = mempos[i%2];
		}
	}
}

//=============================================================================
// �ʒu���̃��Z�b�g
//=============================================================================
void COption::ResetPos(D3DXVECTOR3 posold)
{
	for (int i = 0; i < OPTION_MEMPOS; i++)
	{//���W��ۑ�
		m_PlayerPosOld[i] = posold;
	}
}

