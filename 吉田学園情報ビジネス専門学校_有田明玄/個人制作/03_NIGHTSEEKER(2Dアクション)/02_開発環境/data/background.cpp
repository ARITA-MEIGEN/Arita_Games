//=================================================
// Content     (�w�i�̑���)(BG.cpp)
// Author     : �L�c����
// LastUpdate : (�X�V��2021/07/18)
// Since      : (�쐬��2021/07/06)
//=================================================
#include "background.h"
#include"player.h"
#include"block.h"
#include"player.h"
//�}�N����`
#define NUM_BG	(3)			//�w�i�̖���
#define BG_SPEED	(0.0005f)	//�w�i�̑��x

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnimBG;								//�J�E���^�[������������
int g_nPatternAnimBG;								//�p�^�[��No.������������
D3DXVECTOR3 g_posBG;								//�ʒu
D3DXVECTOR3 g_moveBG;								//�ړ���

//�X�^�e�B�b�N�֐�
static void ControlBG(void);		//�w�i�̑���֌W�̏���
//======================================================
//�w�i�̏���������
//======================================================
void InitBG(void)
{
	int nCntBG;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg000.jpg",
			&g_apTextureBG[0]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg001.png",
			&g_apTextureBG[1]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg002.png",
			&g_apTextureBG[2]);
	
	g_nCounterAnimBG = 0;						//�J�E���^�[������������
	g_nPatternAnimBG = 0;						//�p�^�[��No.������������
	g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
	g_moveBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�����������

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG-1; nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.4f, 0.8f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 20.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20.0f, SCREEN_HEIGHT / 2 - 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 20.0f, SCREEN_HEIGHT / 2 - 260.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20.0f, SCREEN_HEIGHT / 2 - 260.0f, 0.0f);

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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//======================================================
//�w�i�̏I������
//======================================================
void UninitBG(void)
{
	int nCntBG;
	//�e�N�X�`���̔j��
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBG[nCntBG] != NULL)
		{
			g_apTextureBG[nCntBG]->Release();
			g_apTextureBG[nCntBG] = NULL;
		}
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//======================================================
//�w�i�̍X�V����
//======================================================
void UpdateBG(void)
{
	//�ʒu���X�V
	g_posBG = g_moveBG;

	//�v���C���[�̓����ɉ����Ĕw�i�̈ړ�
	ControlBG();

	//�ړ��ʍX�V(����������)
	g_moveBG.x += (0.0f - g_moveBG.x)*0.1f;
	g_moveBG.y += (0.0f - g_moveBG.y)*0.1f;

	VERTEX_2D*pVtx;//���_���W�ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBG = 0; nCntBG < NUM_BG-1; nCntBG++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));//�E���ɍ��W���w��
		pVtx[1].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx[2].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx[3].tex += D3DXVECTOR2(g_posBG.x*(nCntBG + 1), g_posBG.y*(nCntBG + 1));
		pVtx += 4;
	}
	pVtx[0].pos += D3DXVECTOR3(0.0f, 0.0f,0.0f);//�E���ɍ��W���w��
	pVtx[1].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}
//======================================================
//�w�i�̕`�揈��
//======================================================
void DrawBG(void)
{
	static int nCntBG;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntBG  = 0; nCntBG <NUM_BG; nCntBG++)
	{
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);
	
		//�w�i�̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBG*4, 2);
	}
}
//======================================================
//�w�i�̑���֌W�̏���
//======================================================
static void ControlBG(void)
{
	CenterPlayer(&g_moveBG);
	g_moveBG.x/=-3000;
}