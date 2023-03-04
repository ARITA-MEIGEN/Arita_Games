//**************************************************
// 
// file_x_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FILE_X_MANAGER_H_	//このマクロ定義がされてなかったら
#define _FILE_X_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CFileX;

//==================================================
// クラス
//==================================================
class CFileXManager
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,			// 使用しない
		LABEL_NeedleBall = 0,		// 鉄球
		LABEL_Daruma_Head,			// ダルマの頭
		LABEL_Daruma_Body,			// ダルマの身体
		LABEL_Daruma_Body_Orange,	// ダルマの身体(オレンジ)
		LABEL_Daruma_Body_Yellow,	// ダルマの身体(イエロー)
		LABEL_WING,					// 羽根
		LABEL_HUMMER,				// ハンマー
		LABEL_BAMBOO,				// 門松
		LABEL_Hagoita,				// 羽子板
		LABEL_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CFileXManager();	// デフォルトコンストラクタ
	~CFileXManager();	// デストラクタ

public:
	void LoadAll();						// 全ての読み込み
	void Load(ELabel label);			// 指定の読み込み
	void Load(const string& str);		// 指定の読み込み
	void ReleaseAll();					// 全ての破棄
	void Release(ELabel label);			// 指定の破棄
	void Release(const string& str);	// 指定の破棄
	CFileX* Get(ELabel label);			// 情報の取得
	CFileX* Get(const string& str);		// 情報の取得
	const string& Change(ELabel label);	// 変換
	ELabel Change(const string& str);	// 変換

	/* ↓メンバ変数↓ */
private:
	CFileX* m_pFileX[LABEL_MAX];	// Xファイルの情報
};

#endif // !_FILE_X_MANAGER_H_
