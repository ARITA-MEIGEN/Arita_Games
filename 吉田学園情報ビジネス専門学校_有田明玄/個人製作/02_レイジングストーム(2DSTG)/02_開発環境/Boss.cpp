//=============================================================================
//
// �G(�{�X1)
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"sound.h"
#include"Explosion.h"
#include"Boss.h"
#include"Score.h"
#include"Enemy.h"
#include"Fade.h"
#include"Effect.h"
#include"Game.h"


//�ÓI�����o�ϐ��錾	
CBoss::BOSSSTATE CBoss::m_BossState = BOSSSTATE_NONE;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoss::CBoss()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoss::~CBoss()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT  CBoss::Init(float Width, float Height)
{
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -255.0f, 0.0f);
	m_nLife = MAX_BOSSLIFE;
	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�f��
	m_pBossbase = CEnemy::Create(CEnemy::MOVE_BOSS_BASE, m_pos);

	//�Œ�C��
	m_apBossCannon[0] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x - 120.0f, m_pos.y + 75.0f, 0.0f));
	m_apBossCannon[1] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x + 120.0f, m_pos.y + 75.0f, 0.0f));
	m_apBossCannon[2] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x - 295.0f, m_pos.y + 65.0f, 0.0f));
	m_apBossCannon[3] = CEnemy::Create(CEnemy::MOVE_BOSS_CANNON, D3DXVECTOR3(m_pos.x + 295.0f, m_pos.y + 65.0f, 0.0f));

	//���@�_��
	m_apBossATCannon[0] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y + 60.0f, 0.0f));
	m_apBossATCannon[1] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x - 200.0f, m_pos.y + 60.0f, 0.0f));
	m_apBossATCannon[2] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y + 40.0f, 0.0f));
	m_apBossATCannon[3] = CEnemy::Create(CEnemy::MOVE_BOSS_ATCANNON, D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y + 40.0f, 0.0f));

	//�R�A�r�[��
	m_pBossCoreCannon = CEnemy::Create(CEnemy::MOVE_BOSS_CORECANNON, D3DXVECTOR3(m_pos.x, m_pos.y + 105.0f, 0.0f));
	//�R�A
	m_apBossCore[0] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x + 255.0f, m_pos.y - 30.0f, 0.0f));
	m_apBossCore[1] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x - 255.0f, m_pos.y - 30.0f, 0.0f));
	m_apBossCore[2] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x + 505.0f, m_pos.y - 20.0f, 0.0f));
	m_apBossCore[3] = CEnemy::Create(CEnemy::MOVE_BOSS_CORE, D3DXVECTOR3(m_pos.x - 505.0f, m_pos.y - 20.0f, 0.0f));
	m_BossState = BOSSSTATE_APPEAR;

	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CBoss::Uninit()
{
	m_BossState = BOSSSTATE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���W�����Z�b�g(���Ȃ��ƍŏ��������ʓ������ɂȂ�̂�)
	CObject::Release();
}

//=============================================================================
// �X�V
//=============================================================================
void  CBoss::Update()
{
	if (m_BossState == BOSSSTATE_APPEAR)
	{
		m_pos.y += m_move.y;
	}

	if (m_nLife <= 4 && m_frame % 600 == 0)
	{
		CEnemy::Create(CEnemy::MOVE_004, D3DXVECTOR3(-200.0f, SCREEN_HEIGHT / 2, 0.0f));
		CEnemy::Create(CEnemy::MOVE_005, D3DXVECTOR3(SCREEN_WIDTH + 200.0f, SCREEN_HEIGHT / 2, 0.0f));

	}
	if (m_nLife <= 1 && m_frame % 360 == 0)
	{//���E�̏ォ��΂ߕ����ɍ~��Ă���
		CEnemy::Create(CEnemy::MOVE_006, D3DXVECTOR3(-100.0f,0.0f, 0.0f));
		CEnemy::Create(CEnemy::MOVE_007, D3DXVECTOR3(SCREEN_WIDTH + 100.0f, -0.0f, 0.0f));
	}

	InScreen();
	SetPos();
	StateManager();
	m_time--;
	m_frame++;
}

//=============================================================================
// �`��
//=============================================================================
void  CBoss::Draw()
{

}

//=============================================================================
// �G����
//=============================================================================
CBoss* CBoss::Create()
{
	CBoss*pBoss;
	pBoss = new CBoss;
	pBoss->Init(0.0f, 0.0f);
	StopSound(SOUND_LABEL_STAGE001);
	PlaySound(SOUND_LABEL_SE_SIREN);
	return pBoss;
}

//=============================================================================
// �_���[�W�ݒ�
//=============================================================================
void CBoss::CoreDamage()
{
	//�_���[�W����                                                           
  	m_nLife--;
	if (m_nLife <= 0)
	{
		m_BossState = BOSSSTATE_DEATH;
		CGame::GetScore()-> AddScore(100000);
		CApplication::StopTime(60);
		CApplication::SlowTime(true);			//�X���[�ɂ���
		m_time = NEXT_BOSS_TIME;				//�t�F�[�h�܂ł̎���
		CGame::SetGame(CGame::GAME_END);
	}
	PlaySound(SOUND_LABEL_SE_EXPLOSION003);
	CGame::GetScore()->AddScore(50000);
}

//=============================================================================
// ��ԊǗ�
//=============================================================================
void CBoss::StateManager()
{
	switch (m_BossState)
	{
	case CBoss::BOSSSTATE_DEATH:
		if (m_time == NEXT_BOSS_TIME - 1)
		{//����ōŏ���1f�����ʂ�
			for (int i = 0; i < 20; i++)
			{//����
				CEffect::Create(m_pBossbase->GetPos(),																//�ʒu
					D3DXVECTOR2(m_pBossbase->GetSiz().y/2, m_pBossbase->GetSiz().y/2),								//�傫��
					m_pBossbase->GetRot(),																			//����
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10+5) / 1.0f + 00.0f,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10+5) / 1.0f + 0.0f,			//y
						0.0f),																						//z
					600,																							//����
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 5.0f));															//�F
			}
			//�f��
			m_pBossbase->Uninit();

			//��������
			for (int i = 0; i < MAX_CANNON; i++)
			{
				if (m_apBossCannon[i] != nullptr)
				{
					//�Œ�C��
					m_apBossCannon[i]->Uninit();
				}
			}

			for (int i = 0; i < MAX_ATCANNON; i++)
			{
				if (m_apBossCannon[i] != nullptr)
				{
					//���@�_��
					m_apBossATCannon[i]->Uninit();
				}
			}
			PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		}

		if (m_time <= 0)
		{
			if (CFade::Get() == CFade::FADE_NONE)
			{
				m_BossState = BOSSSTATE_APPEAR;
				CFade::Set(CApplication::MODE_RESULT);
			}
		}
		break;
	}
}

//=============================================================================
// ��ʊO�����ʓ��ɓ��������̏���(�o�ꎞ)
//=============================================================================
void CBoss::InScreen()
{
	if (m_pos.y >= 75.0f&&m_BossState==BOSSSTATE_APPEAR)
	{
		StopSound();
		PlaySound(SOUND_LABEL_STAGE001BOSS);
		m_move.y = 0.0f;
		m_BossState = BOSSSTATE_NORMAL;
	}
}

//=============================================================================
//���W�X�V
//=============================================================================
void CBoss::SetPos()
{
	//�f��
	m_pBossbase ->SetPos (m_pos);

	//�Œ�C��
	m_apBossCannon[0]->SetPos( D3DXVECTOR3(m_pos.x - 120.0f, m_pos.y + 75.0f+75.0f, 0.0f));
	m_apBossCannon[1]->SetPos(D3DXVECTOR3(m_pos.x + 120.0f, m_pos.y + 75.0f + 75.0f, 0.0f));
	m_apBossCannon[2]->SetPos(D3DXVECTOR3(m_pos.x - 295.0f, m_pos.y + 65.0f + 75.0f, 0.0f));
	m_apBossCannon[3]->SetPos(D3DXVECTOR3(m_pos.x + 295.0f, m_pos.y + 65.0f + 75.0f, 0.0f));

	//���@�_��
	m_apBossATCannon[0]->SetPos(D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y + 60.0f + 75.0f, 0.0f));
	m_apBossATCannon[1]->SetPos(D3DXVECTOR3(m_pos.x - 200.0f, m_pos.y + 60.0f + 75.0f, 0.0f));
	m_apBossATCannon[2]->SetPos(D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y + 40.0f + 75.0f, 0.0f));
	m_apBossATCannon[3]->SetPos(D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y + 40.0f + 75.0f, 0.0f));

	//�R�A�r�[��
	m_pBossCoreCannon->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 105.0f + 75.0f, 0.0f));
	//�R�A
	m_apBossCore[0]->SetPos(D3DXVECTOR3(m_pos.x + 255.0f, m_pos.y - 30.0f + 75.0f, 0.0f));
	m_apBossCore[1]->SetPos(D3DXVECTOR3(m_pos.x - 255.0f, m_pos.y - 30.0f + 75.0f, 0.0f));
	m_apBossCore[2]->SetPos(D3DXVECTOR3(m_pos.x + 505.0f, m_pos.y - 20.0f + 75.0f, 0.0f));
	m_apBossCore[3]->SetPos(D3DXVECTOR3(m_pos.x - 505.0f, m_pos.y - 20.0f + 75.0f, 0.0f));
}

//=============================================================================
// ��ʊO�����ʓ��ɓ��������̏���(�o�ꎞ)
//=============================================================================
CBoss::BOSSSTATE CBoss::GetState()
{
	return m_BossState;
}

//=============================================================================
// �̗͂̎擾
//=============================================================================
int CBoss::GetLife()
{
	return m_nLife;
}
