//=================================================
// Content     (処理)(ranking.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/09/15)
//=================================================
#include"ranking.h"
#include"sound.h"
#include"renderer.h"
#include"Application.h"
#include"Score.h"
#include"Bg.h"
#include"InputJoyPad.h"
#include"InputKeyBoard.h"

//====================================
//コンストラクタ
//====================================
CRanking::CRanking()
{
	 m_nRankUpdate = -1;	//更新ランクNo.
	 m_nTimerRanking;		//ランキング画面表示タイマー
	 m_fPtnrank = 1.0f;		//プレイヤー点滅
	 m_nCntrank = 0;		//点滅のカウント用
}

//====================================
//デストラクタ
//====================================
CRanking::~CRanking()
{
}

//============================
//初期化処理
//============================
void CRanking::Init(void)
{
	Load();	//テクスチャ読み込み
	CBg::Load();
	CScore::Load();

	//頂点ポインタを生成
	m_apBG = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CApplication::MODE_RANKING);
	m_apUI = CObject2D::Create(D3DXVECTOR3(500.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(160.0f, 600.0f), CObject::OBJTYPE_UI);
	m_apUI->BindTexture(m_pTexture);

	FILE*fp = fopen("data\\TXT\\score.txt", "r");		//ファイル読み込み
	const int lenLine = 1024;	//1単語の最大数
	int nrScore=0;		//読み込み用の文字列

	for (int i = 0; i < MAX_RANK; i++)
	{
		if (fp != NULL)
		{
			fscanf(fp, "%d", &nrScore);	//読み込んだ文字ごとに設定する
		}
		m_apScore[i] = CScore::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_apScore[i]->SetPos(D3DXVECTOR3(600.0f, 605.0f - (121.0f * i),0.0f), D3DXVECTOR2(40.0f, 100.0f));
		m_apScore[i]->SetScore(nrScore);
	}

	fclose(fp);

	//タイマーのリセット
	m_nTimerRanking = 0;
}

//===========================
//終了処理
//===========================
void  CRanking::Uninit(void)
{
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (m_apScore[i] != nullptr)
		{
			m_apScore[i]->Uninit();
			m_apScore[i] = nullptr;
		}
	}
	if (m_apBG != nullptr)
	{
		m_apBG->Uninit();
		m_apBG = nullptr;
	}
	if (m_apUI != nullptr)
	{
		m_apUI->Uninit();
		m_apUI = nullptr;
	}
	Unload();
	CBg::Unload();
	CScore::Unload();
}

//===========================
//更新処理
//===========================
void  CRanking::Update(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();
	CInputJoyPad* pJoyPad = CApplication::GetInputJoypad();

	m_nCntrank++;
	m_nTimerRanking++;

	if (m_nTimerRanking >= 1800
		||pKeyboard->GetTrigger(DIK_RETURN) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_Y) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_X) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_A) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_B) == true && CFade::Get() == CFade::FADE_NONE
		|| pJoyPad->GetJoypadTrigger(CInputJoyPad::JOYKEY_START) == true
		&& CFade::Get()	 == CFade::FADE_NONE)
	{//タイトルへ移行
		PlaySound(SOUND_LABEL_SE_GAMESTART);
		CFade::Set(CApplication::MODE_TITLE);
	}

	//スコアの設定
	if ((m_nCntrank % 30) == 0)
	{//ランクインしたとき点滅させるためのタイマー
		m_fPtnrank = 1.0f - m_fPtnrank;
	}

	//ランクインした場合
	if (m_nRankUpdate != -1)
	{
		for (int i = 0; i < MAX_RANK; i++)
		{
			//ランキングを点滅させる
			m_apScore[m_nRankUpdate]->SetCol(D3DXCOLOR(1.0f,0.0f,0.0f, m_fPtnrank));
		}
	}
}
//===========================
//描画処理
//===========================
void  CRanking::Draw(void)
{

}

//===========================
//設定処理
//===========================
void  CRanking::Set(int nScore)
{
	int nSave;
	m_nRankUpdate = -1;
	m_nTimerRanking = 0;
	if (nScore >= m_apScore[0]->GetScore())
	{//比較
		m_nRankUpdate++;
		m_apScore[0]->SetScore(nScore);
		for (int i = 0; i < MAX_RANK - 1; i++)
		{
			if (m_apScore[i]->GetScore() > m_apScore[i + 1]->GetScore())
			{//並べ替え
				nSave = m_apScore[i + 1]->GetScore();
				m_apScore[i + 1]->SetScore(m_apScore[i]->GetScore());
				m_apScore[i]->SetScore(nSave);
				m_nRankUpdate++;
			}
		}
	}
	FILE*fp = fopen("data\\TXT\\score.txt", "w");		//ファイル読み込み

	for (int i = 0; i < MAX_RANK; i++)
	{
		fprintf(fp, "%d\n", m_apScore[i]->GetScore());
	}

	fclose(fp);
}

//=============================================================================
// データを読み込み
//=============================================================================
void CRanking::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank.png",
		&m_pTexture);
}

//=============================================================================
// データを破棄
//=============================================================================
void CRanking::Unload()
{
	if (m_pTexture != nullptr)
	{//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
