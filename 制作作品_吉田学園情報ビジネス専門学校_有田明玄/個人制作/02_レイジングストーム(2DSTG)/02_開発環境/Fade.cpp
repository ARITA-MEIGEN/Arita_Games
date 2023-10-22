//=================================================
// Content     (フェードの設定)(fade.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/29)
//=================================================
#include "fade.h"

//静的メンバ変数
 CFade::FADE CFade::m_fade;						
 CApplication::MODE CFade::m_modeNext;			
 D3DXCOLOR CFade::m_colorFade;					
//======================================================
//コンストラクタ
//======================================================
CFade::CFade()
{

}

//======================================================
//デストラクタ
//======================================================
CFade::~CFade()
{
}

//======================================================
//フェードの初期化処理
//======================================================
void CFade::Init(CApplication::MODE modeNext)
{
	m_aObject[0] = new CObject2D(CObject::OBJTYPE_FADE);
	m_aObject[0]->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_aObject[0]->SetPos(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0f));
	
	m_fade = FADE_IN;									//フェードイン状態に
	m_modeNext = modeNext;								//次の画面(モード)を設定
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒いポリゴン(不透明)にしておく
	m_aObject[0]->SetCol(m_colorFade);
	//モードの設定
	CApplication::SetMode(m_modeNext);
}

//======================================================
//フェードの終了処理
//======================================================
void CFade::Uninit(void)
{

}
//======================================================
//フェードの更新処理
//======================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//フェードイン状態
			m_colorFade.a -= 0.03f;			//ポリゴンを透明にしていく
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_colorFade.a += 0.01f;	//ポリゴンを不透明にしていく
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;			//何もしていない状態に

				//モード設定(次のモードに移行)
				CApplication::SetMode(m_modeNext);
			}
		}
	//頂点カラー設定
	m_aObject[0]->SetCol(m_colorFade);
	}
}
//======================================================
//フェードの描画処理
//======================================================
void CFade::Draw(void)
{

}
//======================================================
//フェードの設定処理
//======================================================
void CFade::Set(CApplication::MODE modeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;									//フェードアウト状態に
		m_modeNext = modeNext;								//次の画面(モード)を設定
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒いポリゴン(透明)にしておく
	}
}
//======================================================
//フェードの獲得処理
//======================================================
CFade::FADE CFade::Get(void)
{
	return m_fade;
}