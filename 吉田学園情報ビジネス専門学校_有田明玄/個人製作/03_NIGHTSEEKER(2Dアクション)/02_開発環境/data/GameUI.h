//=================================================
// Content     (UI�̐ݒ�)(UI.h)
// Author     : �L�c����
// Since      : (�쐬��2021/11/01)
//=================================================
#ifndef _GAMEUI_H_			//���̃}�N����`������ĂȂ�������
#define _GAMEUI_H_			//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�}�N����`
#define		NUM_LIFE	(2)//�̗̓Q�[�W�Ɏg���e�N�X�`���̖���
//UI�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
}LifeUI;

//�v���g�^�C�v�錾
void InitUI(void);				//UI�̏���������
void UninitUI(void);			//UI�̏I������
void UpdateUI(void);			//UI�̍X�V����
void DrawUI(void);				//UI�̕`�揈��
#endif 

