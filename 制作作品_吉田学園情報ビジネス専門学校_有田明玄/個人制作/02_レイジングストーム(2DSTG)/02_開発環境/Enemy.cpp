//=============================================================================
//
// �G
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Enemy.h"
#include"renderer.h"
#include"Application.h"
#include"Easing.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Special.h"
#include"Player.h"
#include"Game.h"
#include"Boss.h"
#include"EnemyManager.h"
#include"Score.h"
#include"Item.h"
#include"Effect.h"

//�ÓI�����o�ϐ��錾	
int CEnemy::m_nEnemy = 0;												//�G�̐�
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[ENEMY_TEX] = {};					//�e�N�X�`��
LPDIRECT3DTEXTURE9 CEnemy::m_apBossTexture[BOSS001_TEX] = {};			//�e�N�X�`���̐�
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() :CObject2D(OBJTYPE_ENEMY)
{
	m_nEnemy++;
	SetObjType(OBJTYPE_ENEMY);
	m_state = ENEMYSTATE_APPEAR;
	m_frame = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	m_nEnemy--;
	SetObjType(OBJTYPE_INVALID);	//���g�p�ɂ���@
}

//=============================================================================
// ������
//=============================================================================
HRESULT  CEnemy::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  CEnemy::Update()
{
	Offscreen();
	SetMove();
	StateManagement();
	CObject2D::Update();
	Shot();
	Lockon();
	if (ENEMYSTATE_APPEAR != m_state)
	{//��ʓ��̏ꍇ�̂݃J�E���g
		if (m_Moveptn == MOVE_BOSS_CORECANNON || m_Moveptn == MOVE_BOSS_CORE || m_Moveptn == MOVE_BOSS_CANNON || m_Moveptn == MOVE_BOSS_ATCANNON)
		{
			if (CBoss::GetState() == CBoss::BOSSSTATE_NORMAL)
			{
				m_frame++;
			}
		}
		else
		{
			m_frame++;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void  CEnemy::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CEnemy::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy001.png",
		&m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy003.png",
		&m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy002.png",
		&m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnemyBonus.png",
		&m_apTexture[3]);

	//�{�X�̃e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BossBase003.png",
		&m_apBossTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Boss001_001.png",
		&m_apBossTexture[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Boss001_002.png",
		&m_apBossTexture[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Boss001_003.png",
		&m_apBossTexture[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Boss001_004.png",
		&m_apBossTexture[4]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CEnemy::Unload()
{
	for (int i = 0; i < ENEMY_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();	
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �G����
//=============================================================================
CEnemy* CEnemy::Create(MOVEPATTERN moveptn,D3DXVECTOR3 pos)
{
	CEnemy*pEnemy;
	pEnemy = new CEnemy;
	if (pEnemy != nullptr)
	{
		pEnemy->SetPos(pos);
		pEnemy->SetMovePtn(moveptn);
		pEnemy->Init(ENEMY_WIDTH, ENEMY_HEIGHT);
		pEnemy->m_nLife = 150;

		switch (moveptn)
		{
		case CEnemy::MOVE_000:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_001:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_002:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_003:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_004:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_005:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_006:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_007:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_008:
			pEnemy->SetSiz(D3DXVECTOR2(CANNON_HEIGHT,CANNON_WIDTH));
			pEnemy->BindTexture(m_apTexture[1]);	//�e�N�X�`���̐ݒ�
			pEnemy->m_nLife = 800;
			break;
		case CEnemy::MOVE_009:
			pEnemy->SetSiz(D3DXVECTOR2(CANNON_HEIGHT, CANNON_WIDTH));
			pEnemy->BindTexture(m_apTexture[2]);	//�e�N�X�`���̐ݒ�
			pEnemy->m_nLife = 800;
			break;

		case CEnemy::MOVE_010:
			pEnemy->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
			pEnemy->SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			pEnemy->m_nLife = 250;
			break;
		case CEnemy::MOVE_BOSS_BASE:
			pEnemy->SetSiz(D3DXVECTOR2(SCREEN_WIDTH, 300.0f));
			pEnemy->BindTexture(m_apBossTexture[0]);	//�e�N�X�`���̐ݒ�
			pEnemy->m_state = ENEMYSTATE_NONE;
			break;
		case CEnemy::MOVE_BOSS_CANNON:
			pEnemy->m_nLife = 2000;
			pEnemy->SetSiz(D3DXVECTOR2(30.0f, 70.0f));
			pEnemy->BindTexture(m_apBossTexture[1]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_BOSS_ATCANNON:
			pEnemy->m_nLife = 2000;
			pEnemy->SetSiz(D3DXVECTOR2(60.0f, 100.0f));
			pEnemy->BindTexture(m_apBossTexture[2]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_BOSS_CORE:
			pEnemy->m_nLife = 3000;
			pEnemy->SetSiz(D3DXVECTOR2(70.0f, 70.0f));
			pEnemy->BindTexture(m_apBossTexture[3]);	//�e�N�X�`���̐ݒ�
			break;
		case CEnemy::MOVE_BOSS_CORECANNON:
			pEnemy->m_nLife = 6000;
			pEnemy->SetSiz(D3DXVECTOR2(150.0f, 270.0f));
			pEnemy->BindTexture(m_apBossTexture[4]);	//�e�N�X�`���̐ݒ�
			break;

		case CEnemy::MOVE_BONUS:
			pEnemy->m_nLife = 1000;
			pEnemy->SetSiz(D3DXVECTOR2(30.0f, 30.0f));
			pEnemy->BindTexture(m_apTexture[3]);	//�e�N�X�`���̐ݒ�
			pEnemy->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		case CEnemy::MOVE_INVALID:
			break;
		case CEnemy::MOVE_MAX:
			break;
		default:
			break;
		}

	}
	return pEnemy;
}

//=============================================================================
// �s���p�^�[���̐ݒ�
//=============================================================================
void CEnemy::SetMove()
{
	D3DXVECTOR3 pos = GetPos();

	switch (m_Moveptn)
	{
	case MOVE_000:
		m_move.x = 2.0f;
		break;
	case MOVE_001:
		m_move.x = -2.0f;
		break;
	case MOVE_002:
		m_move.x = Easing::OutSine<float>((float)m_frame, 40.0f, 8.0f, 0.0f);
		m_move.y = 2.0f;
		break;
	case MOVE_003:
		m_move.x = -Easing::OutSine<float>((float)m_frame, 40.0f, 8.0f, 0.0f);
		m_move.y = 2.0f;
		break;

	case MOVE_004:
		m_move.x = 3.0f;
		m_move.y = (Easing::OutSine<float>((float)m_frame, 60.0f, 3.0f, 0.0f));
	
		break;
	case MOVE_005:
		m_move.x = -3.0f;
		m_move.y = (Easing::OutSine<float>((float)m_frame, 60.0f, 3.0f, 0.0f));
		break;

	case MOVE_006:
		m_move.x = 5.5f;
		//���ݎ��ԁA�ړ����Ă��猳�̈ʒu�ɖ߂�܂ł̎��ԁA�U�ꕝ�A���_
		m_move.y = Easing::OutSine<float>((float)m_frame, 300.0f, 7.0f, 0.0f);
		break;

	case MOVE_007:
		m_move.x = -5.5f;
		//���ݎ��ԁA�ړ����Ă��猳�̈ʒu�ɖ߂�܂ł̎��ԁA�U�ꕝ�A���_
		m_move.y = Easing::OutSine<float>((float)m_frame, 300.0f, 7.0f, 0.0f);
		break;

	case MOVE_008:
		m_move.y = 1.8f;
		break;

	case MOVE_009:
		m_move.y = 1.8f;
		break;

	case MOVE_010:
		m_move.y = 1.8f;
		break;

	case MOVE_BONUS:
		m_move.x = -3.0f;
		break;
	default:
		break;
	}
	
	pos += m_move;

	SetPos(pos);
}

//=============================================================================
// �s���p�^�[���̎w��
//=============================================================================
void CEnemy::SetMovePtn(MOVEPATTERN moveptn)
{
	m_Moveptn = moveptn;
}

//=============================================================================
// ��ԊǗ�
//=============================================================================
void  CEnemy::StateManagement()
{
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:
		break;

	case ENEMYSTATE_DAMAGE:
		m_nCnt++;
		m_nCntState--;
		if ((m_nCnt % 5) == 0)
		{
			m_fPtntitle = 1 - m_fPtntitle;
		}

		//�|���S�����_���[�W�F�ɐݒ�
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fPtntitle));

		if (m_nCntState <= 0)
		{
			m_fPtntitle = 0;
			m_nCnt = 0;

			m_state = ENEMYSTATE_NORMAL;

			//�|���S����ʏ�F�ɐݒ�
			if (m_Moveptn == MOVE_010)
			{
				SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			}
			else
			{
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		break;

	case ENEMYSTATE_DEATH:
		SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
	}
}

//=============================================================================
// �_���[�W�ݒ�
//=============================================================================
void CEnemy::Damage(int damage)
{
	if (CBoss::GetState() == CBoss::BOSSSTATE_APPEAR&&(m_Moveptn == MOVE_BOSS_ATCANNON||m_Moveptn == MOVE_BOSS_CANNON || m_Moveptn == MOVE_BOSS_CORE || m_Moveptn == MOVE_BOSS_CORECANNON))
	{//�o�ꎞ�̓{�X�͖��G
		m_state = ENEMYSTATE_APPEAR;
	}
	if (m_state != ENEMYSTATE_APPEAR&&m_state!=ENEMYSTATE_NONE)
	{
		//�_���[�W����                                                           
		m_nLife -= damage;
		m_state = ENEMYSTATE_DAMAGE;
		m_nCntState = 10;				//���G����

		if (m_nLife <= 0&&m_state!=ENEMYSTATE_DEATH)
		{
			for (int i = 0; i < 20; i++)
			{
				CEffect::Create(GetPos(),																		//�ʒu
					D3DXVECTOR2(GetSiz().x, GetSiz().x),														//�傫��
					GetRot(),																					//����
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//x
								cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//y
								0.0f),																			//z
					600,																						//����
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 1.0f));														//�F
			}
			
			m_state = ENEMYSTATE_DEATH;
			PlaySound(SOUND_LABEL_SE_EXPLOSION003);
			CGame::GetScore()->AddScore(5000);			//�X�R�A���Z
			m_bCharge = false;							//�`���[�W���o�؂�

			if (m_Moveptn == MOVE_008 || m_Moveptn == MOVE_009)
			{//�ł߂̖C��̏ꍇ
				CItem::Create(CItem::ITEM_HEALING,GetPos());
			}

			else if (m_Moveptn == MOVE_BOSS_CORE || m_Moveptn == MOVE_BOSS_CORECANNON)
			{//�{�X�̃R�A�̏ꍇ
				CBoss*pBoss = CEnemyManager::GetBoss();
				pBoss->CoreDamage();
				if (pBoss->GetLife()==1||pBoss->GetLife()==4)
				{
					CItem::Create(CItem::ITEM_HEALING, GetPos());
				}
			}

			else if (m_Moveptn == MOVE_BONUS)
			{
				CGame::GetScore()->AddScore(50000);			//�X�R�A���Z
			}

			if (m_Moveptn == MOVE_BOSS_CORECANNON || m_Moveptn == MOVE_BOSS_CORE || m_Moveptn == MOVE_BOSS_CANNON || m_Moveptn == MOVE_BOSS_ATCANNON)
			{

			}
			else
			{
				Uninit();
				return;
			}
		}
	}
}

//=============================================================================
// ��ʊO�̏���
//=============================================================================
void CEnemy::Offscreen()
{//��ʓ��ɓ����Ă���NORMAL�ɖ߂�
	D3DXVECTOR3 pos = GetPos();
	if (pos.x <= SCREEN_WIDTH + GetSiz().x / 2&&
		pos.x >= -GetSiz().x / 2&&
		pos.y <= SCREEN_HEIGHT + GetSiz().y / 2&&
		pos.y >= -GetSiz().y / 2&&
		m_state == ENEMYSTATE_APPEAR)
	{//��ʓ��ɓ�������
		m_state = ENEMYSTATE_NORMAL;
	}
}

//=============================================================================
// �G�̏�Ԏ擾
//=============================================================================
CEnemy::ENEMYSTATE CEnemy::GetState()
{
	return m_state;
}


//=============================================================================
// �ˌ�
//=============================================================================
void CEnemy::Shot()
{//�G�̒e
	D3DXVECTOR3 pos = GetPos();
	if ((m_state != ENEMYSTATE_APPEAR) && (m_state != ENEMYSTATE_DEATH) && (m_state != ENEMYSTATE_NONE))
	{
		switch (m_Moveptn)
		{
		case CEnemy::MOVE_000:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_001:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_002:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_003:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_004:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_005:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_006:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_007:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_008:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_CANNON01);
				CBullet::Create(pos, CBullet::ENEMY_CANNON03);
				CBullet::Create(pos, CBullet::ENEMY_CANNON07);
				CBullet::Create(pos, CBullet::ENEMY_CANNON09);
			}
			break;
		case CEnemy::MOVE_009:
			if (m_frame % DEFAULT_BULLETRATE == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_CANNON02);
				CBullet::Create(pos, CBullet::ENEMY_CANNON04);
				CBullet::Create(pos, CBullet::ENEMY_CANNON06);
				CBullet::Create(pos, CBullet::ENEMY_CANNON08);
			}
			break;
		case CEnemy::MOVE_010:
			if (m_frame % 150 == 1)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
		case CEnemy::MOVE_BOSS_BASE:
			break;
		case CEnemy::MOVE_BOSS_ATCANNON:
			if (m_frame % 118 == 1&&CBoss::GetState()== CBoss::BOSSSTATE_NORMAL)
			{
				CBullet::Create(pos, CBullet::ENEMY_BULLET);
			}
			break;
		case CEnemy::MOVE_BOSS_CANNON:
			if (m_frame % 153 == 1 && CBoss::GetState() == CBoss::BOSSSTATE_NORMAL)
			{
				CBullet::Create(pos, CBullet::ENEMY_CANNON02);
			}
			break;
		case CEnemy::MOVE_BOSS_CORECANNON:
			if (m_frame % 300==299 && CBoss::GetState() == CBoss::BOSSSTATE_NORMAL)
			{
				m_bCharge = true;
				PlaySound(SOUND_LABEL_SE_CHARGE);
			}
			if (m_bCharge==true&& m_frame % 20 == 0)
			{
				for (int i = 0; i < 5; i++)
				{//�`���[�W���o
					float fSpeed = 3.0f;
					D3DXVECTOR3 move = D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*fSpeed,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*fSpeed,								//y
						0.0f);																			//z
					CEffect::Create((GetPos()+D3DXVECTOR3(0.0f,-55.0f,0.0f)) + move*50.0f,				//�ʒu
						D3DXVECTOR2(GetSiz().x/3, GetSiz().x/3),										//�傫��
						GetRot(),																		//����
						-move,																			//�ړ���
						600,																			//����
						D3DXCOLOR(1.0f, 0.40f, 0.0f, 5.0f));											//�F
				}
			}
			
			if (m_frame % 600 == 599 && CBoss::GetState() == CBoss::BOSSSTATE_NORMAL)
			{
				m_bCharge = false;
				StopSound(SOUND_LABEL_SE_CHARGE);
				PlaySound(SOUND_LABEL_SE_BOSSCANNON);
				CBullet::Create(pos, CBullet::ENEMY_BEAMCANNON);
			}
			break;
		case CEnemy::MOVE_BOSS_CORE:
			if (m_frame % 201 == 1 && CBoss::GetState() == CBoss::BOSSSTATE_NORMAL)
			{
				CBullet::Create(pos, CBullet::ENEMY_CANNON01);
				CBullet::Create(pos, CBullet::ENEMY_CANNON03);
			}
			break;
		case CEnemy::MOVE_INVALID:
			break;
		case CEnemy::MOVE_MAX:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// ���b�N�I��(����)
//=============================================================================
void CEnemy::Lockon()
{
	if (m_Moveptn == MOVE_BOSS_ATCANNON&&m_frame%1==0)
	{//�z�[�~���O�̐ݒ�
		//��莞�Ԍo�߂Ńv���C���[�̕����ɖ��C
		float fRotMove, fRotDest, fRotDiff, fTgMove = 0.0f, fTgDest = 0.0f, fTgDiff = 0.0f;	//�v�Z�E��r�p
		float TgLength = 1000.0f;	//�K���Ȑ��l���Ԃ�����

		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_PLAYER);
			if (pObject != nullptr)
			{//�g�p�����ǂ�������
				D3DXVECTOR3 BulletPos = CObject2D::GetPos();					//�e�̍��W���擾
				CPlayer *pPlayer = (CPlayer*)pObject;
				fRotMove = atan2f(0.0f,0.0f);									//���݂̈ړ�����(�p�x)
																				//�ړI�̈ړ�����(�p�x)	����̍��W���玩������������
				fRotDest = atan2f(pPlayer->GetPos().x - BulletPos.x, pPlayer->GetPos().y - BulletPos.y);
				fRotDiff = fRotDest - fRotMove;									//�ړI�̈ړ������܂ł̍���
				D3DXVECTOR3 fDiff = pPlayer->GetPos() - BulletPos;
				float fLength = D3DXVec3Length(&fDiff);							//����
				if (fLength <= TgLength)
				{
					//�^�[�Q�b�g�̏�����
					TgLength = fLength;
					fTgMove = fRotMove;
					fTgDest = fRotDest;
					fTgDiff = fRotDiff;
				}
			}
		}
		if (TgLength < 1000.0f)
		{//�˒��������ɓG������ꍇ
			if (fTgDiff > D3DX_PI)
			{
				fTgDiff -= D3DX_PI * 2;
			}
			else if (fTgDiff < -D3DX_PI)
			{
				fTgDiff += D3DX_PI * 2;
			}

			fTgMove += fTgDiff*1.0f;	//�ړ�����(�p�x)�̕␳

			if (fTgMove > D3DX_PI)
			{
				fTgMove -= D3DX_PI * 2;
			}
			else if (fTgMove < -D3DX_PI)
			{
				fTgMove += D3DX_PI * 2;
			}

			SetRot(fTgMove -D3DX_PI*2);	//�p�x���^�[�Q�b�g�Ɍ�����
		}
	}
}

//=============================================================================
// �s���p�^�[���̎擾
//=============================================================================
CEnemy::MOVEPATTERN CEnemy::GetMovePtn()
{
	return m_Moveptn;
}
