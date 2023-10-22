//=================================================
// Content     (�^�C�g����ʂ̏���)(Tutorial.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/9)
//=================================================
#include"Tutorial.h"
#include"sound.h"
#include"fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorial=NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//���_�o�b�t�@�ւ̃|�C���^
//===========================
//�^�C�g����ʂ̏���������
//===========================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tutorial000.png",
		&g_pTextureTutorial);

	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	
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
	g_pVtxBuffTutorial->Unlock();
}
//===========================
//�^�C�g����ʂ̏I������
//===========================
void UninitTutorial(void)
{
	//�T�E���h�̒�~
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial= NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//===========================
//�^�C�g����ʂ̍X�V����
//===========================
void UpdateTutorial(void)
{
	FADE pFade = GetFade();	//�t�F�[�h�̏�Ԃ��擾
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if ((GetKeyboardTrigger(DIK_RETURN) == true
		||GetJoypadTrigger(JOYKEY_Y) == true  
		|| GetJoypadTrigger(JOYKEY_X) == true 
		|| GetJoypadTrigger(JOYKEY_A) == true 
		|| GetJoypadTrigger(JOYKEY_B) == true 
		|| GetJoypadTrigger(JOYKEY_START) == true) && pFade == FADE_NONE)
	{
		//���[�h�ݒ�
		SetFade(MODE_GAME);
		PlaySound(SOUND_LABEL_SE_START);
	}
}
//===========================
//�^�C�g����ʂ̕`�揈��
//===========================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�
}