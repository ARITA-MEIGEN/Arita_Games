//=================================================
// Content     (�u���b�N�̐ݒ�)(Block.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/10/12)
//=================================================
#include"block.h"
#include"player.h"
#include"input.h"
#include"enemy.h"
#include"boss.h"
//�X�^�e�B�b�N�ϐ�
static bool btexture;		//�e�N�X�`���𒣂邩�ǂ���
static LPDIRECT3DTEXTURE9 s_pTextureBlock = NULL;		//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffBlock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
static Block s_aBlock[MAX_BLOCK];						//�u���b�N�̏��
static bool bStopBlock;									//�u���b�N�̓������~�߂邩�ǂ���
	
//�X�^�e�B�b�N�֐�
static void SetBlockType(int nType, int BlockNumber);
//============================
//�u���b�N�̏���������
//============================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.jpg",
		&s_pTextureBlock);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		s_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aBlock[nCntBlock].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
		s_aBlock[nCntBlock].fHeight = 0.0f;
		s_aBlock[nCntBlock].fWidth = 0.0f;
	}

	btexture = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffBlock,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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
	s_pVtxBuffBlock->Unlock();
}
//============================
//�u���b�N�̏I������
//============================
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (s_pTextureBlock != NULL)
	{
		s_pTextureBlock->Release();
		s_pTextureBlock = NULL;
	}
	//���_�o�b�t�@��j��
	if (s_pVtxBuffBlock != NULL)
	{
		s_pVtxBuffBlock->Release();
		s_pVtxBuffBlock = NULL;
	}
}
//============================
//�u���b�N�̍X�V����
//============================
void UpdateBlock(void)
{
	int nCntBlock;
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//1�L�[���������Ƃ��e�N�X�`�����͂���
	 if (GetKeyboardTrigger(DIK_1) == true)
	{
		 btexture= !btexture;
	}
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���
			//�O��̈ʒu���L�^
			s_aBlock[nCntBlock].posold = s_aBlock[nCntBlock].pos;
			
			if (bStopBlock == false)
			{
				//��ʂ̒����ɗ������̐ݒ�
				CenterPlayer(&s_aBlock[nCntBlock].pos);
			}
			
			//�ʒu�̍X�V
			s_aBlock[nCntBlock].pos += s_aBlock[nCntBlock].move;

			//�v���C���[�̓����蔻��
			CollisionPlayer(&s_aBlock[nCntBlock].pos, &s_aBlock[nCntBlock].posold, &s_aBlock[nCntBlock].move, s_aBlock[nCntBlock].fWidth, s_aBlock[nCntBlock].fHeight);

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[1].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[2].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[3].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBlock->Unlock();
}
//==============================
//�u���b�N�̕`�揈��
//==============================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	if (btexture == true)
	{
		pDevice->SetTexture(0, s_pTextureBlock);
	}
	else if(btexture == false)
	{
		pDevice->SetTexture(0, NULL);
	}
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���

		 //�|���S���̕`��       
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
				nCntBlock * 4,							//���_�̊J�n�ꏊ
				2);										//�v���~�e�B�u�̐�
		}
	}
}
//=====================
//�u���b�N�̐ݒ菈��
//=====================
void SetBlock(D3DXVECTOR3 pos, float Width, float Height,int Type)
{
	int nCntBlock;
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�
			s_aBlock[nCntBlock].pos = pos;
			s_aBlock[nCntBlock].fHeight = Height;
			s_aBlock[nCntBlock].fWidth = Width;
			s_aBlock[nCntBlock].nType = Type;
			s_aBlock[nCntBlock].bUse = true;	//�g�p���Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[1].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, -s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[2].pos = D3DXVECTOR3(-s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;
			pVtx[3].pos = D3DXVECTOR3(+s_aBlock[nCntBlock].fWidth / 2, +s_aBlock[nCntBlock].fHeight / 2, 0) + s_aBlock[nCntBlock].pos;

			//�^�C�v�ɉ����ĐF��ړ��ʂ̐ݒ�
			SetBlockType(s_aBlock[nCntBlock].nType,nCntBlock);
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBlock->Unlock();
}
//=====================
//�u���b�N�̓����蔻��
//=====================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float Width, float Height,Block**pBlock)
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���
		bStopBlock = false;			//�ǂɓ������Ă��邩�ǂ���

	//�u���b�N�ɑ��肪�Ԃ�������
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (s_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă��� 
			if (pPos->x + Width / 2 > s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2 /*+ DASH_SPEED*/		//�u���b�N�̍��E�̐ݒ� 
				&& pPos->x - Width / 2 < s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2/*- DASH_SPEED*/)
			{
				//�ォ�痎���Ēn�ʂɂ߂荞�񂾏ꍇ(���)
				if (pPosOld->y <= s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2			//�O��̃v���C���[�̈ʒu(y��)���u���b�N�̈ʒu��荂���ꍇ
					&& pPos->y >= s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2			//���݂̃v���C���[�̈ʒu(y��)���u���b�N�̈ʒu���Ⴂ�ꍇ
					)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
				{//�v���C��-�ƃu���b�N������������
					if (pBlock!=NULL)
					{
						//�v���C���[�\���̂�pBlock��s_aBlock�̃A�h���X��ݒ�
						*pBlock = &s_aBlock[nCntBlock];
					}
					bIsLanding = true;
					pPos->y = s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2;
					pMove->y = 0;
				}
				//��������Ńu���b�N�ɂ߂荞�񂾏ꍇ(����)
				else if (pPosOld->y - Height >= s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2		//�O��̃v���C���[�̈ʒu���u���b�N�̈ʒu���Ⴂ�ꍇ
						&& pPos->y - Height <= s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2		//���݂̃v���C���[�̈ʒu���u���b�N�̈ʒu��荂���ꍇ
					)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
				{//�v���C��-�ƃu���b�N������������
					pMove->y = 0;
					pPos->y = s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2 + Height;
				}
			}
			 //������Ԃ������ꍇ
			if (pPosOld->y > s_aBlock[nCntBlock].pos.y - s_aBlock[nCntBlock].fHeight / 2		//�u���b�N�̏㉺�͈͎̔w��
				&& pPosOld->y - Height < s_aBlock[nCntBlock].pos.y + s_aBlock[nCntBlock].fHeight / 2)
			{
				//������Ԃ������ꍇ(�E��)
				if (pPosOld->x - Width / 2 >= s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 		//�O��̃v���C���[�̈ʒu���u���b�N�̈ʒu���E�ɂ���ꍇ
					&& pPos->x - Width / 2 < s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 		//���݂̃v���C���[�̈ʒu���u���b�N�̈ʒu��荶�ɂ���(�߂荞��ł���)�ꍇ
					)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
				{//�v���C��-�ƃu���b�N������������
					bStopBlock = true;
					pPos->x = s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2 + Width / 2;
					s_aBlock[nCntBlock].move.x = 0;
					pMove->x = 0;
				}																					
				//������Ԃ������ꍇ(����)
				else if (pPosOld->x + Width / 2 <= s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2	//�O��̃v���C���[�̈ʒu���u���b�N�̈ʒu��荶�ɂ���ꍇ
						 && pPos->x + Width / 2 > s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2	//���݂̃v���C���[�̈ʒu���u���b�N�̈ʒu���E�ɂ���(�߂荞��ł���)�ꍇ
					)//�v���C���[�̍��E�Ƀu���b�N�����������ꍇ
				{//�v���C��-�ƃu���b�N������������
					bStopBlock = true;
					pPos->x = s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2 - Width / 2;
					s_aBlock[nCntBlock].move.x = 0;
					pMove->x = 0;
				}
			}
			//�v���C���[�̊l������
			Player*pPlayer = GetPlayer();
			if (s_aBlock[nCntBlock].nType== 5
				&& (pPos->y - Height <= s_aBlock[nCntBlock].pos.y
				&&pPos->x <= s_aBlock[nCntBlock].pos.x + s_aBlock[nCntBlock].fWidth / 2
				&& pPos->x >= s_aBlock[nCntBlock].pos.x - s_aBlock[nCntBlock].fWidth / 2
				&&&pPlayer->pos==pPos))
			{//���̃u���b�N�̏��ʉ߂���ƃ{�X���o��
				SetBoss(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2, 0.0f));
			}
		}
	}
	return bIsLanding;
}
//=====================
//�u���b�N�̎�ނ̐ݒ�
//=====================
static void SetBlockType(int nType, int BlockNumber)
{
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	s_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	switch (nType)
	{
	case 1:
		pVtx[BlockNumber * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case 2:
		pVtx[BlockNumber * 4].col =		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	case 5:
		pVtx[BlockNumber * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[BlockNumber * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aBlock[BlockNumber].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffBlock->Unlock();
}
//=====================
//�u���b�N�̎擾����
//=====================
Block *GetBlock(void)
{//�G�l�~�[�̃|�C���^�����Z�b�g
	return &s_aBlock[0];
}