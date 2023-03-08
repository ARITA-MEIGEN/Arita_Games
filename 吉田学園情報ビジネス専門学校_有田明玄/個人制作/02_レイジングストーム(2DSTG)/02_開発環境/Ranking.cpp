//=================================================
// Content     (����)(ranking.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/09/15)
//=================================================
#include"ranking.h"
#include"sound.h"
#include"renderer.h"
#include"Application.h"
#include"Score.h"
#include"Bg.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"

//====================================
//�R���X�g���N�^
//====================================
CRanking::CRanking()
{
	 m_nRankUpdate = -1;	//�X�V�����NNo.
	 m_nTimerRanking;		//�����L���O��ʕ\���^�C�}�[
	 m_fPtnrank = 1.0f;		//�v���C���[�_��
	 m_nCntrank = 0;		//�_�ł̃J�E���g�p
}

//====================================
//�f�X�g���N�^
//====================================
CRanking::~CRanking()
{
}

//============================
//����������
//============================
void CRanking::Init(void)
{
	Load();	//�e�N�X�`���ǂݍ���
	CBg::Load();
	CScore::Load();

	//���_�|�C���^�𐶐�
	m_apBG = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_RANKING);
	m_apUI = CObject2D::Create(D3DXVECTOR3(500.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(160.0f, 600.0f), CObject::OBJTYPE_UI);
	m_apUI->BindTexture(m_pTexture);

	FILE*fp = fopen("data\\TXT\\score.txt", "r");		//�t�@�C���ǂݍ���
	const int lenLine = 1024;	//1�P��̍ő吔
	int nrScore=0;		//�ǂݍ��ݗp�̕�����

	for (int i = 0; i < MAX_RANK; i++)
	{
		if (fp != NULL)
		{
			fscanf(fp, "%d", &nrScore);	//�ǂݍ��񂾕������Ƃɐݒ肷��
		}
		m_apScore[i] = CScore::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_apScore[i]->SetPos(D3DXVECTOR3(600.0f, 605.0f - (121.0f * i),0.0f), D3DXVECTOR2(40.0f, 100.0f));
		m_apScore[i]->SetScore(nrScore);
	}

	fclose(fp);

	//�^�C�}�[�̃��Z�b�g
	m_nTimerRanking = 0;
}

//===========================
//�I������
//===========================
void  CRanking::Uninit(void)
{
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (m_apScore[i] != nullptr)
		{
			m_apScore[i]->Uninit();
			m_apScore[i] = nullptr;
		}
	}
	if (m_apBG != nullptr)
	{
		m_apBG->Uninit();
		m_apBG = nullptr;
	}
	if (m_apUI != nullptr)
	{
		m_apUI->Uninit();
		m_apUI = nullptr;
	}
	Unload();
	CBg::Unload();
	CScore::Unload();
}

//===========================
//�X�V����
//===========================
void  CRanking::Update(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	m_nCntrank++;
	m_nTimerRanking++;

	if (m_nTimerRanking >= 1800
		||pKeyboard->GetTrigger(DIK_RETURN) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true
		&& CFade::Get()	 == CFade::FADE_NONE)
	{//�^�C�g���ֈڍs
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_TITLE);
	}

	//�X�R�A�̐ݒ�
	if ((m_nCntrank % 30) == 0)
	{//�����N�C�������Ƃ��_�ł����邽�߂̃^�C�}�[
		m_fPtnrank = 1.0f - m_fPtnrank;
	}

	//�����N�C�������ꍇ
	if (m_nRankUpdate != -1)
	{
		for (int i = 0; i < MAX_RANK; i++)
		{
			//�����L���O��_�ł�����
			m_apScore[m_nRankUpdate]->SetCol(D3DXCOLOR(1.0f,0.0f,0.0f, m_fPtnrank));
		}
	}
}
//===========================
//�`�揈��
//===========================
void  CRanking::Draw(void)
{

}

//===========================
//�ݒ菈��
//===========================
void  CRanking::Set(int nScore)
{
	int nSave;
	m_nRankUpdate = -1;
	m_nTimerRanking = 0;
	if (nScore >= m_apScore[0]->GetScore())
	{//��r
		m_nRankUpdate++;
		m_apScore[0]->SetScore(nScore);
		for (int i = 0; i < MAX_RANK - 1; i++)
		{
			if (m_apScore[i]->GetScore() > m_apScore[i + 1]->GetScore())
			{//���בւ�
				nSave = m_apScore[i + 1]->GetScore();
				m_apScore[i + 1]->SetScore(m_apScore[i]->GetScore());
				m_apScore[i]->SetScore(nSave);
				m_nRankUpdate++;
			}
		}
	}
	FILE*fp = fopen("data\\TXT\\score.txt", "w");		//�t�@�C���ǂݍ���

	for (int i = 0; i < MAX_RANK; i++)
	{
		fprintf(fp, "%d\n", m_apScore[i]->GetScore());
	}

	fclose(fp);
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
void CRanking::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank.png",
		&m_pTexture);
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CRanking::Unload()
{
	if (m_pTexture != nullptr)
	{//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
