//=================================================
// Content     (�Q�[���̐ݒ�)(game.cpp)
// Author     : �L�c����
// Since      : (�쐬��2021/08/29)
//=================================================
#include"Player.h"
#include"input.h"
#include"background.h"
#include"enemy.h"
#include"main.h"
#include"sound.h"
#include"game.h"
#include"pause.h"
#include"result.h"
#include"mapload.h"
#include"playereffect.h"
#include"block.h"
#include"GameUI.h"
#include"Attack.h"
#include"effect.h"
#include"score.h"
#include"boss.h"
#include"bullet.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCntGameState = 0;				//�Q�[���̏�ԃJ�E���^�[
bool g_bPause = false;					//�|�[�Y�����ǂ���
//============================
//�Q�[����ʂ̏���������
//============================
void InitGame(void)
{
	InitBG();			//�w�i�̏���������
	InitPlayer();		//�v���C���[�̏���������
	InitEnemy();		//�G�̏���������
	InitPause();		//�|�[�Y�̏���������
	InitPlayereffect();	//�c���̏���������
	InitPlayer();		//�v���C���[�̏���������
	InitBlock();		//�u���b�N�̏���������
	InitBoss();			//�{�X�̏�����
	InitMapLoad();		//�}�b�v�ǂݍ��݂̏���
	InitUI();			//UI�̏���������
	InitAttack();		//�U���G�t�F�N�g�̏�����
	InitEffect();		//�G�t�F�N�g�̏�����
	InitScore();		//�X�R�A�̏���������
	InitBullet();		//�e�̏�����
	SetScore(0);		//�X�R�A�̐ݒ�

	PlaySound(SOUND_LABEL_BGM000);
	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCntGameState = 0;			//�J�E���^�[�����Z�b�g����
}
//============================
//�Q�[����ʂ̏I������
//============================
void UninitGame(void)
{
	StopSound();
	UninitPlayer();			//�v���C���[�̏I������
	UninitEnemy();			//�G�̏I������
	UninitBG();				//�w�i�̏I������
	UninitPause();			//�|�[�Y�̏I������
	UninitPlayereffect();	//�c���̏I������
	UninitBlock();			//�u���b�N�̏I������
	UninitUI();				//UI�̏I������
	UninitAttack();			//�U���̏I������
	UninitEffect();			//�G�t�F�N�g�̏I������
	UninitBoss();			//�{�X�̏I������
	UninitScore();			//�X�R�A�̏I������
	UninitBullet();			//�e�̏I������
}
//============================
//�Q�[����ʂ̍X�V����
//============================
void UpdateGame(void)
{
	FADE pFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true && pFade == FADE_NONE)
	{//�|�[�Y�L�[(P�L�[)�������ꂽ
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_bPause = g_bPause ? false : true;
		InitPause();

	}
	if (g_bPause == false)
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:			//�ʏ���
		UpdateBG();				//�w�i�̍X�V����
		UpdateMapLoad();		//�}�b�v�ǂݍ��݂̍X�V����
		UpdatePlayer();			//�v���C���[�̍X�V����
		UpdateBlock();			//�u���b�N�̍X�V����
		UpdateEnemy();			//�G�̍X�V����
		UpdatePlayereffect();	//�c���̍X�V����
		UpdateUI();				//UI�̍X�V����
		UpdateAttack();			//�U���G�t�F�N�g�̍X�V����
		UpdateEffect();			//�G�t�F�N�g�̍X�V����
		UpdateBoss();			//�{�X�̍X�V����
		UpdateScore();			//�X�R�A�̍X�V����
		UpdateBullet();			//�e�̍X�V����
		break;
		case GAMESTATE_CLEAR:			//�I�����
			g_nCntGameState++;
			if (g_nCntGameState >= 60)
			{
				//g_gameState = GAMESTATE_NONE;

				//��ʂ̐ݒ�
				SetFade(MODE_RESULT);

				g_nCntGameState = 0;	//�^�C�}�[���Z�b�g
			}
			break;
		case GAMESTATE_FAILED:			//�I�����
			g_nCntGameState++;
			if (g_nCntGameState >= 60)
			{
				//g_gameState = GAMESTATE_NONE;

				//��ʂ̐ݒ�
				SetFade(MODE_RESULT);

				g_nCntGameState = 0;	//�^�C�}�[���Z�b�g
			}
			break;
		default:
			break;
		}
		g_nCntGameState++;	//�^�C�}�[�̐i�s
	}
	else
	{
		UpdatePause();			//�|�[�Y�̍X�V����
	}
}
//============================
//�Q�[����ʂ̕`�揈��
//============================
void DrawGame(void)
{
	DrawBG();				//�w�i�̕`�揈��
	DrawEnemy();			//�G�̕`�揈��
	DrawPlayereffect();		//�c���̕`�揈��
	DrawBlock();			//�u���b�N�̕`�揈��
	DrawAttack();			//�U���G�t�F�N�g�̕`�揈��
	DrawPlayer();			//�v���C���[�̕`�揈��
	DrawBoss();				//�{�X�̕`�揈��
	DrawBullet();			//�e�̕`�揈��
	DrawEffect();			//�G�t�F�N�g�̕`�揈��
	DrawScore();			//�X�R�A�̕`�揈��
	DrawUI();				//UI�̕`�揈��
	if (g_bPause==true)
	{
		DrawPause();		//�|�[�Y�̍X�V����
	}
}
//============================
//�Q�[���̏�ԏ����ݒ�
//============================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntGameState = 0;
}
//============================
//�Q�[���̏�Ԃ̎擾
//============================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//============================
//�|�[�Y�̗L�������ݒ�
//============================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}