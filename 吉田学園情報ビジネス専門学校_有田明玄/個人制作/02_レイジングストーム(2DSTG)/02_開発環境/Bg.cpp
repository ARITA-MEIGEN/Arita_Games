//=============================================================================
//
// 背景
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include "Bg.h"
#include"renderer.h"
#include"Application.h"
#include"Fade.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBg::m_apTexture[NUM_TEXBG];

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg() :CObject(OBJTYPE_BG)
{
	m_bflash = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBg::Init(float Width, float Height)
{
	for (int i = 0; i < MAX_BG; i++)
	{
		m_apObject2D[i] = new CObject2D(OBJTYPE_BG);
		m_apObject2D[i]->Init(Width, Height);
	}
	m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	m_Move.x = 0.0f;

	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CBg::Uninit()
{
	CObject::Release();
}

//=============================================================================
// 更新
//=============================================================================
void CBg::Update()
{
	Colchange();
	Mode();
	m_frame++;
}

//=============================================================================
// 描画
//=============================================================================
void CBg::Draw()
{

}

//=============================================================================
// データを読み込み
//=============================================================================
HRESULT CBg::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//タイトルロゴ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TitlelogoSTG.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TitlelogoSTG002.png",
		&m_apTexture[1]);

	//ゲーム
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG_002.jpg",
		&m_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&m_apTexture[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&m_apTexture[4]);

	//リザルト
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\STG001Result.png",
		&m_apTexture[5]);

	//ランキング
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RankBg.png",
		&m_apTexture[6]);

	return S_OK;
}

//=============================================================================
// データを破棄
//=============================================================================
void CBg::Unload()
{
	for (int i = 0; i <NUM_TEXBG; i++)
	{
		if (m_apTexture[i] != nullptr)
		{//テクスチャの破棄
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}
	}
}

//=============================================================================
// 背景生成
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos,CApplication::MODE Bgptn)
{
	CBg*pBg;
	pBg = new CBg;
	if (pBg != nullptr)
	{// ポリゴンの初期化処理
		pBg->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
		pBg->m_BgPtn = Bgptn;
		pBg->SetPos(pos);
		StopSound();
		switch (pBg->m_BgPtn)
		{
		case CApplication::MODE_TITLE:
			pBg->m_apObject2D[0]->BindTexture(m_apTexture[0]);
			pBg->m_apObject2D[1]->BindTexture(m_apTexture[1]);
			pBg->m_apObject2D[2]->Uninit();
			pBg->m_fAlpha = 1.0f;
			break;
		case CApplication::MODE_GAME:
			pBg->m_apObject2D[0]->BindTexture(m_apTexture[2]);
			pBg->m_apObject2D[1]->BindTexture(m_apTexture[3]);
			pBg->m_apObject2D[2]->BindTexture(m_apTexture[4]);
			break;
		case CApplication::MODE_RESULT:
			pBg->m_apObject2D[0]->BindTexture(m_apTexture[5]);
			pBg->m_apObject2D[1]->Uninit();
			pBg->m_apObject2D[2]->Uninit();
			break;
		case CApplication::MODE_RANKING:
			pBg->m_apObject2D[0]->BindTexture(m_apTexture[6]);
			pBg->m_apObject2D[1]->Uninit();
			pBg->m_apObject2D[2]->Uninit();
			pBg->m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
			break;
		}
	}
	return pBg;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CBg::SetPos(D3DXVECTOR3 pos)
{
	for (int i = 0; i < MAX_BG; i++)
	{
		m_apObject2D[i]->SetPos( pos);
	}
}

//=============================================================================
// モード切り替え
//=============================================================================
void CBg::Mode()
{
	switch (m_BgPtn)
	{
	case CApplication::MODE_TITLE:
		break;

	case CApplication::MODE_GAME:
		for (int i = 0; i < MAX_BG; i++)
		{
			m_Move.y = BG_SPEED;
			//テクスチャ座標の設定
			D3DXVECTOR2 pos[2];
			pos[0] = m_apObject2D[i]->GetUV(0);
			pos[1] = m_apObject2D[i]->GetUV(1);
			m_apObject2D[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
			//UV座標設定
			m_apObject2D[i]->SetUV(pos[0].x + (i + 1), pos[1].x + (i + 1), pos[0].y + m_Move.y*(i + 1), pos[1].y + m_Move.y*(i + 1));
		}

	case CApplication::MODE_RESULT:
		break;

	default:
		break;
	}
}

//=============================================================================
// タイトルの色変更
//=============================================================================
void CBg::Colchange()
{
	if (m_BgPtn == CApplication::MODE_TITLE)
	{
		//時間経過で点滅させたい
		if (m_fAlpha >= 1.0f)
		{
			m_bflash = false;
		}
		if (m_fAlpha <= 0.0f)
		{
			m_bflash = true;
		}
		if (m_bflash == true)
		{
			m_fAlpha += BG_FLASH;
		}
		else
		{
			m_fAlpha -= BG_FLASH;
		}
		if (CFade::Get() == CFade::FADE_NONE)
		{
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
		}
		else
		{
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
