#ifndef _FADE_H_
#define _FADE_H_

#include "Application.h"
#include"Object2D.h"

class CFade
{
public:
	enum FADE
	{//フェードの状態
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX,
	};

	CFade();
	~CFade();
	//プロトタイプ宣言
	void Init(CApplication::MODE modeNext);				//フェードの初期化処理
	void Uninit(void);									//フェードの終了処理
	void Update(void);									//フェードの更新処理
	void Draw(void);									//フェードの描画処理
	static void Set(CApplication::MODE modeNext);		//フェードの設定処理
	static FADE Get(void);								//フェードの獲得処理

private:
	//グローバル変数
	CObject2D*m_aObject[1];							//フェード用ポリゴン
	static FADE m_fade;								//フェードの状態
	static CApplication::MODE m_modeNext;			//次の画面(モード)
	static D3DXCOLOR m_colorFade;					//ポリゴン(フェード)の色
};

#endif

