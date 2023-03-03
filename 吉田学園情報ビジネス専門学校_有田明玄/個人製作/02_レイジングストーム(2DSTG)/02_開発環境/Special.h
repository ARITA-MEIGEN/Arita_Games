//=============================================================================
//
// �X�R�A
// Author : �L�c����
//
//=============================================================================

#ifndef _SPECIAL_H_
#define _SPECIAL_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define SPECIAL_HEIGHT		(25.0f)		//�Q�[�W�̍���
#define SPECIAL_WIDTH		(250.0f)	//�Q�[�W�̕�
#define MAX_SPECIAL			(100.0f)	//�K�E�Z�Q�[�W�̍ő�
#define NUM_TEX_SP			(2)			//�e�N�X�`���̖���
#define RECOVERY_QUANTITY	(0.03f)		//���R�񕜂����

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CSpecial : public CObject
{
public:
	CSpecial();
	~CSpecial()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CSpecial *Create(D3DXVECTOR3 pos);
	static void AddSpecial(float Special);
	static float GetSpecial();

private:
	//�����o�֐�			
	static CObject2D*m_apObject2D[NUM_TEX_SP];
	static LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEX_SP];
	static float m_nSpecial;
	static int m_stack;
};

#endif

