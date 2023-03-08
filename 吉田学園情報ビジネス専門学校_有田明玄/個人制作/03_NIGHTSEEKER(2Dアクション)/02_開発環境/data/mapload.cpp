#include"main.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mapload.h"
#include"block.h"
#include"player.h"
#include"enemy.h"
#include"boss.h"

//�}�N����`
#define NUM_BLOCK_X			(320)		//�����p
#define NUM_BLOCK_Y			(18)		//�c���p
#define MAX_BLOCK_X			(32)		//��ʓ��̃u���b�N���p
#define MAX_BLOCK_Y			(18)		//��ʓ��̃u���b�N���p
#define FILE_BLOCK_PLACE	"data\\TXT\\mapdata.txt"	//�ǂݍ��ރt�@�C����
//�X�^�e�B�b�N�ϐ�
static int   s_Block[NUM_BLOCK_Y][NUM_BLOCK_X];					//�u���b�N�̍��W�̕ۑ�
static float blockW = (float)SCREEN_WIDTH / MAX_BLOCK_X;		//�u���b�N�̉��̒���
static float blockH = (float)SCREEN_HEIGHT / MAX_BLOCK_Y;		//�u���b�N�̏c�̒���
static float blockX[NUM_BLOCK_X];
static float blockY[NUM_BLOCK_Y];
//======================================================
//�}�b�v�ǂݍ��݂̏���������
//======================================================
void InitMapLoad(void)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK_X; nCnt++)
	{
		blockX[nCnt] = (nCnt%NUM_BLOCK_X)*blockW;
	}
	for (int nCnt = 0; nCnt < NUM_BLOCK_Y; nCnt++)
	{
		blockY[nCnt] = (nCnt%NUM_BLOCK_Y)*blockH;
	}
	//static int aBlock[NUM_BLOCK_Y][NUM_BLOCK_X];
	const int lenLine = 1024; //��s�̍ő吔
	char strLine[lenLine];
	FILE*fp = fopen(FILE_BLOCK_PLACE, "r");		//excel�̓ǂݍ��݁H
	if (fp != NULL)
	{
		//EXCEL�f�[�^�ǂݍ��ݗp
		for (int y = 0; y < NUM_BLOCK_Y; y++)
		{
			fgets(strLine, lenLine, fp);			//��s�ǂݍ���
			for (int x = 0; x < NUM_BLOCK_X; x++)
			{
				switch (atoi(&(strLine[x * 2])))	//���l���ꕶ�����󂯎��(����)	�Ȃ��x*2�Ȃ̂�������Ȃ��@atoi��char�^����int�^�ɕς���
				{
				case 0://�󂯎�������l�ɉ����Ďw��̐F�ɂ���
					s_Block[y][x] = 0;		
					break;
				case 1:	//��~�u���b�N����
					s_Block[y][x] = 1;		
					break;
				case 2:	//�ړ��u���b�N�̐���
					s_Block[y][x] = 2;		
					break;	
				case 3:	//�G�̐���
					s_Block[y][x] = 3;	
					break;
				case 4:	//�v���C���[�̐���
					s_Block[y][x] = 4;
					break;
				case 5:	//�{�X�̐����t���O
					s_Block[y][x] = 5;
					break;
				}
			}
		}
		//�u���b�N�z�u�p
		for (int y = 0; y < NUM_BLOCK_Y; y++)
		{
			for (int x = 0; x < NUM_BLOCK_X; x++)
			{
				switch (s_Block[y][x])	//���l���ꕶ�����󂯎��(����)	�Ȃ��x*2�Ȃ̂�������Ȃ��@atoi��char�^����int�^�ɕς���
				{
				case 0://�󂯎�������l�ɉ����Ďw��̐F�ɂ���
					break;
				case 1:	//��~�u���b�N����
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 1);	
					break;
				case 2:	//�ړ��u���b�N�̐���
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 2);
					break;
				case 3:	//�G�̐ݒ�
					SetEnemy(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f),0);
					break;
				case 4:	//�v���C���[�̐���
					SetPlayer(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f));
					break;
				case 5:	//�{�X�̐����t���O
					SetBlock(D3DXVECTOR3(blockW / 2 + blockX[x], blockH / 2 + blockY[y], 0.0f), blockW, blockH, 5);
					break;
				}
			}
		}
	}
}
//======================================================
//�}�b�v�ǂݍ��݂̍X�V����
//======================================================
void UpdateMapLoad(void)
{
	////static int aBlock[NUM_BLOCK_Y][NUM_BLOCK_X];
	//const int lenLine = 1024; //��s�̍ő吔
	//char strLine[lenLine];
	//FILE*fp = fopen(FILE_BLOCK_PLACE, "r");		//excel�̓ǂݍ��݁H
	//if (fp != NULL)
	//{
	//	for (int y = 0; y < NUM_BLOCK_Y; y++)
	//	{
	//		fgets(strLine, lenLine, fp);		//��s�ǂݍ���
	//		for (int x = 0; x < NUM_BLOCK_X; x++)
	//		{
	//			switch (atoi(&(strLine[x * 2])))//���l���ꕶ�����󂯎��(����)	�Ȃ��x*2�Ȃ̂�������Ȃ��@atoi��char�^����int�^�ɕς���
	//			{
	//			case 0://�󂯎�������l�ɉ����Ďw��̐F�ɂ���
	//				break;
	//			case 1:
	//				SetBlock(D3DXVECTOR3(blockX[x], blockY[y], 0.0f), blockW, blockH, 1);	//�u���b�N�̐ݒu
	//				break;
	//			}
	//		}
	//	}
	//}
}