//=============================================================================
//
// ����
// Author : �L�c����
//
//=============================================================================
//�C���N���[�h
#include "Explosion.h"
#include"Application.h"
#include"renderer.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_apTexture[EXPLOSION_TEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion() :CObject2D(8)
{
	SetObjType(OBJTYPE_EXPLOSION);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{
	m_nAnimTimer = 0;
	m_nPtnAnim = 0;
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT  CExplosion::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	CObject2D::BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
	SetUV((1.0f / EXPLOSION_PTN)*m_nPtnAnim, (1.0f / EXPLOSION_PTN)*(m_nPtnAnim + 1), 0.0f, 1.0f);
		
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  CExplosion::Update()
{
	SetUV((1.0f / EXPLOSION_PTN)*m_nPtnAnim, (1.0f / EXPLOSION_PTN)*(m_nPtnAnim + 1), 0.0f, 1.0f);
	CObject2D::Update();

	m_nAnimTimer++;					//�J�E���^�[���Z
	if ((m_nAnimTimer % EXPLOSION_TIME) == 0)
	{
		m_nPtnAnim++;
		//�p�^�[�����𒴂����ꍇ
		if (m_nPtnAnim >= EXPLOSION_PTN)
		{
			Uninit();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void  CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CExplosion::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CExplosion::Unload()
{
	for (int i = 0; i < EXPLOSION_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �����G�t�F�N�g����
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz)
{
	CExplosion*pBullet = nullptr;
	pBullet = new CExplosion;
	pBullet->SetPos(pos);			//�ʒu�ݒ�
	pBullet->Init(siz.x, siz.y);
	pBullet->SetSiz(siz);
	return pBullet;
}