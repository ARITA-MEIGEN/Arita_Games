//=================================================
// Content     (�|�[�Y�̑���)(Pause.cpp)
// Author     : �L�c����
// LastUpdate : (�X�V��2021/07/18)
// Since      : (�쐬��2021/07/06)
//=================================================
#include"pause.h"

//�}�N����`
#define NUM_PAUSE	(5)		//�|�[�Y�̖���
#define MODE_COUNT	(3)		//���[�h�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePause[NUM_PAUSE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			//���_�o�b�t�@�ւ̃|�C���^
PAUSE_MENU g_Pause;										//�|�[�Y�̏�Ԑݒ�
//======================================================
//�|�[�Y�̏���������
//======================================================
void InitPause(void)
{
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause100.png",
		&g_apTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause000.png",
		&g_apTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_apTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_apTexturePause[3]);

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	g_Pause = PAUSE_MENU_CONTINUE;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex += D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex += D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex += D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex += D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}
//======================================================
//�|�[�Y�̏I������
//======================================================
void UninitPause(void)
{
	int nCntPause;
	//�e�N�X�`���̔j��
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//======================================================
//�|�[�Y�̍X�V����
//======================================================
void UpdatePause(void)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���j���[�̑I��
	if (GetKeyboardTrigger(DIK_W) == true|| GetKeyboardTrigger(DIK_UP) == true||GetJoypadTrigger(JOYKEY_UP) == true||GetJoypadStick(JOYKEY_LSTICK).y <= -1.0)
	{
		//��Ɉړ�
		g_Pause = (PAUSE_MENU((g_Pause + (MODE_COUNT-1)) % MODE_COUNT));
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || GetJoypadStick(JOYKEY_LSTICK).y >= 1.0)
	{
		//���Ɉړ�
		g_Pause = (PAUSE_MENU((g_Pause + 1) % MODE_COUNT));
		PlaySound(SOUND_LABEL_SE_SELECT);

	}
	
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_X) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{//����L�[�������ꂽ
		switch (g_Pause)
		{
		case PAUSE_MENU_CONTINUE:		//�R���e�B�j���[�_��
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:			//���g���C�_��
			SetFade(MODE_GAME);
			SetEnablePause(false);
			break;

		case PAUSE_MENU_QUIT:			//�^�C�g���_��
			SetFade(MODE_TITLE);
			SetEnablePause(false);
			break;
		}
		PlaySound(SOUND_LABEL_SE_START);
	}
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT / 5, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT - (SCREEN_HEIGHT / 5), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT - (SCREEN_HEIGHT / 5), 0.0f);

	pVtx[8].pos = D3DXVECTOR3(440.0f, 200.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(840.0f, 200.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(440.0f, 300.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(840.0f, 300.0f, 0.0f);

	pVtx[12].pos = D3DXVECTOR3(440.0f, 310.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(840.0f, 310.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(440.0f, 410.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(840.0f, 410.0f, 0.0f);

	pVtx[16].pos = D3DXVECTOR3(440.0f, 420.0f, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(840.0f, 420.0f, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(440.0f, 520.0f, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(840.0f, 520.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	switch (g_Pause)
	{
	case PAUSE_MENU_CONTINUE:
		pVtx[8].col =  D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[9].col =  D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[10].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[11].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;

	case PAUSE_MENU_RETRY:
		pVtx[12].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[13].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[14].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[15].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;

	case PAUSE_MENU_QUIT:
		pVtx[16].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[17].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[18].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		pVtx[19].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		break;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}
//======================================================
//�|�[�Y�̕`�揈��
//======================================================
void DrawPause(void)
{
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|�[�Y�̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	for (nCntPause = 0; nCntPause < 4; nCntPause++)
	{
		pDevice->SetTexture(0, g_apTexturePause[nCntPause]);

		//�|�[�Y�̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPause + 1) * 4, 2);
	}
}