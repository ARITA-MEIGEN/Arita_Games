//=================================================
// Content     (���U���g��ʂ̏���)(result.cpp)
// Author     : �L�c����
// LastUpdate : (�X�V��2021/09/02)
// Since      : (�쐬��2021/08/29)
//=================================================
#include"result.h"
#include"sound.h"
#include"fade.h"
#include"input.h"
#include"game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResultBG = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureResult[2] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_nTimerResult;								//�^�C�}�[
//===========================
//���U���g��ʂ̏���������
//===========================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg003.png",
		&g_pTextureResultBG);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameclear_logo.png",
		&g_apTextureResult[0]);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameover_logo.png",
		&g_apTextureResult[1]);

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultBG,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultBG->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, SCREEN_HEIGHT / 2 - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, SCREEN_HEIGHT / 2 - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	g_nTimerResult = 0;	//�^�C�}�[�̃��Z�b�g
	GAMESTATE pGamestate = GetGameState();

	//�Q�[���̏󋵂ɉ����ĕω�
	switch (pGamestate)
	{//�T�E���h�̍Đ�
	case GAMESTATE_CLEAR:
		PlaySound(SOUND_LABEL_BGM003);
		break;
	case GAMESTATE_FAILED:
		PlaySound(SOUND_LABEL_BGM004);
		break;
	default:
		break;
	}
}
//===========================
//���U���g��ʂ̏I������
//===========================
void UninitResult(void)
{
	//�T�E���h�̒�~
	StopSound();
	
	//�e�N�X�`���̔j��
	if (g_pTextureResultBG != NULL)
	{
		g_pTextureResultBG->Release();
		g_pTextureResultBG = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffResultBG != NULL)
	{
		g_pVtxBuffResultBG->Release();
		g_pVtxBuffResultBG = NULL;
	}
//���ʂ̕\��
	for (int nCount = 0;  nCount < 2;  nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureResult[nCount] != NULL)
		{
			g_apTextureResult[nCount]->Release();
			g_apTextureResult[nCount] = NULL;
		}
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	
}
//===========================
//���U���g��ʂ̍X�V����
//===========================
void UpdateResult(void)
{
	g_nTimerResult++;	//���Ԍo�߂Ŏ��̉�ʂɈڍs

	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	FADE pFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE		//ENTER�L�[
		|| GetJoypadTrigger(JOYKEY_Y) == true && pFade == FADE_NONE			//Y�{�^��
		|| GetJoypadTrigger(JOYKEY_X) == true && pFade == FADE_NONE			//X�{�^��
		|| GetJoypadTrigger(JOYKEY_START) == true && pFade == FADE_NONE		//�X�^�[�g�{�^��
		|| g_nTimerResult >= 600 && pFade == FADE_NONE)						//���Ԍo��
	{
		PlaySound(SOUND_LABEL_SE_START);
		//���[�h�ݒ�
		SetFade(MODE_RANKING);
	}
}
//===========================
//���U���g��ʂ̕`�揈��
//===========================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultBG);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�Q�[���̏��̎擾
	GAMESTATE pGamestate = GetGameState();
	//�Q�[���̏󋵂ɉ����ĕω�
	switch (pGamestate)
	{
	case GAMESTATE_CLEAR:
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[0]);
		break;
	case GAMESTATE_FAILED:
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureResult[1]);
		break;
	default:
		pDevice->SetTexture(0, NULL);
		break;
	}
	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�
}
