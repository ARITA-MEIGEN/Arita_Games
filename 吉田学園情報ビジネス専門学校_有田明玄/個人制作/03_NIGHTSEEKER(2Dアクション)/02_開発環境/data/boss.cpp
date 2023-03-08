//=================================================
// Content     (�{�X�̐ݒ�)(Boss.cpp)
// Author     : �L�c����
//=================================================
#include"Boss.h"
#include"Player.h"
#include"sound.h"
#include"game.h"
#include"Attack.h"
#include"effect.h"
#include"bullet.h"
#include"score.h"

//�}�N����`
#define INV_TIME	(10)

//�X�^�e�B�b�N�ϐ�
static LPDIRECT3DTEXTURE9 s_apTextureBoss[NUM_BOSS] = {};	//�{�X�̃e�N�X�`��
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffBoss = NULL;		//�{�X�̒��_�o�b�t�@
static BOSS s_Boss;											//�{�X�̏��

//�v���g�^�C�v�錾
static void StateBoss(void);			//��ԕω��̐ݒ�
static void OutScreenBoss(void);		//��ʊO�̏���
//============================
//�{�X�̏���������
//============================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\boss000.png",
		&s_apTextureBoss[0]);

	//�{�X�̏��̏�����
		s_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Boss.move = D3DXVECTOR3(1.5f, 0.0f, 0.0f);
		s_Boss.nType = 0;
		s_Boss.nLife = 0;
		s_Boss.bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
		s_Boss.nCntAnim = 0;
		s_Boss.nPtnAnim = 0;
		s_Boss.state = BOSSSTATE_NORMAL;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBoss,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBoss,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBoss->Unlock();
}
//============================
//�{�X�̏I������
//============================
void UninitBoss(void)
{
	//�����̒�~
	StopSound();
	for (int nCntBoss = 0; nCntBoss < NUM_BOSS; nCntBoss++)
	{
		//�e�N�X�`���̔j��
		if (s_apTextureBoss[nCntBoss] != NULL)
		{
			s_apTextureBoss[nCntBoss]->Release();
			s_apTextureBoss[nCntBoss] = NULL;
		}
	}

	//���_�o�b�t�@��j��
	if (s_pVtxBuffBoss != NULL)
	{
		s_pVtxBuffBoss->Release();
		s_pVtxBuffBoss = NULL;
	}
}
//============================
//�{�X�̍X�V����
//============================
void UpdateBoss(void)
{
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
	if (s_Boss.bUse == true)
	{//�{�X���g�p����Ă���ꍇ
	 //�ʒu�̍X�V
		if (s_Boss.pos.x <= SCREEN_WIDTH)
		{
			s_Boss.posOld = s_Boss.pos;
			s_Boss.pos.x += s_Boss.move.x;
			s_Boss.pos.y += s_Boss.move.y;
		}
		//�u���b�N�̏�ɏ���Ă���ꍇ
		if (s_Boss.pBlock != NULL)
		{
			//�u���b�N�̃^�C�v���Q��
			if (s_Boss.pBlock->nType == 1)
			{
				//�u���b�N�̈ړ��ʂ����Z
				s_Boss.pos += s_Boss.pBlock->move;
			}
		}
		//�����蔻��
		CollisionBlock(&s_Boss.pos, &s_Boss.posOld, &s_Boss.move, BOSS_SIZE, BOSS_SIZE, &s_Boss.pBlock);
		
		if (CollisionWeapon(&s_Boss.pos, &s_Boss.posOld, &s_Boss.move, BOSS_SIZE, BOSS_SIZE) == true && s_Boss.state != BOSSSTATE_DAMAGE)
		{
			HitBoss(100);
		}

		//�J�E���^�[�̍X�V
		if ((s_Boss.nCntAnim++ % 180) == 0)
		{//�A�j���[�V�����̐ݒ�
			s_Boss.nAtkUse ^= 1;
		}

		//�U�����Ȃ�
		if (s_Boss.nAtkUse == 1&&s_Boss.state!=BOSSSTATE_APPEAR&&s_Boss.state!=BOSSSTATE_DEATH)
		{
			if (s_Boss.nCntAnim%30==0)
			{
				PlaySound(SOUND_LABEL_SE_FIRE);
			SetBullet(s_Boss.pos- D3DXVECTOR3(0.0f, 100.0f, 0.0f),D3DXVECTOR3(1.0f,1.0f,0.0f),
				500,40.0f,40.0f);
			}
		}

		//��ʂ̒����ɗ������̐ݒ�
		CenterPlayer(&s_Boss.pos);

		//�{�X����ʊO�ɍs�������̏���
		OutScreenBoss();

		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove+ s_Boss.nAtkUse), 0.5f);	//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse + 1), 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(s_Boss.nPtnAnim + s_Boss.nDirectionMove + s_Boss.nAtkUse + 1), 1.0f);
		s_Boss.move.y =(s_Boss.state==BOSSSTATE_APPEAR)? 0.0f:10.0f;
	}
		//�{�X�̏�ԊǗ�
		StateBoss();

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBoss->Unlock();
}
//==============================
//�{�X�̕`�揈��
//==============================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (s_Boss.bUse == true&&s_Boss.state!=BOSSSTATE_APPEAR)
	{//�{�X���g�p����Ă���

	 //�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_apTextureBoss[0]);

		//�|���S���̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
			0,										//���_�̊J�n�ꏊ
			2);										//�v���~�e�B�u�̐�
	}
}
//=====================
//�{�X�̐ݒ菈��
//=====================
void SetBoss(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (s_Boss.bUse == false&&s_Boss.state!=BOSSSTATE_DEATH)
	{//�{�X���g�p����Ă��Ȃ�
	 //�{�X�̏��̐ݒ�
		s_Boss.pos = pos;
		s_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_Boss.nLife = 2000;
		s_Boss.bUse = true;	//�g�p���Ă����Ԃɂ���
		s_Boss.state = BOSSSTATE_APPEAR;
		s_Boss.nAtk = 300;
		s_Boss.nCounterState = 180;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[1].pos = D3DXVECTOR3(+BOSS_SIZE / 2, -BOSS_SIZE, 0.0f) + s_Boss.pos;
		pVtx[2].pos = D3DXVECTOR3(-BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;
		pVtx[3].pos = D3DXVECTOR3(+BOSS_SIZE / 2, 0.0f, 0.0f) + s_Boss.pos;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�����̒�~
		StopSound(SOUND_LABEL_BGM000);

		PlaySound(SOUND_LABEL_SE_BOSS);

	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBoss->Unlock();
}
//=======================
//�{�X�̃q�b�g����
//=======================
void HitBoss(int nDamage)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	s_Boss.nLife -= nDamage;
	if (s_Boss.nLife <= 0)
	{//�̗͂��O�ɂȂ�����
		s_Boss.bUse = false;
		//pPlayer->nLife = MAX_PLIFE;		//�ő僉�C�t
		s_Boss.nCounterState = 60;
		s_Boss.state = BOSSSTATE_DEATH;
		//�����̐ݒ�
		for (int e = 0; e < 30; e++)
		{
			SetEffect(
				s_Boss.pos-D3DXVECTOR3(0.0f, BOSS_SIZE/2, 0.0f)	//�ʒu�̐ݒ�
				//�ړ��ʂ̐ݒ�																		
				, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f
				,			  cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 1.0f + 0.0f, 0.0f)
				, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)		//���_�J���[�̐ݒ�
				, 50									//���a�̑傫���̐ݒ�
				, 60									//����(����܂�Ӗ��Ȃ�)
				, true									//���Z�������邩�ǂ���
				, 1);									//�����ڂ̃e�N�X�`�����g�����ǂ���
		}
		AddScore(50000);

		PlaySound(SOUND_LABEL_SE_EXPLOSION);
	}
	else
	{//�����Ă�ꍇ
		s_Boss.state = BOSSSTATE_DAMAGE;
		s_Boss.nCounterState = INV_TIME;//�_���[�W���Ԃ�ۂ��Ԃ�ݒ�
		pPlayer->nLife += 20;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		//�|���S�����_���[�W�F�ɐݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		s_pVtxBuffBoss->Unlock();

		//PlaySound(SOUND_LABEL_SE_HIT);
	}
}
//=====================
//��ԕω��̐ݒ�
//=====================
void StateBoss(void)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	switch (s_Boss.state)
	{
	case BOSSSTATE_APPEAR:
		s_Boss.nCounterState--;
		SetEffect(
			s_Boss.pos +
			D3DXVECTOR3((float)(rand() % 20 + 10), (float)(rand() % 20 + 10), 0.0f)		//�ʒu�̐ݒ�
																						//�ړ��ʂ̐ݒ�																		
			, D3DXVECTOR3(-sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f
				, -cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f, 0.0f)
			, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f)		//���_�J���[�̐ݒ�
			, 50									//���a�̑傫���̐ݒ�
			, 900									//����(����܂�Ӗ��Ȃ�)
			, true									//���Z�������邩�ǂ���
			, 1);									//�����ڂ̃e�N�X�`�����g�����ǂ���
		if (s_Boss.nCounterState <= 0)
		{
			PlaySound(SOUND_LABEL_BGM001);
			s_Boss.state = BOSSSTATE_NORMAL;
		}
		break;
	case BOSSSTATE_NORMAL:
		s_Boss.nDirectionMove = (pPlayer->pos.x > s_Boss.pos.x) ? 0 : 2;
		break;
	case BOSSSTATE_DAMAGE:
		s_Boss.nCounterState--;
		if (s_Boss.nCounterState <= 0)
		{
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			s_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			s_Boss.state = BOSSSTATE_NORMAL;

			//�|���S����ʏ�F�ɐݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���_�o�b�t�@���A�����b�N
			s_pVtxBuffBoss->Unlock();
		}
		break;
	case BOSSSTATE_DEATH:
		s_Boss.nCounterState--;
		if (s_Boss.nCounterState <= 0)
		{
			s_Boss.bUse = false;
			s_Boss.move.x = 0;
			//���[�h�̐ݒ�(���U���g��ʂɈڍs)
			SetGameState(GAMESTATE_CLEAR);
			return;
		}
		break;
	}
}
//=====================
//��ʊO�̏���
//=====================
static void OutScreenBoss(void)
{
	if (s_Boss.pos.x <= -BOSS_SIZE)
	{//��ʊO�ɏo���ꍇ�̏���(���[)
		s_Boss.pos.x = BOSS_SIZE;
		s_Boss.bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
	if (s_Boss.pos.y >= SCREEN_HEIGHT + BOSS_SIZE)
	{//��ʊO�ɏo���ꍇ�̏���(���[)
		s_Boss.bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
}
//=====================
//�{�X�̓����蔻��
//=====================
void CollisionBoss(D3DXVECTOR3 *pPos, float Width, float Height)
{
	if (s_Boss.bUse == true)
	{//�v���C���[���g�p����Ă��� 
	 //�v���C���[�ɑ��肪�Ԃ�������
		if (pPos->y  >= s_Boss.pos.y - BOSS_SIZE
			&& pPos->y - Height <= s_Boss.pos.y
			&&pPos->x - Width / 2 <= s_Boss.pos.x + BOSS_SIZE / 2 - 50
			&& pPos->x + Width / 2 >= s_Boss.pos.x - BOSS_SIZE / 2 + 50)
		{//�v���C��-�ƃv���C���[������������
			HitPlayer(s_Boss.nAtk);
		}
	}
}
//=====================
//�{�X�̎擾����
//=====================
BOSS *GetBoss(void)
{//�{�X�̃|�C���^�����Z�b�g
	return &s_Boss;
}