#ifndef _PLAYEREFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYEREFFECT_H_	//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
//�v���g�^�C�v�錾
void InitPlayereffect(void);		//�c���̏���������
void UninitPlayereffect(void);		//�c���̏I������
void UpdatePlayereffect(void);		//�c���̍X�V����
void DrawPlayereffect(void);		//�c���̕`�揈��

//�c���̐ݒ菈��
void SetPlayereffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadiuswidth, float fRadiusheight, int nLife, D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d);
#endif
