//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

#ifndef _OPTION_H_
#define _OPTION_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define OPTION_HEIGHT	(35)		//�v���C���[�̍���
#define OPTION_WIDTH	(40)		//�v���C���[�̕�	
#define OPTION_TEX		(2)			//�e�N�X�`���̖���
#define OPTION_MEMPOS	(60)		//�L������ʒu���W�̐�
#define MAX_OPTION		(2)			//�I�v�V�����̍ő吔

//�O���錾

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class COption : public CObject2D
{
public:
	COption();
	~COption()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static COption *Create(D3DXVECTOR3 pos);
	static HRESULT Load();						//�e�N�X�`���̓ǂݍ���
	static void Unload();						//�e�N�X�`���̔j��
	static void MemPos(D3DXVECTOR3 posold);		//�v���C���[�̍��W��ۑ�����
	static void ResetPos(D3DXVECTOR3 posold);

private:
	//�����o�֐�
	static D3DXVECTOR3 m_PlayerPosOld[OPTION_MEMPOS];			//�v���C���[�̍��W��ۑ�
	static LPDIRECT3DTEXTURE9 m_apTexture[OPTION_TEX];	
	int m_nId;						//���ʔԍ�
	static int  m_nNumOption;		//�S�̂̐�
};
#endif // !_OBJECT_H_


