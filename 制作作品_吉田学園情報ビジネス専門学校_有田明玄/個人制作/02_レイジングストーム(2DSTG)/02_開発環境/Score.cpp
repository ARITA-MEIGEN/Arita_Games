//=============================================================================
//
// �X�R�A
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Score.h"
#include"renderer.h"
#include"Application.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CScore::m_apTexture;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore() :CObject(OBJTYPE_UI)
{
	SetObjType (OBJTYPE_UI);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CScore::Init(float Width, float Height)
{
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i] = new CObject2D(OBJTYPE_UI);
		m_apObject2D[i]->Init(Width, Height);
		m_apObject2D[i]->BindTexture(m_apTexture);	//�e�N�X�`���̐ݒ�
	}
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void CScore::Uninit()
{
	CObject::Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CScore::Update()
{
	D3DXVECTOR3 dpos=m_pos;
	for (int i = 0; i < NUM_SCORE; i++)
	{//�S�̂̈ʒu��ݒ�
		m_apObject2D[i]->SetPos(dpos);
		m_apObject2D[i]->SetSiz(m_siz);
		dpos.x += m_siz.x;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CScore::Draw()
{

}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CScore::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&m_apTexture);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CScore::Unload()
{
	for (int i = 0; i <NUM_SCORE; i++)
	{
		if (m_apTexture != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture->Release();
			m_apTexture = nullptr;
		}
	}
}

//=============================================================================
// �w�i����
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos)
{
	CScore*pScore;
	pScore = new CScore;
	if (pScore != nullptr)
	{// �|���S���̏���������
		pScore->Init(SCORE_WIDTH, SCORE_HEIGHT);
		pScore->SetPos(pos, D3DXVECTOR2(SCORE_WIDTH,SCORE_HEIGHT));
	}
	return pScore;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CScore::SetPos(D3DXVECTOR3 pos, D3DXVECTOR2 siz)
{
	m_pos = pos;
	m_siz = siz;
}

//=============================================================================
// �ݒ�
//=============================================================================
void CScore::SetScore(int nScore)
{
	int aPosTexU[NUM_SCORE];	//�e���̐������i�[

	m_Score = nScore;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetUV(0.1f*(aPosTexU[i]), 0.1f*(aPosTexU[i] + 1), 0.0f, 1.0f);
	}
}

//=============================================================================
// ���Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	int aPosTexU[NUM_SCORE];	//�e���̐������i�[

	m_Score += nValue;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetUV(0.1f*(aPosTexU[i]), 0.1f*(aPosTexU[i] + 1), 0.0f, 1.0f);
	}
}

//=============================================================================
// �擾
//=============================================================================
int CScore::GetScore()
{
	return m_Score;
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScore::SetCol(D3DXCOLOR col)
{
	for (int i = 0; i < NUM_SCORE; i++)
	{
		m_apObject2D[i]->SetCol(col);
	}
}

