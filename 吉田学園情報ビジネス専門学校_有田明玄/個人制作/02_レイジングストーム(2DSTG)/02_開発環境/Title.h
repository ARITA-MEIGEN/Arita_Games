//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//�C���N���[�h
#include"main.h"
#include"Application.h"

//�O���錾
class CBg;

class CTitle
{
public:
	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CBg*GetBg();

private:
	static CBg*m_pBg;
};

#endif


