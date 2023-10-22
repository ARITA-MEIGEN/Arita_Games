//=================================================
// Content     (�^�C�g����ʂ̏���)(title.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/9)
//=================================================
#include"title.h"
#include"sound.h"
#include"fade.h"

//�}�N����`
#define NUM_TITLE		(2)									//�^�C�g���Ŏg���|���S����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitlelogo = NULL;				//�^�C�g�����S�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlelogo = NULL;			//�^�C�g�����S���_�o�b�t�@�ւ̃|�C���^
int g_nCnt = 0;	//���[�v�p
float g_fPtntitle = 0;	//�_�ŗp
//===========================
//�^�C�g����ʂ̏���������
//===========================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg003.png",
		&g_apTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\press_enter.png",
		&g_apTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titlelogo000.png",
		&g_pTextureTitlelogo);

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlelogo,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH/2-300, 500.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH/2+300, 500.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH/2-300, 700.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH/2+300, 700.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

//�^�C�g�����S�̐ݒ�
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitlelogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, 600.0f, 0.0f);

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
	g_pVtxBuffTitlelogo->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);
}
//===========================
//�^�C�g����ʂ̏I������
//===========================
void UninitTitle(void)
{
	//�����̒�~
	StopSound();

	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < NUM_TITLE; nCount++)
	{
		if (g_apTextureTitle[nCount] != NULL)
		{
			g_apTextureTitle[nCount]->Release();
			g_apTextureTitle[nCount] = NULL;
		}
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}


	//�^�C�g�����S�e�N�X�`���̔j��
	if (g_pTextureTitlelogo != NULL)
	{
		g_pTextureTitlelogo->Release();
		g_pTextureTitlelogo = NULL;
	}

	//�^�C�g�����S���_�o�b�t�@��j��
	if (g_pVtxBuffTitlelogo != NULL)
	{
		g_pVtxBuffTitlelogo->Release();
		g_pVtxBuffTitlelogo = NULL;
	}

}
//===========================
//�^�C�g����ʂ̍X�V����
//===========================
void UpdateTitle(void)
{
	FADE pFade = GetFade();	//�t�F�[�h�̏�Ԃ��擾

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;
	
	g_nCnt++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCnt % 30) == 0)
	{
		g_fPtntitle=1- g_fPtntitle;
	}
	if (pFade==FADE_OUT)
	{
		if ((g_nCnt % 2) == 0)
		{
			g_fPtntitle = 1 - g_fPtntitle;
		}
	}
	
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fPtntitle);
	

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�w��̃L�[�������ꂽ���ǂ���
	if ((GetKeyboardTrigger(DIK_RETURN) == true 	//ENTER�L�[
		||GetJoypadTrigger(JOYKEY_Y) ==   true 			//�p�b�hY�L�[
		|| GetJoypadTrigger(JOYKEY_X) ==  true 		//�p�b�hX�L�[
		|| GetJoypadTrigger(JOYKEY_A) ==  true 	//�p�b�hA�L�[
		|| GetJoypadTrigger(JOYKEY_B) ==  true 	//�p�b�hB�L�[
		|| GetJoypadTrigger(JOYKEY_START) == true) && pFade != FADE_OUT)	//�p�b�h�X�^�[�g�L�[
	{
		PlaySound(SOUND_LABEL_SE_START);
		//���[�h�ݒ�
		SetFade(MODE_TUTOLIAL);
	}
}
//===========================
//�^�C�g����ʂ̕`�揈��
//===========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTitle[0]);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTitle[1]);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		4,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�

//�^�C�g�����S�̐ݒ�
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitlelogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitlelogo);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�

}