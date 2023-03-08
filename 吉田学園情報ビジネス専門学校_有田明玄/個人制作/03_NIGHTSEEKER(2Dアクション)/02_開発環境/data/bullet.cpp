//=================================================
// Content     (�e�ۂ̐ݒ�)(bullet.cpp)
// Author     : �L�c����
//=================================================
#include "bullet.h"	
#include"effect.h"
#include"Player.h"
#include "enemy.h"
#include"boss.h"

//�}�N����`
#define MAX_BULLET			(5120)	//�e�̍ő吔
#define PBULLET_SIZE		(15)	//�v���C���[�̒e�̃T�C�Y
#define EBULLET_SIZE		(5)		//�G�̒e�̃T�C�Y

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��
													//============================
													//�e�̏���������
													//============================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].nDamage = 0;
		g_aBullet[nCntBullet].fHeight = 0.0f;
		g_aBullet[nCntBullet].fWidth = 0.0f;
		g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth/2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
		pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�ݒ�
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
	g_pVtxBuffBullet->Unlock();
}
//============================
//�e�̏I������
//============================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//============================
//�e�̍X�V����
//============================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//�e�̈ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].pos.y <= -g_aBullet[nCntBullet].fHeight)
			{//��ʊO�ɏo���ꍇ�̏���(��[)
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
			else if (g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT + g_aBullet[nCntBullet].fHeight)
			{//��ʊO�ɏo���ꍇ�̏���(���[)
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
			else if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH + g_aBullet[nCntBullet].fWidth)
			{//��ʊO�ɏo���ꍇ�̏���(�E�[)
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
			else if (g_aBullet[nCntBullet].pos.x <= -g_aBullet[nCntBullet].fWidth)
			{//��ʊO�ɏo���ꍇ�̏���(���[)
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
			//�e�̎����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

			//�e�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

			//�e�N�X�`���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), g_aBullet[nCntBullet].fHeight, 10, true, 1);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}
//==============================
//�e�̕`�揈��
//==============================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

		 //�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				nCntBullet * 4,							//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}
	}
}
//=====================
//�e�̐ݒ菈��
//=====================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int Damage,float Width,float Height)
{
	int nCntBullet;
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].fWidth = Width;
			g_aBullet[nCntBullet].fHeight = Height;
			g_aBullet[nCntBullet].nDamage = Damage;
			g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].nLife = 500;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[1].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;
			pVtx[3].pos = D3DXVECTOR3(+g_aBullet[nCntBullet].fWidth / 2, +g_aBullet[nCntBullet].fHeight / 2, 0) + g_aBullet[nCntBullet].pos;

			//�G���g�p����Ă���
			SetHorming(nCntBullet);
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}
//=====================
//�z�[�~���O�e�̐ݒ菈��
//=====================
void SetHorming(int CntBullet)
{//�z�[�~���O�̐ݒ�
	int nCntBullet;
	nCntBullet = CntBullet;
	Player *pPlayer = GetPlayer(); //�|�C���^

	float fRotMove, fRotDest, fRotDiff;

	//���݂̈ړ�����(�p�x)
	fRotMove = atan2f(g_aBullet[nCntBullet].move.x, g_aBullet[nCntBullet].move.y);			
	//�ړI�̈ړ�����(�p�x)	����̍��W���玩������������
	fRotDest = atan2f(pPlayer->pos.x - g_aBullet[nCntBullet].pos.x, (pPlayer->pos.y-PLAYER_HEIGHT/2-20.0f) - g_aBullet[nCntBullet].pos.y);		
	//�ړI�̈ړ������܂ł̍���
	fRotDiff = fRotDest - fRotMove;															

	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= D3DX_PI * 2;
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2;
	}

	fRotMove += fRotDiff*1.0f;	//�ړ�����(�p�x)�̕␳

	if (fRotMove > D3DX_PI)
	{
		fRotMove -= D3DX_PI * 2;
	}
	else if (fRotMove < -D3DX_PI)
	{
		fRotMove += D3DX_PI * 2;
	}

	g_aBullet[nCntBullet].move.x = sinf(fRotMove)*4.0f;
	g_aBullet[nCntBullet].move.y = cosf(fRotMove)*4.0f;
}
//=====================
//�e�̓����蔻�菈��
//=====================
void CollisionBullet(D3DXVECTOR3 *pPos, float Width, float Height)
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse==true)
		{//�G���g�p����Ă���
			if ( pPos->y  >= g_aBullet[nCnt].pos.y - g_aBullet[nCnt].fHeight / 2 			//��[
				&& pPos->y - Height <= g_aBullet[nCnt].pos.y + g_aBullet[nCnt].fHeight / 2					//���[
				&&  pPos->x + Width / 2 >= g_aBullet[nCnt].pos.x - g_aBullet[nCnt].fWidth / 2		//���[
				&& pPos->x - Width / 2 <= g_aBullet[nCnt].pos.x + g_aBullet[nCnt].fWidth / 2)		//�E�[
			{//�v���C���[�ɒe������������
			 //�v���C���[�̃q�b�g����
				HitPlayer(g_aBullet[nCnt].nDamage);
				g_aBullet[nCnt].bUse = false;			//�g�p���Ă��Ȃ����
			}
		}
	}
}
//=====================
//�o���b�g�̎擾����
//=====================
Bullet *GetBullet(void)
{//�G�l�~�[�̃|�C���^�����Z�b�g
	return &g_aBullet[0];
}