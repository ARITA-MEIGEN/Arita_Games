//=================================================
// Content     (�X�R�A�̐ݒ�)(Score.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/28)
//=================================================
#include"score.h"	
#include"fade.h"
#include"game.h"
#include"result.h"
#include"ranking.h"

//�}�N����`
#define MAX_SCORE				(8)//�X�R�A�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureScoreBG = NULL;			//�w�i�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreBG = NULL;		//�w�i���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;									//�X�R�A�̈ʒu
int g_nScore;											//�X�R�A�̒l
//============================
//�X�R�A�̏���������
//============================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&g_pTextureScore);

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\scorebg000.jpg",
	//	&g_pTextureScoreBG);

	g_posScore = D3DXVECTOR3(950.0f, 100.0f, 0.0f);//�ʒu�̏�����
	g_nScore = 0;
	
	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	////���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffScoreBG,
	//	NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//���_���W�̏�����
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 20 + (nCntScore * 35), g_posScore.y - 50, 0);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 20 + (nCntScore * 35), g_posScore.y - 50, 0);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 20 + (nCntScore * 35), g_posScore.y + 50, 0);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 20 + (nCntScore * 35), g_posScore.y + 50, 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();

////�w�i�̐ݒ�
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffScoreBG->Lock(0, 0, (void**)&pVtx, 0);
//	//���_���W�̏�����
//	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), 0.0f, 0);
//	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0);
//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT, 0);
//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
//
//	//rhw�̐ݒ�
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//���_�J���[�̐ݒ�
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	//�e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffScoreBG->Unlock();
}
//============================
//�X�R�A�̏I������
//============================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//============================
//�X�R�A�̍X�V����
//============================
void UpdateScore(void)
{

}
//==============================
//�X�R�A�̕`�揈��
//==============================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

////�w�i�̐ݒ�
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffScoreBG, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pTextureScoreBG);
//
//	//�|���S���̕`��       
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
//		0,										//���_�̊J�n�ꏊ
//		2);										//�v���~�e�B�u�̐�
//
//�X�R�A�̐ݒ�
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//�|���S���̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
			nCntScore * 4,							//���_�̊J�n�ꏊ
			2);										//�v���~�e�B�u�̐�
	}
}
//=====================
//�X�R�A�̐ݒ菈��
//=====================
void SetScore(int nScore)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int aPosTexU[8];	//�e���̐������i�[

	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore]), 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nScore] + 1), 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
//=====================
//�X�R�A�̉��Z����
//=====================
void AddScore(int nValue)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D*pVtx;
	int aPosTexU[8];	//�e���̐������i�[

	g_nScore += nValue;
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 0.0f);//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
//============================
//�X�R�A�̏�Ԃ̎擾
//============================
int GetScore(void)
{
	return g_nScore;
}