//=============================================================================
//
// �G�t�F�N�g
// Author : �L�c����
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define EFFECT_HEIGHT	(35)		//�v���C���[�̍���
#define EFFECT_WIDTH	(40)		//�v���C���[�̕�	
#define EFFECT_TEX		(4)			//�e�N�X�`���̖���

//�O���錾

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CEffect : public CObject2D
{
public:
	CEffect();
	~CEffect()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 siz, float lot, D3DXVECTOR3 move, int nLife, D3DXCOLOR col);
	static HRESULT Load();
	static void Unload();

private:
	//�����o�֐�
	static LPDIRECT3DTEXTURE9 m_apTexture[EFFECT_TEX];
	int m_Life;						//����
	D3DXVECTOR3 m_move;
	float m_alpha;					//�A���t�@�l
};
#endif // !_OBJECT_H_


