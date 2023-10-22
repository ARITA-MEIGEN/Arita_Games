//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Player.h"
#include"renderer.h"
#include"Application.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Option.h"
#include"Enemy.h"
#include"Item.h"
#include"Lifegauge.h"
#include"sound.h"
#include"Fade.h"
#include"Special.h"
#include"Effect.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"
#include"Game.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYER_TEX] = {};
int CPlayer::m_nLife=0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() :CObject2D(OBJTYPE_PLAYER)
{
	m_Move = { 0.0f,0.0f,0.0f };
	SetObjType(OBJTYPE_PLAYER);
	nCnt = 0;
	nCntState = 0;
	fPtntitle = 0.0f;
	m_state = PLAYERSTATE_APPEAR;
	m_nLife = PLAYER_DEFAULTLIFE;
	bFusion = false;
	m_nRedCT = 0;
	m_nBlueCT = 0;
	m_nYellowCT = 0;
	m_nSpecial = 0;

	//���z�u
	m_apOption[0] = COption::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));
	m_apOption[1] = COption::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
	SetObjType(OBJTYPE_INVALID);
}

//=============================================================================
// ������
//=============================================================================
HRESULT  CPlayer::Init(float Width, float Height)
{
	CObject2D::Init(Width, Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  CPlayer::Update()
{
	CObject2D::Update();				//�X�V
	Move();								//�ړ�
	CBullet::GetPlayerPos(GetPos());	//�e�Ɍ��݂̍��W�𑗂�
	COption::MemPos(GetPos());			//�ʒu���I�v�V�����ɋL�^������
	StateManagement();					//��ԊǗ�
	AutoShot();							//�A��

	if (bFusion == true&&bShot==true)
	{//���̍U����
		CSpecial::AddSpecial(-0.7f);
	}
}

//=============================================================================
// �`��
//=============================================================================
void  CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================================================================
// �v���C���[����
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer;
	if (pPlayer != nullptr)
	{// �|���S���̏���������
		pPlayer->Init(PLAYER_WIDTH, PLAYER_HEIGHT);
		pPlayer->SetPos(pos);
		COption::ResetPos(pPlayer->GetPos());			//���Z�b�g
	}
	return pPlayer;
}

//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::Move(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	D3DXVECTOR3 pos = GetPos();

	if (pKeyboard->GetPress(DIK_W) || JOYPAD_UP)
	{
		m_Move.y = -PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_A)||JOYPAD_LEFT)
		{
			m_Move.x = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if(pKeyboard->GetPress(DIK_D)||JOYPAD_RIGHT)
		{
			m_Move.x = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_S) || JOYPAD_DOWN)
	{
		m_Move.y = PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_A)||JOYPAD_LEFT)
		{
			m_Move.x = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_D)||JOYPAD_RIGHT)
		{
			m_Move.x = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_A) || JOYPAD_LEFT)
	{
		m_Move.x = -PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_W)||JOYPAD_UP)
		{
			m_Move.y = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_S)||JOYPAD_DOWN)
		{
			m_Move.y = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}
	else if (pKeyboard->GetPress(DIK_D) || JOYPAD_RIGHT)
	{
		m_Move.x = PLAYER_MOVE;
		if (pKeyboard->GetPress(DIK_W)||JOYPAD_UP)
		{
			m_Move.y = -PLAYER_MOVE;
			m_Move *= 0.75;
		}
		else if (pKeyboard->GetPress(DIK_S)||JOYPAD_DOWN)
		{
			m_Move.y = PLAYER_MOVE;
			m_Move *= 0.75;
		}
	}

	if (pKeyboard->GetTrigger(DIK_LSHIFT)||pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A)|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B))
	{//����
		Fusion();
	}

	//�ʒu���X�V
	if (bFusion==true)
	{
		m_Move.x *= 0.5f;
		m_Move.y *= 0.5f;
	}
	pos.x += m_Move.x;
	pos.y += m_Move.y;
	m_Move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�ʒu�̔��f
	SetPos(pos);

	//��ʊO�ɂ������ꍇ
	Offscreen();

}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CPlayer::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_RED001.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\FUSION001.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CPlayer::Unload()
{
	for (int i = 0; i < PLAYER_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �����蔻��܂��̂��
//=============================================================================
void CPlayer::Hit()
{
	for (int j = 0; j < MAX_TYPE; j++)
	{
		for (int i = 0; i < MAX_POLYGON; i++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(i,j);
			if (pObject != nullptr)
			{
				CObject::EObjType objType;
				objType = pObject->GetObjType(i,j);			//��ނ̎擾

				D3DXVECTOR3 PlayerPos = CObject2D::GetPos();
				D3DXVECTOR2 PlayerSiz = CObject2D::GetSiz();	//����̃T�C�Y���擾

				switch (objType)
				{
				case OBJTYPE_ENEMY:
				{
					CEnemy *pEnemy = (CEnemy*)pObject;
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();	//����̈ʒu���擾
					D3DXVECTOR2 EnemySiz = pEnemy->GetSiz();	//����̃T�C�Y���擾
					if (CObject2D::Hit(PlayerPos, EnemyPos, PlayerSiz / 2, EnemySiz) == true&&pEnemy->GetState()!=(CEnemy::ENEMYSTATE_APPEAR, CEnemy::ENEMYSTATE_DEATH))
						//�����蔻��̏��� 2�Ŋ����Ă���͓̂����蔻��̒���
					{
						//�_���[�W����                                            
						Damage();
					}
				}
				break;

				case OBJTYPE_ITEM:
				{
					CItem *pItem = (CItem*)pObject;
					D3DXVECTOR3 ItemPos = pItem->GetPos();	//�A�C�e���̈ʒu���擾
					D3DXVECTOR2  ItemSiz = pItem->GetSiz();	//�A�C�e���̃T�C�Y���擾
					if (CObject2D::Hit(PlayerPos, ItemPos, PlayerSiz, ItemSiz) == true)	//�����蔻��̏����I2�Ŋ����Ă���͓̂����蔻��̒���
					{
						PlaySound(SOUND_LABEL_SE_HEAL);
						m_nLife++;
						CLife::LifeRecovery();
						pItem->Uninit();
						if (m_nLife <= 3)
						{
							m_apOption[m_nLife - 2] = COption::Create(GetPos());
						}
						else if (m_nLife >= PLAYER_MAXLIFE)
						{//�ő�̗͂𒴂����ꍇ
							m_nLife = PLAYER_MAXLIFE;
						}
					}

				}
				default:
					break;
				}
			}
		}
	}
}

//=============================================================================
// �̗͂̌���
//=============================================================================
int CPlayer::GetLife()
{
	return m_nLife;
}

//=============================================================================
// �A�ˏ���
//=============================================================================
void CPlayer::AutoShot()
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	if (bFusion == false)
	{//���̂��Ă��Ȃ��Ƃ�
		if (pKeyboard->GetPress(DIK_SPACE) == true||JOYPAD_SHOT)
		{
			if (ShotTimer % RED_RATE == 0 && m_nRedCT <= 0)
			{//��
				Shot(0);
				PlaySound(SOUND_LABEL_SE_REDBEAM);
				m_nRedCT = RED_RATE;
			}
			if (ShotTimer % BLUE_RATE == 0 && m_apOption[0] != nullptr&&m_nBlueCT <= 0)
			{//��
				Shot(1);
				PlaySound(SOUND_LABEL_SE_BLUEMISSILE);
				m_nBlueCT = BLUE_RATE;
			}
			if (ShotTimer % YELLOW_RATE == 0 && m_apOption[1] != nullptr&&m_nYellowCT <= 0)
			{//��
				Shot(2);
				m_nYellowCT = YELLOW_RATE;
			}
			ShotTimer++;
		}
		else
		{
			ShotTimer = 0;
		}
	}
	else
	{//���̎�
		if ((bShot == false) &&
			(CSpecial::GetSpecial() > 0.0f) && (pKeyboard->GetPress(DIK_SPACE) || JOYPAD_SHOT))
		{
			Shot(0);
			bShot = true;
			CBullet::SetBeam(true);
			PlaySound(SOUND_LABEL_SE_FUSIONSHOT);
		}
	}

	if (CSpecial::GetSpecial() <= 0.0f && (bFusion == true))
	{//�Q�[�W���Ȃ��Ȃ����ꍇ
		Separation();
	}

	if ((bShot == true) &&
		(pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_X)==false &&pJoyPad->GetJoypadPress(CInputJoyPad::JOYKEY_Y)==false &&
			pKeyboard->GetPress(DIK_SPACE)==false)  ||
			(bFusion==false))
	{//�������Ƃ�
		bShot = false;
		CBullet::SetBeam(false);
		StopSound(SOUND_LABEL_SE_FUSIONSHOT);
	}


	m_nRedCT--;
	m_nBlueCT--;
	m_nYellowCT--;
}

//=============================================================================
// �ˌ�
//=============================================================================
void CPlayer::Shot(int number)
{
	//�ˌ�
	if (bFusion == false)
	{//�����U��
		D3DXVECTOR3 pos = GetPos();

		switch (number)
		{
		case 0:
			pos.y -= PLAYER_HEIGHT;
			CBullet::Create(pos, CBullet::BTYPE_REDBEAM);
			break;
		case 1:
			pos = m_apOption[0]->GetPos();
			pos.y -= OPTION_HEIGHT;
			CBullet::Create(pos, (CBullet::BTYPE_BLUEMSSILE));
			break;

		case 2:
			pos = m_apOption[1]->GetPos();
			pos.y -= OPTION_HEIGHT;
			CBullet::Create(pos, (CBullet::BTYPE_YELLOWDRILL));
			break;
		default:
			break;
		}
	}
	else if (bFusion == true)
	{//���̍U��
		D3DXVECTOR3 pos = GetPos();
		pos.y -= SCREEN_HEIGHT/2;
		CBullet::Create(pos, CBullet::BTYPE_FUSIONSHOT);
		
	}
}

//=============================================================================
// ��ʊO�̏���
//=============================================================================
void CPlayer::Offscreen()
{
	D3DXVECTOR3 pos = GetPos();
	if (pos.y > SCREEN_HEIGHT - PLAYER_HEIGHT / 2)
	{//�n�_(Y���W)����ʂ̉��[�ɓ�������
		pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT / 2;
	}
	else if (pos.y < PLAYER_HEIGHT / 2)
	{//�n�_(Y���W)����ʂ̏�[�ɓ�������
		pos.y = PLAYER_HEIGHT / 2;
	}
	if (pos.x > SCREEN_WIDTH - PLAYER_WIDTH / 2)
	{//�n�_(X���W)����ʂ̉E�[�ɓ�������
		pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
	}
	else if (pos.x < PLAYER_WIDTH / 2)
	{//�n�_(X���W)����ʂ̍��[�ɓ�������
		pos.x = PLAYER_WIDTH / 2;
	}
	SetPos(pos);

	//��ʓ��ɓ����Ă���NORMAL�ɖ߂�
	if (pos.x <= SCREEN_WIDTH + GetSiz().x / 2 &&
		pos.x >= -GetSiz().x / 2 &&
		pos.y <= SCREEN_HEIGHT + GetSiz().y / 2 &&
		pos.y >= -GetSiz().y / 2 &&
		m_state == PLAYERSTATE_APPEAR)
	{//��ʓ��ɓ�������
		m_state = PLAYERSTATE_NORMAL;
	}
}

//=============================================================================
// ���̂̏���
//=============================================================================
void CPlayer::Fusion()
{
	if (m_nLife >= PLAYER_DEFAULTLIFE)
	{
		if (bFusion == true)
		{//���̉���
			Separation();
		}
		else if (bFusion == false && CSpecial::GetSpecial()>0.0f)
		{//����
			PlaySound(SOUND_LABEL_SE_UNION);
			bFusion = true;
			BindTexture(m_apTexture[1]);	//�e�N�X�`���̐ݒ�
			for (int i = 0; i < MAX_OPTION; i++)
			{
				m_apOption[i]->Uninit();
			}
		}
	}
}

//=============================================================================
// ��ԊǗ�
//=============================================================================
void  CPlayer::StateManagement()
{
	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:
		//�ʏ펞�̂ݓ����蔻��̏������s��
		Hit();
		break;

	case PLAYERSTATE_DAMAGE:
		nCnt++;
		if ((nCnt % 5) == 0)
		{
			fPtntitle = 1 - fPtntitle;
		}

		//�|���S�����_���[�W�F�ɐݒ�
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, fPtntitle));

		if (nCntState <= 0)
		{//���G���Ԃ��������ꂽ�Ƃ�

			fPtntitle = 0;
			nCnt = 0;

			m_state = PLAYERSTATE_NORMAL;

			//�|���S����ʏ�F�ɐݒ�
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	case PLAYERSTATE_DEATH:
		if (nCntState == NEXT_TIME-1)
		{//����ōŏ���1f�����ʂ�
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 30; i++)
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
			PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		}

		if (nCntState <= 0)
		{
			if (CFade::Get() == CFade::FADE_NONE)
			{
				CFade::Set(CApplication::MODE_RESULT);
				m_state = PLAYERSTATE_APPEAR;
			}
		}
		break;
	}
	
	nCntState--;
}

//=============================================================================
// �_���[�W�ݒ�
//=============================================================================
void CPlayer::Damage()
{
	if (m_state == PLAYERSTATE_NORMAL&&m_nLife >= 1&&CGame::GetGame()!=CGame::GAME_END)
	{
		m_nLife--;
		CLife::LifeDecrease();
		m_state = PLAYERSTATE_DAMAGE;
		nCntState = 60;				//���G����

		if (m_nLife <= 0)
		{
			//��������
			PlaySound(SOUND_LABEL_SE_EXPLOSION005);
			m_state = PLAYERSTATE_DEATH;
			CApplication::StopTime(60);
			nCntState = NEXT_TIME;				//�t�F�[�h�܂ł̎���
			CApplication::SlowTime(true);			//�X���[�ɂ���
		}
		else if (m_nLife <= 2)
		{
			if (bFusion == true)
			{//���̏�Ԃł̔�e
				Separation();
			}
			for (int i = 0; i < 30; i++)
			{//�I�v�V��������
				CEffect::Create(m_apOption[m_nLife - 1]->GetPos(),												//�ʒu
					m_apOption[m_nLife - 1]->GetSiz()*2.0f,														//�傫��
					GetRot(),																					//����
					D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,	//x
						cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f,			//y
						0.0f),																					//z
					600,																						//����
					D3DXCOLOR(1.0f, 0.40f, 0.0f, 1.0f));														//�F
			}
			m_apOption[m_nLife - 1]->Uninit();	//�̗͂ɉ����ċ@�̂�j��
			m_apOption[m_nLife - 1] = nullptr;
			PlaySound(SOUND_LABEL_SE_EXPLOSION002);
		}
		else if (m_nLife >= PLAYER_MAXLIFE)
		{//�ő�̗͂𒴂����ꍇ
			m_nLife = PLAYER_MAXLIFE;
		}
	}
}

//=============================================================================
// �v���C���[�̕���
//=============================================================================
void CPlayer::Separation()
{
	PlaySound(SOUND_LABEL_SE_SEPARATION);
	bFusion = false;
	BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
	for (int i = 0; i < MAX_OPTION; i++)
	{
		m_apOption[i] = COption::Create(GetPos());
	}
}

//=============================================================================
// �v���C���[�̏�Ԏ擾
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState()
{
	return m_state;
}
