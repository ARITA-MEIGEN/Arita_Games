#ifndef _MAIN_H_						//���̃}�N����`������ĂȂ�������
#define _MAIN_H_						//��d�C���N���[�h�h�~�̃}�N����`

#include<windows.h>
#include"d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x800)		//�r���h���̌x���Ώ��p�}�N��
#include"dinput.h"						//���͏����ɕK�v
#include"xaudio2.h"						//�T�E���h�����ɕK�v
#include"Xinput.h"						//�W���C�p�b�h�����ɕK�v

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//d3d9.lib�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dInput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")		//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME			"WindowClass"							//�E�B���h�E�N���X�̖��O
#define	WINDOW_CLASSNAME	"NIGHTSEEKER"							//�E�B���h�E�̖��O
#define	SCREEN_WIDTH	(1280)										//�E�B���h�E�̕�
#define	SCREEN_HEIGHT	(720)										//�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_TUTOLIAL,	//�`���[�g���A�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_RANKING,	//�����L���O�̉��
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
void DrawFPS(void);

#endif 




