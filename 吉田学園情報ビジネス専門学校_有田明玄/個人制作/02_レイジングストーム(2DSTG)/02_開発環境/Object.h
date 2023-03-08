//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�C���N���[�h
#include"main.h"

#define MAX_TYPE (12)

class CObject
{
public:
	//�\����
	enum EObjType
	{
		OBJTYPE_BG=0,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_OPTION,
		OBJTYPE_PLAYER,
		OBJTYPE_EFFECT,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ITEM,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_INVALID,
		OBJTYPE_MAX
	};

	//�����o�֐�
	explicit CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init(float Width, float Height) = 0;	//������
	virtual void Uninit() = 0;								//�I��
	virtual void Update() = 0;								//�X�V
	virtual void Draw() = 0;								//�`��
	static void ReleaseAll();								//�S�̂̔j��
	static void UpdateAll();								//�S�̂̍X�V
	static void DrawAll();									//�S�̂̕`��
	static CObject* GetObj(int m_nNumber, int nType);		//�I�u�W�F�N�g�̎擾�@�����̓I�u�W�F�N�g�̔ԍ�
	 EObjType GetObjType(int m_nNumber, int nType);	//�I�u�W�F�N�g�̎�ނ̐ݒ�	
	static int NumAll();									//�S�̂̐��̎擾
	void Release();											//�j��
	 void SetObjType(EObjType Type);						//��ނ̐ݒ�

protected:
	int m_frame;										//��������Ă���̎���


private:
	//�����o�ϐ�
	 EObjType m_ObjType;								//�I�u�W�F�N�g�̃^�C�v
	static CObject*m_apObject[MAX_TYPE][MAX_POLYGON];	//�z��	�D�揇�ʂƃI�u�W�F�N�g�̍ő吔
	static int m_nNumAll;								//�S�̂̐�
	int m_nID;											//�̎��ʔԍ�
	int m_nPriority;									//�`��̗D�揇��

};

#endif // !_OBJECT_H_
