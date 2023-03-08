#include "Bullet.h"
#include"Application.h"
#include"renderer.h"
#include"Explosion.h"
#include"Enemy.h"
#include"Effect.h"
#include"Easing.h"
#include"Player.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[BULLET_TEX] = {};
bool CBullet::m_bUse = false;			//�����Ă邩�ǂ���
D3DXVECTOR3 CBullet::m_playerpos;	//�v���C���[�̈ʒu
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet() :CObject2D(OBJTYPE_BULLET)
{
	SetObjType(OBJTYPE_BULLET);
	m_eType = BTYPE_INVALID;
	m_frame = 0;
	m_bEnemy = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
	SetObjType(OBJTYPE_INVALID);
	m_eType = BTYPE_INVALID;
}

//=============================================================================
// ������
//=============================================================================
HRESULT  CBullet::Init(float Width, float Height)
{
 	CObject2D::Init(Width,  Height);
	SetSiz(D3DXVECTOR2(Width, Height));
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void  CBullet::Uninit()
{
 	CObject2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void  CBullet::Update()
{
	//�ʒu���X�V
	CObject2D::Update();

	//�ړ��ʂ̍X�V
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;

	//�����蔻��̏���
	if (Hit() == S_FALSE)
	{//�q�b�g���Ȃ������ꍇ
		if (m_eType == BTYPE_BLUEMSSILE)
		{//2���@�̒e�����ǔ�����
			SetHorming();
			//CEffect::Create(Pos, GetSiz(), GetRot());
		}
		SetPos(Pos);
	}
	else
	{//�e������ɓ��������ꍇ
		//�e������
		switch (m_eType)
		{
		case CBullet::BTYPE_REDBEAM:
			break;
		case CBullet::BTYPE_BLUEMSSILE:
			PlaySound(SOUND_LABEL_SE_EXPLOSION004);
			break;
		case CBullet::BTYPE_YELLOWDRILL:
			break;
		case CBullet::BTYPE_FUSIONSHOT:
			break;
		default:
			break;
		}
		Uninit();
		return;
	}

	if (m_eType == BTYPE_FUSIONSHOT)
	{//�r�[���̏���
		FusionBeam();
	}

	if (m_bUse == false && m_eType == BTYPE_FUSIONSHOT)
	{//�r�[�����g�p���ĂȂ��ꍇ����
		Uninit();
		return;
	}

	Offscreen();	//��ʊO�̏���
	m_NextHItTime--;
	m_frame++;
}

//=============================================================================
// �`��
//=============================================================================
void  CBullet::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	if (m_eType != (BTYPE_REDBEAM, BTYPE_BLUEMSSILE, BTYPE_YELLOWDRILL, BTYPE_FUSIONSHOT))
	{
		//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	CObject2D::Draw();

	if (m_eType != BTYPE_REDBEAM || m_eType != BTYPE_BLUEMSSILE || m_eType != BTYPE_YELLOWDRILL || m_eType != BTYPE_FUSIONSHOT)
	{
		//�ʏ�ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=============================================================================
// �f�[�^��ǂݍ���
//=============================================================================
HRESULT CBullet::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_REDBEAM.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_BLUEMISSILE.png",
		&m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG_YELLOWDRILL.png",
		&m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\FUSIONBEAM_001.png",
		&m_apTexture[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnemyBullet.png",
		&m_apTexture[4]);

	return S_OK;
}

//=============================================================================
// �f�[�^��j��
//=============================================================================
void CBullet::Unload()
{
	for (int i = 0; i < BULLET_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//�e�N�X�`���̔j��
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// �o���b�g����
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, EBULLETTYPE type)
{
	CBullet*pBullet = nullptr;
	pBullet = new CBullet;
	//���x�ݒ�
	pBullet->SetPos(pos);			//�ʒu�ݒ�
	pBullet->m_eType = type;
	pBullet->m_HitCount = DEFAULT_HIT;
	switch (pBullet->m_eType)
	{
	case CBullet::BTYPE_REDBEAM:
		pBullet->Init(BULLET_WIDTH_RED, BULLET_HEIGHT_RED);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[0]);	//�e�N�X�`���̐ݒ�
		break;

	case CBullet::BTYPE_BLUEMSSILE:
		pBullet->Init(BULLET_WIDTH_BLUE, BULLET_HEIGHT_BLUE);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -BLUE_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[1]);	//�e�N�X�`���̐ݒ�
		pBullet->Lockon();
		break;

	case CBullet::BTYPE_YELLOWDRILL:
		pBullet->Init(BULLET_WIDTH_YELLOW, BULLET_HEIGHT_YELLOW);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -YELLOW_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[2]);	//�e�N�X�`���̐ݒ�
		pBullet->m_HitCount = YELLOW_HIT;
		break;
	case CBullet::BTYPE_FUSIONSHOT:
		pBullet->Init(BEAM_WIDTH, SCREEN_HEIGHT);
		pBullet->m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[3]);	//�e�N�X�`���̐ݒ�
		break;

	case ENEMY_BULLET:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		pBullet->Lockon();
		break;

	case ENEMY_CANNON01:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_CANNON02:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_CANNON03:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;

		break;
	case ENEMY_CANNON04:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON06:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, 0.0f, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON07:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(-CANNON_SPEED, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON08:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(0.0f, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pBullet->m_bEnemy = true;
		
		break;
	
	case ENEMY_CANNON09:
		pBullet->Init(BULLET_SIZ, BULLET_SIZ);
		pBullet->m_Move = D3DXVECTOR3(CANNON_SPEED, -CANNON_SPEED, 0.0f);
		pBullet->BindTexture(m_apTexture[4]);	//�e�N�X�`���̐ݒ�
		pBullet->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		
		pBullet->m_bEnemy = true;
		break;

	case ENEMY_BEAMCANNON:
		pBullet->Init(BEAM_WIDTH, 200.0f);
		pBullet->m_Move = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pBullet->BindTexture(m_apTexture[3]);	//�e�N�X�`���̐ݒ�
		pBullet->m_bEnemy = true;
		
		break;

	default:
		break;
	}

	return pBullet;
}

//=============================================================================
//�����蔻��֘A
//=============================================================================
HRESULT CBullet::Hit()
{
	if (m_bEnemy==false)
	{//�v���C���[�̒e
		for (int i = 0; i < MAX_TYPE; i++)
		{
			for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
			{
				CObject*pObject;
				pObject = CObject::GetObj(nCnt, i);
				if (pObject != nullptr)
				{
					CObject::EObjType objType;
					objType = pObject->GetObjType(nCnt, i);			//��ނ̎擾

					D3DXVECTOR3 BulletPos = CObject2D::GetPos();
					D3DXVECTOR2 BulletSiz = CObject2D::GetSiz();	//����̃T�C�Y���擾

					if (objType == OBJTYPE_ENEMY)					//�G���ǂ�������Ȃ����񍇑̎�
					{//�G�ɍU��
						CEnemy *pEnemy = (CEnemy*)pObject;
						D3DXVECTOR3 EnemyPos = pEnemy->GetPos();	//����̈ʒu���擾
						D3DXVECTOR2 EnemySiz = pEnemy->GetSiz();	//����̃T�C�Y���擾
						if (pEnemy->GetMovePtn() != CEnemy::MOVE_BOSS_BASE &&
							CObject2D::Hit(BulletPos, EnemyPos, BulletSiz, EnemySiz) == true &&
							pEnemy->GetState() != CEnemy::ENEMYSTATE_DEATH)	//�����蔻��̏����I
						{
							m_HitCount--;
							//�_���[�W����
							switch (m_eType)
							{
							case CBullet::BTYPE_REDBEAM:
								pEnemy->Damage(RED_DAMAGE);
								break;

							case CBullet::BTYPE_BLUEMSSILE:
								pEnemy->Damage(BLUE_DAMAGE);
								break;

							case CBullet::BTYPE_YELLOWDRILL:
								pEnemy->Damage(YELLOW_DAMAGE);
								break;

							case CBullet::BTYPE_FUSIONSHOT:
								pEnemy->Damage(FUSION_DAMAGE);
								break;
							default:
								break;
							}
							if (m_eType != BTYPE_FUSIONSHOT&&m_HitCount<=0)
							{//�r�[���ȊO�͒e������
								return	S_OK;
							}
							else if (m_HitCount>0)
							{//�����蔻�肪��������܂ł̎���
								m_NextHItTime = DEFAULT_NEXTHIT;
							}
						}
					}
					else if (objType == OBJTYPE_BULLET)
					{//�r�[�����e�ɓ���������
						CBullet *pBullet = (CBullet*)pObject;
						D3DXVECTOR3 pBulletPos = pBullet->GetPos();	//�G�̒e�̈ʒu���擾
						D3DXVECTOR2 pBulletSiz = pBullet->GetSiz();	//�G�̒e�̃T�C�Y���擾
						if (CObject2D::Hit(BulletPos,pBulletPos, BulletSiz, pBulletSiz) == true &&
							pBullet->m_bEnemy == true)	//�����蔻��̏����I
						{//�G�̒e���r�[���ɓ��������ꍇ����
							m_HitCount--;
							if (m_NextHItTime<=0&&m_HitCount <= 0 && m_eType == BTYPE_FUSIONSHOT&&pBullet->m_eType != ENEMY_BEAMCANNON)
							{//�G�̎�C�ȊO�͏�����悤�ɂ���
								pBullet->Uninit();
								PlaySound(SOUND_LABEL_SE_DELETEBULLET);
							}
							else if (m_HitCount>0)
							{//�����蔻�肪��������܂ł̎���
								m_NextHItTime = DEFAULT_NEXTHIT;
							}
						}
					}
				}
			}
		}
	}
	else
	{//�G�̒e
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_PLAYER);
			if (pObject != nullptr)
			{
				CObject::EObjType objType;
				objType = pObject->GetObjType(nCnt, OBJTYPE_PLAYER);		//��ނ̎擾

				D3DXVECTOR3 BulletPos = CObject2D::GetPos();
				D3DXVECTOR2 BulletSiz = CObject2D::GetSiz();				//����̃T�C�Y���擾
					
				if (objType == OBJTYPE_PLAYER)
				{//�v���C���[�̏ꍇ
					CPlayer *pPlayer = (CPlayer*)pObject;
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();				//����̈ʒu���擾
					D3DXVECTOR2 PlayerSiz = pPlayer->GetSiz();				//����̃T�C�Y���擾
					if (CObject2D::Hit(BulletPos, PlayerPos, BulletSiz/2, PlayerSiz) == true && pPlayer->GetState() == CPlayer::PLAYERSTATE_NORMAL)	//�����蔻��̏����I
					{
						//�_���[�W����
						pPlayer->Damage();
					}
				}
			}
		}
	}
	return S_FALSE;
}

//=============================================================================
//�z�[�~���O�e�̃^�[�Q�b�g�ݒ�
//=============================================================================
void CBullet::Lockon()
{
	float fRotMove, fRotDest, fRotDiff, fTgMove = 0.0f, fTgDest = 0.0f, fTgDiff = 0.0f;	//�v�Z�E��r�p
	float TgLength = 1000.0f;	//�K���Ȑ��l���Ԃ�����

	if (m_bEnemy == true)
	{//�G�̒e
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_PLAYER);
			if (pObject != nullptr)
			{//�g�p�����ǂ�������
				D3DXVECTOR3 BulletPos = CObject2D::GetPos();						//�e�̍��W���擾
				CPlayer *pPlayer = (CPlayer*)pObject;
				fRotMove = atan2f(m_Move.x, m_Move.y);							//���݂̈ړ�����(�p�x)
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
					m_Target = nCnt;
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

			SetRot(fTgMove + D3DX_PI);	//�p�x���^�[�Q�b�g�Ɍ�����

			m_Move.x = sinf(fTgMove)*ENEMY_SPEED;
			m_Move.y = cosf(fTgMove)*ENEMY_SPEED;
		}
	}
	else
	{//�v���C���[�̒e
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			CObject*pObject;
			pObject = CObject::GetObj(nCnt, OBJTYPE_ENEMY);
			if (pObject != nullptr)
			{//�g�p�����ǂ�������
				D3DXVECTOR3 BulletPos = CObject2D::GetPos();						//�e�̍��W���擾
				if (pObject->GetObjType(nCnt, OBJTYPE_ENEMY) == OBJTYPE_ENEMY)		//�G���ǂ�������
				{
					CEnemy *pEnemy = (CEnemy*)pObject;
					if (pEnemy->GetState() != (CEnemy::ENEMYSTATE_APPEAR, CEnemy::ENEMYSTATE_DEATH))
					{
						fRotMove = atan2f(m_Move.x, m_Move.y);							//���݂̈ړ�����(�p�x)
																						//�ړI�̈ړ�����(�p�x)	����̍��W���玩������������
						fRotDest = atan2f(pEnemy->GetPos().x - BulletPos.x, pEnemy->GetPos().y - BulletPos.y);
						fRotDiff = fRotDest - fRotMove;									//�ړI�̈ړ������܂ł̍���
						D3DXVECTOR3 fDiff = pEnemy->GetPos() - BulletPos;
						float fLength = D3DXVec3Length(&fDiff);							//����
						if (fLength <= TgLength)
						{
							//�^�[�Q�b�g�̏�����
							TgLength = fLength;
							fTgMove = fRotMove;
							fTgDest = fRotDest;
							fTgDiff = fRotDiff;
							m_Target = nCnt;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
//�z�[�~���O�e�̐ݒ菈��
//=============================================================================
void CBullet::SetHorming()
{//�z�[�~���O�̐ݒ�

	float fRotMove, fRotDest, fRotDiff, fTgMove = 0.0f, fTgDest = 0.0f, fTgDiff = 0.0f;	//�v�Z�E��r�p
	float TgLength = 1000.0f;	//�K���Ȑ��l���Ԃ�����

	CObject*pObject;
	pObject = CObject::GetObj(m_Target, OBJTYPE_ENEMY);
	if (pObject != nullptr)
	{//�g�p�����ǂ�������
		D3DXVECTOR3 BulletPos = CObject2D::GetPos();												//�e�̍��W���擾
		if (pObject->GetObjType(m_Target, OBJTYPE_ENEMY) == OBJTYPE_ENEMY)							//���b�N�I�������G���ǂ�������
		{
			CEnemy *pEnemy = (CEnemy*)pObject;
			CEnemy::ENEMYSTATE Estate = pEnemy->GetState();
			if (Estate == CEnemy::ENEMYSTATE_NORMAL || Estate == CEnemy::ENEMYSTATE_DAMAGE)
			{
				fRotMove = atan2f(m_Move.x, m_Move.y);													//���݂̈ړ�����(�p�x)
				//�ړI�̈ړ�����(�p�x)	����̍��W���玩������������
				fRotDest = atan2f(pEnemy->GetPos().x - BulletPos.x, pEnemy->GetPos().y - BulletPos.y);
				fRotDiff = fRotDest - fRotMove;															//�ړI�̈ړ������܂ł̍���
				D3DXVECTOR3 fDiff = pEnemy->GetPos() - BulletPos;
				float fLength = D3DXVec3Length(&fDiff);				//����
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

		fTgMove += fTgDiff*0.8f;	//�ړ�����(�p�x)�̕␳

		if (fTgMove > D3DX_PI)
		{
			fTgMove -= D3DX_PI * 2;
		}
		else if (fTgMove < -D3DX_PI)
		{
			fTgMove += D3DX_PI * 2;
		}

		SetRot(fTgMove + D3DX_PI);	//�p�x���^�[�Q�b�g�Ɍ�����

		m_Move.x = sinf(fTgMove)*BLUE_SPEED;
		m_Move.y = cosf(fTgMove)*BLUE_SPEED;
	}
}

//=============================================================================
// ��ʊO�̏���
//=============================================================================
void CBullet::Offscreen()
{
	D3DXVECTOR3 pos = GetPos();
	if (m_eType!= BTYPE_FUSIONSHOT&&( pos.y > SCREEN_HEIGHT + GetSiz().y / 2|| pos.y < -GetSiz().y / 2|| pos.x > SCREEN_WIDTH + GetSiz().x / 2|| pos.x <  -GetSiz().x / 2))
	{//�n�_(Y���W)����ʂ̉��[�ɓ�������
		Uninit();
		return;
	}
}

//=============================================================================
//�r�[���̎g�p���
//=============================================================================
void CBullet::SetBeam(bool use)
{
	m_bUse = use;
}

//=============================================================================
//�r�[���̐ݒ�
//=============================================================================
void CBullet::FusionBeam()
{
	SetUV(GetUV(0).x, GetUV(1).x, GetUV(0).y - 0.1f, GetUV(1).y - 0.1f);

	m_playerpos.y -=SCREEN_HEIGHT / 2;
	SetPos(m_playerpos);
}

//=============================================================================
//�v���C���[�̈ړ��ʂ�n���p
//=============================================================================
 void CBullet::GetPlayerPos(D3DXVECTOR3 pos)
{
	 m_playerpos = pos;
}


