//=============================================================================
//
// �X�R�A
// Author : �L�c����
//
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define SCORE_HEIGHT			(60.0f)		//�X�R�A�̑傫���̍���
#define SCORE_WIDTH				(30.0f)		//�X�R�A�̑傫���̕�
#define RESULT_SCORE_HEIGHT		(120.0f)		//���U���g�̃X�R�A�̑傫��
#define RESULT_SCORE_WIDTH		(60.0f)		//���U���g�̃X�R�A�̑傫��
#define NUM_SCORE				(8)			//�X�R�A�̌������p�ӂ���

//�O���錾

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CScore : public CObject
{
public:
	CScore();
	~CScore()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CScore *Create(D3DXVECTOR3 pos);
	void SetPos(D3DXVECTOR3 pos,D3DXVECTOR2 siz);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore();
	void SetCol(D3DXCOLOR col);

private:
	//�����o�֐�			
	static LPDIRECT3DTEXTURE9 m_apTexture;
	CObject2D*m_apObject2D[NUM_SCORE];
	int m_Score;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_siz;
	D3DXCOLOR m_col;
};

#endif // !_OBJECT_H_
