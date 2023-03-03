#ifndef _RANKING_H_
#define _RANKING_H_

#include"main.h"
#include"fade.h"

class CScore;
class CBg;
//�}�N����`
#define MAX_RANK			(5)		//�����N��
#define NUM_RANK			(2)		//�����L���O�̃X�R�A�ȊO�̐�

class CRanking
{
public:
	CRanking();
	~CRanking();
	//�v���g�^�C�v�錾
	void Init(void);			//�����L���O�̏���������
	void Uninit(void);			//�����L���O�̏I������
	void Update(void);			//�����L���O�̍X�V����
	void Draw(void);			//�����L���O�̕`�揈��
	void Set(int nScore);		//�����L���O�̐ݒ�
	void Load();
	void Unload();
private:
	CBg*m_apBG;
	CObject2D*m_apUI;
	CScore*m_apScore[MAX_RANK];

	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nRankUpdate ;								//�X�V�����NNo.
	int m_nTimerRanking;								//�����L���O��ʕ\���^�C�}�[
	float m_fPtnrank;							//�v���C���[�_��
	int m_nCntrank;									//�_�ł̃J�E���g�p
};



#endif
