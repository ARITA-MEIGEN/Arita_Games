//=============================================================================
//
// �I�u�W�F�N�g
// Author : �L�c����
//
//=============================================================================
//�C���N���[�h
#include"main.h"
#include"Application.h"
#include"Game.h"
#include"Player.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Enemy.h"
#include"Option.h"
#include"Bg.h"
#include"Effect.h"
#include"Item.h"
#include"Score.h"
#include"Lifegauge.h"
#include"Mapdata.h"
#include"sound.h"
#include"Special.h"
#include"EnemyManager.h"
#include"Boss.h"
#include"InputKeyBoard.h"
#include"InputJoyPad.h"
#include"Fade.h"

//�ÓI�����o�ϐ�
CPlayer*CGame::m_pPlayer = nullptr;
CExplosion*CGame::m_pExplosion = nullptr;
CEnemy*CGame::m_pEnemy = nullptr;
CBg*CGame::m_pBg = nullptr;
CScore*CGame::m_pScore = nullptr;
CLife*CGame::m_Life= nullptr;				//�̗̓Q�[�W
CMapdata* CGame::m_pMap = nullptr;
CSpecial*CGame::m_pSpecial=nullptr;
CGame::GAME CGame::m_gamestate;
//====================================
//�R���X�g���N�^
//====================================
CGame::CGame()
{
}

//====================================
//�f�X�g���N�^
//====================================
CGame::~CGame()
{

}

//====================================
//������
//====================================
HRESULT CGame::Init()
{
	//�e�N�X�`���̓ǂݍ���
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	COption::Load();
	CBg::Load();
	CEffect::Load();
	CItem::Load();
	CScore::Load();
	CLife::Load();
	CSpecial::Load();

	//�}�b�v�f�[�^�ǂݍ���
	m_pMap = new CMapdata;
	m_pMap->Load();

	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_GAME);
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f));

	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 460.0f, 35.0f, 0));
	m_pScore->SetScore(0);

	//�K�E�Z�Q�[�W
	m_pSpecial = CSpecial::Create(D3DXVECTOR3(SCREEN_WIDTH/2, 35.0f, 0));

	m_gamestate = GAME_NORMAL;

	//�̗�
	m_Life = CLife::Create();

	PlaySound(SOUND_LABEL_STAGE001);

	return S_OK;
}

//====================================
//�I��
//====================================
void CGame::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}
	if (m_pExplosion != nullptr)
	{
		m_pExplosion->Uninit();
		m_pExplosion = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	if (m_Life != nullptr)
	{
		m_Life->Uninit();
		m_Life = nullptr;
	}
	
	//�e�N�X�`���̔j��
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CPlayer::Unload();
	COption::Unload();
	CBg::Unload();
	CEffect::Unload();
	CItem::Unload();
	CScore::Unload();
	CLife::Unload();
}

//====================================
//�X�V
//====================================
void CGame::Update()
{
#ifdef _DEBUG
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad*pJoypad = CApplication::GetInputJoypad();

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_T) == true)
	{
		CItem::Create(CItem::ITEM_HEALING, D3DXVECTOR3(640.0f, 100.0f, 0.0f));
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_E) == true)
	{
		CEnemy::Create((CEnemy::MOVEPATTERN)4, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if ((pKeyboard->GetTrigger(DIK_RETURN) == true || pJoypad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true)
		&& CFade::Get() == CFade::FADE_NONE)		//ENTER�L�[
	{//�G���^�[�Ń��U���g��ʂ�
	 //���[�h�ݒ�
		CFade::Set(CApplication::MODE_RESULT);
	}

#endif // !_DEBUG
	m_pMap->Update();
}

//====================================
//�`��
//====================================
void CGame::Draw()
{

}

//====================================
//�v���C���[�̎擾
//====================================
CPlayer * CGame::GetPlayer()
{
	return m_pPlayer;
}

//====================================
//�����̎擾
//====================================
CExplosion * CGame::GetExplosion()
{
	return m_pExplosion;
}

//====================================
//�G�̎擾
//====================================
CEnemy * CGame::GetEnemy()
{
	return m_pEnemy;
}

//====================================
//�w�i�̎擾
//====================================
CBg * CGame::GetBg()
{
	return m_pBg;
}

//====================================
//�X�R�A�̎擾
//====================================
CScore * CGame::GetScore()
{
	return m_pScore;
}

//====================================
//�Q�[���̏�Ԑݒ�
//====================================
void CGame::SetGame(GAME gamestate)
{
	m_gamestate = gamestate;
}

//====================================
//�Q�[���̏�Ԋl��
//====================================
CGame::GAME CGame::GetGame()
{
	return m_gamestate;
}
