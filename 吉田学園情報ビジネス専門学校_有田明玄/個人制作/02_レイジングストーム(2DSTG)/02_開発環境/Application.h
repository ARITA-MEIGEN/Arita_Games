//=============================================================================
//
// �A�v���P�[�V����
// Author : �L�c����
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include"main.h"
#include"sound.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputJoyPad;
class CGame;
class CTitle;
class CResult;
class CFade;
class CMapdata;
class CTutorial;
class CRanking;

//�}�N����`
#define SCREEN_WIDTH	(1280)		// �X�N���[���̕�
#define SCREEN_HEIGHT	(720)		// �X�N���[���̍���
#define SLOW_SPEED		(3)			// �X���[���o�̍ۉ�F���ƂɃ����_���[���X�V����邩�ǂ���

// �v���g�^�C�v�錾
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};

	//�����o�֐�
	CApplication();
	~CApplication();
	HRESULT Init(HWND hWnd, bool bWindow,HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer*GetRenderer();
	static CInputKeyboard*GetInputKeyboard();
	static CInputJoyPad*GetInputJoypad();
	static DWORD m_dwGameStartTime;				//�Q�[���J�n����
	static DWORD m_dwGameTime;					//�Q�[���o�ߎ���
	static void DrawTime(LPD3DXFONT pFont);		//�o�ߎ��Ԃ̕`��
	static void SetMode(MODE mode);
	static MODE GetMode();
	static void StopTime(int frame);
	static void SlowTime(bool slow);

private:
	//�����o�ϐ�
	static CRenderer*m_pRenderer;
	static CInputKeyboard*m_pInputKeyboard;
	static CInputJoyPad*m_pInputJoyPad;
	static MODE m_mode;
	static bool m_bEndGame;		//�I���t���O
	//���
	static CTitle*m_pTitle;
	static CTutorial*m_pTutorial;
	static CGame*m_pGame;
	static CResult*m_pResult;
	static CRanking*m_pRank;

	static CFade*m_pFade;		//�t�F�[�h
	static int m_nScore;		//�X�R�A�ۑ��p
	static CMapdata*m_nMap;		//�}�b�v�f�[�^�ǂݍ���
	static int m_StopTime;		
	static bool m_bSlow;
	static int m_nFrame;		//���݂̃t���[��

};

#endif // !_APPLICATION_H_
