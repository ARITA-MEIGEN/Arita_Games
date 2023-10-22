//=================================================
// Content     (フェードの設定)(fade.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/08/29)
//=================================================
#include "fade.h"

 //===========================
 // コンストラクタ
 //===========================
 CFade::CFade()
 {

 }

 //===========================
 // デストラクタ
 //===========================
 CFade::~CFade()
 {

 }

 //===========================
 // 初期化
 //===========================
 HRESULT CFade::Init(CApplication::MODE modeNext)
 {
	 //列挙型の初期化
	 m_fade = FADE_IN;		//フェードイン状態
	 m_modeNext = modeNext;	//次の画面(モード)を設定
	 m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒いポリゴン(不透明)にしておく
	 m_bModeChange = false;

	 return S_OK;
 }

 //===========================
 // 終了
 //===========================
 void CFade::Uninit()
 {
	
 }

 //===========================
 // 更新
 //===========================
 void CFade::Update()
 {
	 if (m_fade != FADE_NONE)
	 {
		 if (m_fade == FADE_IN)
		 {//フェードイン状態
			 FadeIn();
		 }
		 else if (m_fade == FADE_OUT)
		 {//フェードアウト状態
			 FadeOut();
		 }
	 }
	 m_pObject->SetCol(m_col);
	 m_pObject->Update();		//後ろに置かないと生成された一瞬だけ透明のままになってしまう
 }

 //===========================
 // 描画
 //===========================
 void CFade::Draw()
 {
	 m_pObject->Draw();
 }

 //===========================
 // 設定
 //===========================
 void CFade::SetFade(CApplication::MODE modeNext)
 {
	 if (m_fade != FADE_OUT)
	 {
		 m_fade = FADE_OUT;		//フェードアウト状態に
		 m_modeNext = modeNext;	//次の画面を設定
		 m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 m_bModeChange = true;
	 }
 }
 //遷移なし
 void CFade::SetFade()
 {
	 if (m_fade != FADE_OUT)
	 {
		 m_fade = FADE_OUT;		//フェードアウト状態に
		 m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 m_bModeChange = false;
	 }
 }

 //===========================
 //生成
 //===========================
 CFade* CFade::Create()
 {
	 CFade* pFade = new CFade();
	 CApplication::getInstance()->SetMode(CApplication::MODE_TITLE);
	 pFade->CreateFade();
	 pFade->Init(CApplication::MODE_TITLE);


	 return pFade;
 }

 //===========================
 //ポリゴンの生成
 //===========================
 void CFade::CreateFade()
 {
	 m_pObject = new CObject2D(CObject::OBJTYPE_FADE);
	 m_pObject->Init();
	 m_pObject->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	 m_pObject->SetSiz(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));
	 m_pObject->SetCol(m_col);
 }

 //フェードイン
 void CFade::FadeIn()
 {
	 m_col.a -= 0.03f;	//ポリゴンを透明にしていく

	 if (m_col.a <= 0.0f)
	 {
		 m_col.a = 0.0f;
		 m_fade = FADE_NONE;	//何もしていない状態に
	 }
 }

 //フェードアウト
 void CFade::FadeOut()
 {
	 m_col.a += 0.03f;	//ポリゴンを不透明にしていく

	 if (m_col.a >= 1.0f)
	 {
		 m_col.a = 1.0f;
		 m_fade = FADE_IN;	//フェードイン状態に

		 if (m_bModeChange == true)
		 {//レンダラーの終了処理を通るためもう一度ポリゴンを生成しなければならない
			 CApplication::getInstance()->SetMode(m_modeNext);	//画面切り替え
			 CreateFade();
		 }
	 }
 }
