//=================================================
// Content     (�G�̐ݒ�)(Enemy.cpp)
// Author     : �L�c����
// LastUpdate : (�X�V��2021/08/14)
// Since      : (�쐬��2021/07/06)
//=================================================
#include"enemy.h"
#include"Player.h"
#include"sound.h"
#include"game.h"
#include"Attack.h"
#include"effect.h"
#include"score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//�G�̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//�G�̒��_�o�b�t�@
static Enemy s_aEnemy[MAX_ENEMY];						//�G�̏��

//�v���g�^�C�v�錾
static void SettingbyTypeEnemy(int nCnt);	//�^�C�v���Ƃ̐ݒ�
static void StateEnemy(int nCnt);			//��ԕω��̐ݒ�
static void OutScreenEnemy(int nCnt);		//��ʊO�̏���
//============================
//�G�̏���������
//============================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy004.png",
		&g_apTextureEnemy[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy001.png",
		&g_apTextureEnemy[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy002.png",
		&g_apTextureEnemy[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy003.png",
		&g_apTextureEnemy[3]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		s_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEnemy[nCntEnemy].nType = 0;
		s_aEnemy[nCntEnemy].nLife = 0;
		s_aEnemy[nCntEnemy].nBullettimer = 0;
		s_aEnemy[nCntEnemy].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
		s_aEnemy[nCntEnemy].nCntAnim = 0;
		s_aEnemy[nCntEnemy].nPtnAnim = 0;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

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

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//============================
//�G�̏I������
//============================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		s_aEnemy[i].bUse = false;
	}
}

//============================
//�G�̍X�V����
//============================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���ꍇ
			//�ʒu�̍X�V
				s_aEnemy[nCntEnemy].posOld = s_aEnemy[nCntEnemy].pos;
				if (s_aEnemy[nCntEnemy].pos.x<=SCREEN_WIDTH)
				{
					s_aEnemy[nCntEnemy].pos.x += s_aEnemy[nCntEnemy].move.x;
				} 
				s_aEnemy[nCntEnemy].pos.y += s_aEnemy[nCntEnemy].move.y;

				//��ʂ̒����ɗ������̐ݒ�
				CenterPlayer(&s_aEnemy[nCntEnemy].pos);

				//�u���b�N�̏�ɏ���Ă���ꍇ
				if (s_aEnemy[nCntEnemy].pBlock != NULL)
				{
					//�u���b�N�̃^�C�v���Q��
					if (s_aEnemy[nCntEnemy].pBlock->nType == 1)
					{
						//�u���b�N�̈ړ��ʂ����Z
						s_aEnemy[nCntEnemy].pos += s_aEnemy[nCntEnemy].pBlock->move;
					}
				}
				//�����蔻��
				if (CollisionBlock(&s_aEnemy[nCntEnemy].pos, &s_aEnemy[nCntEnemy].posOld, &s_aEnemy[nCntEnemy].move, ENEMY_SIZE, ENEMY_SIZE, &s_aEnemy[nCntEnemy].pBlock) == true)
				{
					s_aEnemy[nCntEnemy].move.y = 0;
				}

				if (CollisionWeapon(&s_aEnemy[nCntEnemy].pos, &s_aEnemy[nCntEnemy].posOld, &s_aEnemy[nCntEnemy].move, ENEMY_SIZE, ENEMY_SIZE) == true && s_aEnemy[nCntEnemy].state != ENEMYSTATE_DAMAGE)
				{
					HitEnemy(nCntEnemy, 100);
				}

				if (s_aEnemy[nCntEnemy].nCntAnim++ % 10 == 0)
				{//�A�j���[�V�����̐ݒ�
					s_aEnemy[nCntEnemy].nPtnAnim++;
					if (s_aEnemy[nCntEnemy].nPtnAnim % 3 == 0)
					{
						s_aEnemy[nCntEnemy].nPtnAnim = 0;
					}
				}

				//�G�̏�ԊǗ�
				StateEnemy(nCntEnemy);

				//�G����ʊO�ɍs�������̏���
				OutScreenEnemy(nCntEnemy);

				s_aEnemy[nCntEnemy].move.y += 1.0f;
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[1].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
				pVtx[3].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3), 0.25f);	//�E���ɍ��W���w��
				pVtx[1].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3 + 1), 0.25f);
				pVtx[2].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3), 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.33f*(s_aEnemy[nCntEnemy].nPtnAnim % 3 + 1), 0.5f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//==============================
//�G�̕`�揈��
//==============================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���

		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[s_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				nCntEnemy * 4,							//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}
	}
}
//=====================
//�G�̐ݒ菈��
//=====================
void SetEnemy(D3DXVECTOR3 pos, int type)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (s_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ�
			//�G�̏��̐ݒ�
			s_aEnemy[nCntEnemy].pos = pos;
			s_aEnemy[nCntEnemy].nType = type;
			s_aEnemy[nCntEnemy].nBullettimer = 0;
			s_aEnemy[nCntEnemy].bUse = true;	//�g�p���Ă����Ԃɂ���

			//�^�C�v�ʂ̐ݒ�
			SettingbyTypeEnemy(nCntEnemy);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
			pVtx[1].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, -ENEMY_SIZE, 0.0f)+s_aEnemy[nCntEnemy].pos;
			pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;
			pVtx[3].pos = D3DXVECTOR3(+ENEMY_SIZE / 2, 0.0f, 0.0f) + s_aEnemy[nCntEnemy].pos;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//=======================
//�G�̃q�b�g����
//=======================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;
	Player*pPlayer = GetPlayer();
	s_aEnemy[nCntEnemy].nLife -= nDamage;
	if (s_aEnemy[nCntEnemy].nLife <= 0)
	{//�̗͂��O�ɂȂ�����
		s_aEnemy[nCntEnemy].bUse = false;
		pPlayer->nLife += 400;
		//�����̐ݒ�
		for (int e = 0; e < 20; e++)
		{
			SetEffect(
				s_aEnemy[nCntEnemy].pos- D3DXVECTOR3(0.0f,ENEMY_SIZE/2,0.0f) 
				+D3DXVECTOR3((float)(rand() % 20 - 10), (float)(rand() % 20 - 10), 0.0f)		//�ʒu�̐ݒ�
				//�ړ��ʂ̐ݒ�																		
				, D3DXVECTOR3(sinf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) / 3.0f + 0.0f
							, cosf((float)(rand() % 629 - 314) / 100.0f)*(float)(rand() % 10) /3.0f + 0.0f, 0.0f)
				, D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.5f)		//���_�J���[�̐ݒ�
				, 30									//���a�̑傫���̐ݒ�
				, 30									//����(����܂�Ӗ��Ȃ�)
				, true									//���Z�������邩�ǂ���
				, 1);									//�����ڂ̃e�N�X�`�����g�����ǂ���
		}
			//�������̍Đ�
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			//�X�R�A�̒ǉ�����
			AddScore(20000);
		if (pPlayer->nLife>= MAX_PLIFE)
		{
			pPlayer->nLife = MAX_PLIFE;
		}
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);
	}
	else
	{//�����Ă�ꍇ
		s_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		s_aEnemy[nCntEnemy].nCounterState = 15;//�_���[�W���Ԃ�ۂ��Ԃ�ݒ�

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//�|���S�����_���[�W�F�ɐݒ�
		pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffEnemy->Unlock();

		//PlaySound(SOUND_LABEL_SE_HIT);
	}
}
//=====================
//�^�C�v���Ƃ̐ݒ�
//=====================
static void SettingbyTypeEnemy(int nCnt)
{
		switch (s_aEnemy[nCnt].nType)
		{
		case 0:
			s_aEnemy[nCnt].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			s_aEnemy[nCnt].nLife = 200;
			s_aEnemy[nCnt].bUse = true;	//�g�p���Ă��Ȃ���Ԃɂ���
			s_aEnemy[nCnt].nAtk = 500;
			break;
		case 1:
			s_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			s_aEnemy[nCnt].nLife = 200;
			s_aEnemy[nCnt].bUse = true;	//�g�p���Ă��Ȃ���Ԃɂ���
			s_aEnemy[nCnt].nAtk = 500;
			break;
		default:
			break;
		}
}
//=====================
//��ԕω��̐ݒ�
//=====================
static void StateEnemy(int nCnt)
{
	VERTEX_2D*pVtx;
	switch (s_aEnemy[nCnt].state)
	{
	case ENEMYSTATE_NORMAL:
		break;
	case ENEMYSTATE_DAMAGE:
		s_aEnemy[nCnt].nCounterState--;
		if (s_aEnemy[nCnt].nCounterState <= 0)
		{
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			s_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;
			pVtx += 4 * nCnt;	//���_�f�[�^�̃|�C���^��4���i�߂�

			//�|���S����ʏ�F�ɐݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffEnemy->Unlock();
		}
		break;
	}
}
//=====================
//��ʊO�̏���
//=====================
static void OutScreenEnemy(int nCnt)
{
	if (s_aEnemy[nCnt].pos.x <= -ENEMY_SIZE)
	{//��ʊO�ɏo���ꍇ�̏���(���[)
		s_aEnemy[nCnt].pos.x = ENEMY_SIZE;
		s_aEnemy[nCnt].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
	if (s_aEnemy[nCnt].pos.y >= SCREEN_HEIGHT + ENEMY_SIZE)
	{//��ʊO�ɏo���ꍇ�̏���(���[)
		s_aEnemy[nCnt].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
}
//=====================
//�G�l�~�[�̓����蔻��
//=====================
void CollisionEnemy(D3DXVECTOR3 *pPos, float Width, float Height)
{
	//�v���C���[�̂��G�ɓ����������̔���͕ʁX�ō��Ȃ��Ƃ����Ȃ�
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (s_aEnemy[nCnt].bUse == true)
		{//�v���C���[���g�p����Ă��� 
		 //�v���C���[�ɑ��肪�Ԃ�������
			if (pPos->y >= s_aEnemy[nCnt].pos.y - ENEMY_SIZE
				&& pPos->y - Height <= s_aEnemy[nCnt].pos.y
				&&pPos->x - Width / 2 <= s_aEnemy[nCnt].pos.x + ENEMY_SIZE / 2
				&& pPos->x + Width / 2 >= s_aEnemy[nCnt].pos.x - ENEMY_SIZE / 2)
			{//�v���C��-�ƃv���C���[������������
				HitPlayer(s_aEnemy[nCnt].nAtk);
			}
		}
	}
}
//=====================
//�G�̎擾����
//=====================
Enemy *GetEnemy(void)
{//�G�l�~�[�̃|�C���^�����Z�b�g
	return &s_aEnemy[0];
}