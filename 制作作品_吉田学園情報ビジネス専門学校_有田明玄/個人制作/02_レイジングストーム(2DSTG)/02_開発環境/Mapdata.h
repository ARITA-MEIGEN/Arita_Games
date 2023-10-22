//=============================================================================
//
// �v���C���[
// Author : �L�c����
//
//=============================================================================

#ifndef _MAPDATA_H_
#define _MAPDATA_H_

//�C���N���[�h
#include"Application.h"

//�}�N����`
#define NUM_STAGE	(1)								//�X�e�[�W��
#define FILE_MAPDATA	"data\\TXT\\stage01.txt"	//�ǂݍ��ރt�@�C����
#define DEBUG_MAPDATA	"data\\TXT\\test.txt"		//�ǂݍ��ރt�@�C����


//�O���錾
class CEnemyManager;
//=============================================================================
// �\���̒�`
//=============================================================================
class CMapdata
{
public:
	enum OBJ
	{
		OBJ_ENEMY=0,
		OBJ_ITEM,
	};
	CMapdata();
	~CMapdata();
	void Update();
	void Load();

private:
	//�����o�֐�
	OBJ m_type;			//�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;	//�o�����W
	int m_frame;		//�o������
	int m_ptn;			//�o���p�^�[��
	bool bEnd;			//�I���t���O
	static CEnemyManager*m_pEManager;	//�G�Ǘ�

};
#endif 



