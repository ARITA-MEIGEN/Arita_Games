//=================================================
// Content     (�����L���O�̏���)(ranking.cpp)
// Author     : �L�c����
//=================================================
#include"ranking.h"
#include"sound.h"
#include<stdio.h>
#include"score.h"

//�}�N����`
#define FILE_NAME	("data/TXT/ranking.txt")		//�����L���O��ۑ�����t�@�C��

//�����L���O�X�R�A�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
}RankScore;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//�����L���O�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//�����L���O���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//�X�R�A�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//�X�R�A���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;				//�����L���O�̔w�i�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL;		//�����L���O�̔w�i�̒��_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];						//�����L���O�X�R�A�̏��
int g_nRankUpdate = -1;									//�X�V�����NNo.
int g_nTimerRanking;									//�����L���O��ʕ\���^�C�}�[
float g_fPtnrank = 1.0f;								//�v���C���[�����L���O�̓_��
int g_nCntrank = 0;										//�_�ł̃J�E���g�p
//============================
//�����L���O�̏���������
//============================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//�ǂݍ��ݏ���
	LoadRanking();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",
		&g_pTextureRankScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRank);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rankbg001.jpg",
		&g_pTextureRankBG);

	//���_�|�C���^�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	//�X�R�A�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_SCORE * MAX_RANK; nCntRank++)
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

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankScore->Unlock();

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(600.0f, 550.0f - (95 * nCntRank), 0.0f);		//�ʒu
	}


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

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
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRank->Unlock();

//�w�i�̐ݒ�
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);
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

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//�E���ɍ��W���w��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankBG->Unlock();

	//�^�C�}�[�̃��Z�b�g
	g_nTimerRanking = 0;

	//�����L���O�̕ۑ�
	SaveRanking();
}
//===========================
//�����L���O�̏I������
//===========================
void UninitRanking(void)
{
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffRankBG != NULL)
	{
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
}
//===========================
//�����L���O�̍X�V����
//===========================
void UpdateRanking(void)
{
	VERTEX_2D*pVtx;
	int nCntRank;
	int nCntScore;
	g_nCntrank++;
	g_nTimerRanking++;
	FADE pFade = GetFade();
	if ((g_nTimerRanking >= 600 || GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_X) == true)  && pFade == FADE_NONE)
	{//�^�C�g���ֈڍs
		//PlaySound(SOUND_LABEL_SE_START);
		SetFade(MODE_TITLE);
	}

//�X�R�A�̐ݒ�
	if ((g_nCntrank % 30) == 0)
	{//�����N�C�������Ƃ��_�ł����邽�߂̃^�C�}�[
		g_fPtnrank = 1.0f - g_fPtnrank;
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x - 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y - 40, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x + 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y - 40, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x - 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y + 40, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank].pos.x + 20 + (50 * (nCntScore % 8)), g_aRankScore[nCntRank].pos.y + 40, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankScore->Unlock();
	
	//�����N�C�������ꍇ
	if (g_nRankUpdate != -1)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
		for (nCntRank = 0; nCntRank < MAX_SCORE; nCntRank++)
		{
			
			//�����L���O��_�ł�����
			pVtx[g_nRankUpdate * 4 * MAX_SCORE].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);
			pVtx[g_nRankUpdate * 4 * MAX_SCORE + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fPtnrank);

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffRankScore->Unlock();

//�X�R�A�̃����L���O�̍X�V
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(400.0f - 50, SCREEN_HEIGHT/2- 240, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(400.0f + 50, SCREEN_HEIGHT / 2- 240, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400.0f - 50, SCREEN_HEIGHT / 2+ 240, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(400.0f + 50, SCREEN_HEIGHT / 2+ 240, 0.0f);

		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffRank->Unlock();
	}
}
//===========================
//�����L���O�̕`�揈��
//===========================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
//�w�i�̐ݒ�
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankBG);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�
//�����L���O�̐ݒ�
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRank);

	//�|���S���̕`��       
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		2);										//�v���~�e�B�u�̐�

//�X�R�A�̐ݒ�
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankScore);

	for (nCntRank = 0; nCntRank < MAX_SCORE * MAX_RANK; nCntRank++)
	{
		//�|���S���̕`��       
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
			nCntRank * 4,							//���_�̊J�n�ꏊ
			2);										//�v���~�e�B�u�̐�
	}
}
//===========================
//�����L���O�̃��Z�b�g
//===========================
void ResetRanking(void)
{
	//�ǂݍ��ݏ���
	LoadRanking();

	//�����L���O�̐ݒ�
	SetRanking();

	//�^�C�}�[�̃��Z�b�g
	g_nTimerRanking = 0;

	//�����L���O�̕ۑ�
	SaveRanking();
}
//===========================
//�����L���O�̐ݒ菈��
//===========================
void SetRanking(void)
{
	int nCntRank, nCntScore, nSave;
	int aPosTexU[8];					//�e���̐������i�[
	g_nRankUpdate = -1;
	g_nTimerRanking = 0;

	int pScore = GetScore();

	//�X�R�A�̍ŉ��ʂ��傫����Γ���ւ�
	if (pScore >= g_aRankScore[0].nScore)
	{
		g_aRankScore[0].nScore = pScore;
		g_nRankUpdate++;
	}
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK-1; nCntRank++)
	{
		if (g_aRankScore[nCntRank].nScore > g_aRankScore[nCntRank + 1].nScore)
		{//�����L���O�̕��בւ�
			nSave = g_aRankScore[nCntRank + 1].nScore;
			g_aRankScore[nCntRank + 1].nScore = g_aRankScore[nCntRank].nScore;
			g_aRankScore[nCntRank].nScore = nSave;
			g_nRankUpdate++;
		}
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		aPosTexU[0] = g_aRankScore[nCntRank].nScore % 100000000 / 10000000;
		aPosTexU[1] = g_aRankScore[nCntRank].nScore % 10000000 / 1000000;
		aPosTexU[2] = g_aRankScore[nCntRank].nScore % 1000000 / 100000;
		aPosTexU[3] = g_aRankScore[nCntRank].nScore % 100000 / 10000;
		aPosTexU[4] = g_aRankScore[nCntRank].nScore % 10000 / 1000;
		aPosTexU[5] = g_aRankScore[nCntRank].nScore % 1000 / 100;
		aPosTexU[6] = g_aRankScore[nCntRank].nScore % 100 / 10;
		aPosTexU[7] = g_aRankScore[nCntRank].nScore % 10 / 1;

		for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 0.0f);//�E���ɍ��W���w��
			pVtx[1].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f*(aPosTexU[nCntScore] + 1), 1.0f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankScore->Unlock();
}
//===========================
//�����L���O�̓ǂݍ��ݏ���
//===========================
void LoadRanking(void)
{
	FILE*pFile;
	
	pFile = fopen(FILE_NAME, "r");

	if (pFile!=NULL)
	{
		//�s���ǂݍ���
		for (int nCnt=0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}

	//�t�@�C�������
	fclose(pFile);
}
//===========================
//�����L���O�̕ۑ�����
//===========================
void SaveRanking(void)
{
	FILE*pFile;

	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{
		//�s���ǂݍ���
		for (int nCnt=0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}

	//�t�@�C�������
	fclose(pFile);
}