//=================================================
// Content     (�G�t�F�N�g�̏���)(effect.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/09/07)
//=================================================
#include"effect.h"
#include"player.h"

//�}�N����`
#define MAX_EFFECT		(91920)	//�G�t�F�N�g�̍ő吔
#define NUM_EFFECT		(3)		//�G�t�F�N�g�̖���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEffect[NUM_EFFECT] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];							//�G�t�F�N�g�̏��
//============================
//�G�t�F�N�g�̏���������
//============================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bat000.png",
		&g_apTextureEffect[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_apTextureEffect[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		g_aEffect[nCntEffect].pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aEffect[nCntEffect].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0;				//���a(�傫��)
		g_aEffect[nCntEffect].nLife = 0;				//����
		g_aEffect[nCntEffect].bUse = false;				//�g�p���Ă��邩�ǂ����̔���
		g_aEffect[nCntEffect].bAdd = false;				//���Z�������邩�ǂ���

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//===========================
//�G�t�F�N�g�̏I������
//===========================
void UninitEffect(void)
{
	for (int  nCnt = 0; nCnt < NUM_EFFECT; nCnt++)
	{
		if (g_apTextureEffect[nCnt] != NULL)
		{
			g_apTextureEffect[nCnt]->Release();
			g_apTextureEffect[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//===========================
//�G�t�F�N�g�̍X�V����
//===========================
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_2D*pVtx;
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	//�ʒu�̍X�V

			//�v���C���[�������ɗ����ꍇ
			CenterPlayer(&g_aEffect[nCntEffect].pos);

			//���_�J���[�ݒ�	(�A���t�@�l�������ĐF�𔖂�����)
			g_aEffect[nCntEffect].col.a -= 0.01f;
			
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].fRadius-=0.05f;	//���a�̌���

			//���_���W�̐ݒ�	(�傫��������������)
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[1].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius,- g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[2].pos = D3DXVECTOR3(- g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;
			pVtx[3].pos = D3DXVECTOR3( g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f) + g_aEffect[nCntEffect].pos;

			//�������s�����ꍇ
			if (g_aEffect[nCntEffect].fRadius <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			if (g_aEffect[nCntEffect].col.a <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			g_aEffect[nCntEffect].nLife--;		

			//�������s�����ꍇ
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();

}
//===========================
//�G�t�F�N�g�̕`�揈��
//===========================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCntEffect].nType]);

			if (g_aEffect[nCntEffect].bAdd == true)
			{

				//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				nCntEffect * 4,							//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}
//===========================
//�G�t�F�N�g�̐ݒ菈��
//===========================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,bool ADD,int Type)
{
	int nCntEffect;
	VERTEX_2D*pVtx;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			g_aEffect[nCntEffect].bAdd = ADD;
			g_aEffect[nCntEffect].nType = Type;
			
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCntEffect * 4;	//���_�f�[�^�̃|�C���^��4���i�߂�

			//���_�J���[�ݒ�	(�A���t�@�l�������ĐF�𔖂�����)
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].fRadius--;

			//���_���W�̐ݒ�	(�傫��������������)
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffEffect->Unlock();
			break;
		}
	}
}