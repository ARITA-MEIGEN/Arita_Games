//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Effect.h"
#include"renderer.h"
#include"Application.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[EFFECT_TEX] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect() :CObject2D(OBJTYPE_EFFECT)
{
	SetObjType(OBJTYPE_EFFECT);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT  CEffect::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	CObject2D::BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CEffect::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  CEffect::Update()
{
	CObject2D::Update();

	//�傫����ω�������
	D3DXVECTOR2 Siz = GetSiz();
	D3DXCOLOR col = GetCol();

	Siz -= {0.1f, 0.1f};
	m_Life--;
	col.a -= 0.1f;

	//�F(�A���t�@�l��ω�������)
	if (col.a <= 0.0f || Siz.x <= 0.0f || Siz.y <= 0.0f || m_Life <= 0)
	{//�A���t�@�l��0�ȉ��̏ꍇ�����I��
		Uninit();
		return;
	}
	else
	{
		SetSiz(Siz);
		SetCol(col);
	}
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;
	SetPos(pos);
}

//=============================================================================
// �`��
//=============================================================================
void  CEffect::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ����
//=============================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz, float lot, D3DXVECTOR3 move, int nLife,D3DXCOLOR col)
{
	CEffect*pEffect;
	pEffect = new CEffect;
 	if (pEffect != nullptr)
	{// �|���S���̏���������
 		pEffect->SetPos(pos);
		pEffect->SetRot(lot);
		pEffect->m_Life=nLife;
		pEffect->SetCol(col);
		pEffect->m_move = move;
		pEffect->Init(siz.x/2,siz.y/2);
	}
	return pEffect;
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CEffect::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_WHITE001.png",
		&m_apTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOW001.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CEffect::Unload()
{
	for (int i = 0; i < EFFECT_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}
