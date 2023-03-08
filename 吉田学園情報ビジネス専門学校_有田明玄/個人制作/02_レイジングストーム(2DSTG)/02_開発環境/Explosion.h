//=============================================================================
//
// ����
// Author : �L�c����
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define EXPLOSION_TEX		(2)		//�摜�̖���
#define EXPLOSION_PTN		(8)		//�e�N�X�`���̃p�^�[����
#define EXPLOSION_TIME		(2)		//�ꖇ���Ƃ̕\������

//�O���錾
//=============================================================================
// �\���̒�`
//=============================================================================
class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR2 siz);

private:
	//�����o�֐�
	static LPDIRECT3DTEXTURE9 m_apTexture[EXPLOSION_TEX];
	int m_nAnimTimer;		//���ԁ@�^�C�}�[
	int m_nPtnAnim;			//�e�N�X�`���̖���
};
#endif // !_EXPLOSION_H_



