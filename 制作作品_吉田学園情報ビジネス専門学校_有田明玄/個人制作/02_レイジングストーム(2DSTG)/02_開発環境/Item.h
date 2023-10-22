//=============================================================================
//
// �A�C�e��
// Author : �L�c����
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define ITEM_HEIGHT		(50.0f)		//�A�C�e���̍���
#define ITEM_WIDTH		(50.0f)		//�A�C�e���̕�
#define ITEM_TEX		(1)			//�e�N�X�`���̖���

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CItem : public CObject2D
{
public:
	enum ITEMTYPE
	{
		ITEM_HEALING = 0,
		ITEM_SCOREUP,
		ITEM_MAX
	};

	CItem();												//�R���X�g���N�^
	~CItem()override;										//�f�X�g���N�^
	HRESULT Init(float Width, float Height)override;		//������
	void Uninit()override;									//�I��
	void Update()override;									//�X�V
	void Draw()override;									//�`��
	static HRESULT Load();									//�f�[�^��ǂݍ���
	static void Unload();									//�ǂݍ��񂾃f�[�^��j��
	static CItem *Create(ITEMTYPE nType,D3DXVECTOR3 pos);	//����

private:
	//�����o�֐�
	int m_move;
	ITEMTYPE m_ItemType;
	static int m_nItem;
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEM_TEX];
};
#endif // !_OBJECT_H_




