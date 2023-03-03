//=================================================
// Content     (�G�t�F�N�g�̏���)(playerPlayereffect.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/09/07)
//=================================================
#include"playereffect.h"
#include"player.h"

//�}�N����`
#define MAX_Playereffect		(9192)	//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
	float fRadiuswidth;	//����
	float fRadiusheight;//�c��
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ����̔���
}Playereffect;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayereffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayereffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Playereffect g_aPlayereffect[MAX_Playereffect];						//�G�t�F�N�g�̏��
//============================
//�G�t�F�N�g�̏���������
//============================
void InitPlayereffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPlayereffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player001.png",
		&g_pTexturePlayereffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Playereffect,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayereffect,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏��̏�����
	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		g_aPlayereffect[nCntPlayereffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aPlayereffect[nCntPlayereffect].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
		g_aPlayereffect[nCntPlayereffect].fRadiuswidth = 0;							//���a(�傫��)
		g_aPlayereffect[nCntPlayereffect].nLife = 0;								//����
		g_aPlayereffect[nCntPlayereffect].bUse = false;								//�g�p���Ă��邩�ǂ����̔���

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayereffect->Unlock();
}
//===========================
//�G�t�F�N�g�̏I������
//===========================
void UninitPlayereffect(void)
{
	if (g_pTexturePlayereffect != NULL)
	{
		g_pTexturePlayereffect->Release();
		g_pTexturePlayereffect = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffPlayereffect != NULL)
	{
		g_pVtxBuffPlayereffect->Release();
		g_pVtxBuffPlayereffect = NULL;
	}
}
//===========================
//�G�t�F�N�g�̍X�V����
//===========================
void UpdatePlayereffect(void)
{
	int nCntPlayereffect;

	VERTEX_2D*pVtx;
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

			//���_�J���[�ݒ�	(�A���t�@�l�������ĐF�𔖂�����)
			g_aPlayereffect[nCntPlayereffect].col.a -= 1.0f/30.0f;

			pVtx[0].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[1].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[2].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[3].col = g_aPlayereffect[nCntPlayereffect].col;

			g_aPlayereffect[nCntPlayereffect].nLife--;

			//�������s�����ꍇ
			if (g_aPlayereffect[nCntPlayereffect].nLife <= 0)
			{
				g_aPlayereffect[nCntPlayereffect].bUse = false;
			}

			//��ʂ̒����ɗ������̐ݒ�
			CenterPlayer(&g_aPlayereffect[nCntPlayereffect].pos);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, -g_aPlayereffect[nCntPlayereffect].fRadiusheight, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, -g_aPlayereffect[nCntPlayereffect].fRadiusheight, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth/2, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayereffect->Unlock();
}
//===========================
//�G�t�F�N�g�̕`�揈��
//===========================
void DrawPlayereffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPlayereffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayereffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayereffect);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == true)
		{
			//�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				nCntPlayereffect*4,						//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//===========================
//�G�t�F�N�g�̐ݒ菈��
//===========================
void SetPlayereffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight, int nLife, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	int nCntPlayereffect;
	VERTEX_2D*pVtx;

	for (nCntPlayereffect = 0; nCntPlayereffect < MAX_Playereffect; nCntPlayereffect++)
	{
		if (g_aPlayereffect[nCntPlayereffect].bUse == false)
		{
			g_aPlayereffect[nCntPlayereffect].pos = pos;
			g_aPlayereffect[nCntPlayereffect].col = col;
			g_aPlayereffect[nCntPlayereffect].fRadiuswidth = fRadiuswidth;
			g_aPlayereffect[nCntPlayereffect].fRadiusheight = fRadiusheight;
			g_aPlayereffect[nCntPlayereffect].nLife = nLife;
			g_aPlayereffect[nCntPlayereffect].bUse = true;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPlayereffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCntPlayereffect * 4;	//���_�f�[�^�̃|�C���^��4���i�߂�

			//���_�J���[�ݒ�
			pVtx[0].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[1].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[2].col = g_aPlayereffect[nCntPlayereffect].col;
			pVtx[3].col = g_aPlayereffect[nCntPlayereffect].col;

			//���_���W�̐ݒ�	(�傫��������������)
			pVtx[0].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth, -g_aPlayereffect[nCntPlayereffect].fRadiusheight * 2, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth, -g_aPlayereffect[nCntPlayereffect].fRadiusheight * 2, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aPlayereffect[nCntPlayereffect].fRadiuswidth, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aPlayereffect[nCntPlayereffect].fRadiuswidth, 0.0f, 0.0f) + g_aPlayereffect[nCntPlayereffect].pos;

			pVtx[0].tex = a;	//�E���ɍ��W���w��
			pVtx[1].tex = b;
			pVtx[2].tex = c;
			pVtx[3].tex = d;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffPlayereffect->Unlock();
			break;
		}
	}
}