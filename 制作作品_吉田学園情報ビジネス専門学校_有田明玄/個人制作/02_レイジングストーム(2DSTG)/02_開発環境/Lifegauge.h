//=============================================================================
//
// UI
// Author : �L�c����
//
//=============================================================================

#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

//�C���N���[�h
#include"main.h"
#include"Object2D.h"

//�}�N����`
#define LIFE_TEX		(2)						//UI�̐��ɉ����ăe�N�X�`���𑝂₷
#define LIFE_POLYGON	(5)						//�|���S����
#define LIFE_SIZ		(25.0f)					//�|���S���̑傫��
#define LIFEUI_SIZ_X	(75.0f)					//�|���S���̑傫��
#define LIFEUI_SIZ_Y	(40.0f)					//�|���S���̑傫��
#define LIFE_INTERVAL	(10.0f)					//�̗͓��m�̊Ԋu
#define LIFE_POS_X		(300.0f)				//�����ʒu
#define LIFE_POS_Y		(30.0f)					//�����ʒu
#define LIFELOGO_POS_X	(LIFE_POS_X -60.0f)		//�����ʒu
#define LIFELOGO_POS_Y	(LIFE_POS_Y)			//�����ʒu


//�O���錾

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
class CLife : public CObject
{
public:
	CLife();
	~CLife()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CLife *Create();
	static void SetPos();
	static void LifeRecovery();
	static void LifeDecrease();

private:
	//�����o�֐�			
	static LPDIRECT3DTEXTURE9 m_apTexture[LIFE_TEX];
	static CObject2D*m_apObject2D[LIFE_POLYGON];
	static CObject2D*m_aLifeUI;
	static int m_NumLife;
};

#endif // !_OBJECT_H_

