//=================================================
// Content     (�v���C���[�̑���)(UI.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/10/04)
//=================================================
#include"GameUI.h"
#include"player.h"
//�}�N����`
#define LIFEGAUGE_SIZE		(20.0f)		//�̗̓Q�[�W�̃T�C�Y�����p

//�X�^�e�B�b�N�ϐ�
static LPDIRECT3DTEXTURE9 s_apTexturePlayerLife[NUM_LIFE] = {};	//�̗̓Q�[�W�̃e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPlayerLife = NULL;		//�̗̓Q�[�W�̒��_�o�b�t�@�ւ̃|�C���^

//�v���g�^�C�v�錾
static void ResetLifegauge(void);					//�v���C���[�̗̑̓Q�[�W�̏�����
static void UpdatePlayerLife(void);					//�̗̓Q�[�W�̏��X�V
//======================================================
//�v���C���[�̏���������
//======================================================
void InitUI(void)
{
	ResetLifegauge();	//�̗̓Q�[�W�̏��̏�����
}
//======================================================
//�v���C���[�̏I������
//======================================================
void UninitUI(void)
{
	//�̗̓Q�[�W�̃e�N�X�`���̔j��
	for (int  nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		if (s_apTexturePlayerLife[nCnt]!=NULL)
		{
			s_apTexturePlayerLife[nCnt]->Release();
			s_apTexturePlayerLife[nCnt] = NULL;
		}
	}
	//�̗̓Q�[�W�̒��_�o�b�t�@��j��
	if (s_pVtxBuffPlayerLife != NULL)
	{
		s_pVtxBuffPlayerLife->Release();
		s_pVtxBuffPlayerLife = NULL;
	}
}
//======================================================
//�v���C���[�̍X�V����
//======================================================
void UpdateUI(void)
{
	//�̗̓Q�[�W�̍X�V
	UpdatePlayerLife();
}
//======================================================
//�v���C���[�̕`�揈��
//======================================================
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�O�����̃e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_apTexturePlayerLife[nCnt]);

		//�v���C���[�̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//======================================================
//�v���C���[�̗̑̓Q�[�W�̏�����
//======================================================
static void ResetLifegauge(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Lifegaugeblood.png",
		&s_apTexturePlayerLife[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifegauge004.png",
		&s_apTexturePlayerLife[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffPlayerLife,
		NULL);

	//�v���C���[�̏��̊l��
	Player*pPlayer = GetPlayer();
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		pVtx[0].pos= D3DXVECTOR3(50.0f, 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 80.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayerLife->Unlock();
}
//======================================================
//�̗̓Q�[�W�̏��X�V
//======================================================
static void UpdatePlayerLife(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̏��̊l��
	Player*pPlayer = GetPlayer();

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(50.0f, 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)pPlayer->nLife / LIFEGAUGE_SIZE + 50.0f, 80.0f, 0.0f);
		
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);	//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffPlayerLife->Unlock();
}