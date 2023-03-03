//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// クラス
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,		// 使用しない
		LABEL_Effect = 0,		// エフェクト
		LABEL_Cursor,			// カーソル
		LABEL_PressEnter,		// プレスエンター
		LABEL_TitleLogo,		// タイトルロゴ
		LABEL_Result,			// リザルト
		LAVEL_TATAMI,			// 畳
		LAVEL_TATAMI_NOLINE,	// 畳(線無し)
		LAVEL_PlayStart,		// 遊戯開始
		LAVEL_Tutorial,			// 達磨を護れ！
		LAVEL_Count,			//「護った回数　回」
		LABEL_Explanation,		// 操作説明(文言)
		LABEL_Explanation_Icon,	// 操作説明(アイコン)
		LABEL_Number,			// ナンバー画像
		LABEL_Number_Secret,	// ナンバー秘匿用
		LABEL_Ranking,			// らんきんぐ
		LABEL_Restart,			// もういちど
		LABEL_ReturnToTitle,	// たいとるへ
		LABEL_RankingBG002,		// ランキング背景
		LABEL_Title_Hackson,	// タイトル背景
		LABEL_Frame_Japan,		// 和風フレーム
		LABEL_Finish,			// そこまで！
		LABEL_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 m_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
