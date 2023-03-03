//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

#ifndef _BG_H_
#define _BG_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"
#include"Application.h"

//�}�N����`
#define NUM_TEXBG		(7)			//�w�i�̃e�N�X�`���̖���
#define NUM_TITLEBG		(2)			//�w�i�̃e�N�X�`���̖���
#define NUM_GAMEBG		(3)			//�Q�[���̔w�i�̃e�N�X�`���̖���
#define NUM_RESULTBG	(1)			//���U���g�̔w�i�̃e�N�X�`���̖���
#define BG_SPEED		(-0.0008f)	//�w�i�̑��x
#define BG_FLASH		(0.02f)		//�^�C�g�����S�̓_�ő��x
#define MAX_BG			(3)			//�|���S���̐�

//=============================================================================
// �\���̒�`
//=============================================================================
class CBg : public CObject
{
public:
	CBg();
	~CBg()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CBg *Create(D3DXVECTOR3 pos, CApplication::MODE Bgptn);
	void SetPos(D3DXVECTOR3 pos);
	void Mode();
	void Colchange();	//�F�ύX


private:
	//�����o�֐�			
	static LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXBG];
	 CObject2D*m_apObject2D[MAX_BG];
	 CApplication::MODE m_BgPtn;		//�w�i�p�^�[��
	 D3DXVECTOR3 m_Pos;
	 D3DXVECTOR3 m_Move;
	 float m_fAlpha;
	 bool m_bflash;	//�A���t�@�l�����p

};
#endif // !_OBJECT_H_


