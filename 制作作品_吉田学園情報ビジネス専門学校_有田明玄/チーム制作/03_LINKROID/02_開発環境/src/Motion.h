//**************************************************************************************************
//
// モーション処理(motion.h)
// Auther：唐﨑結斗
// Auther：Yuda Katio
// 概要 : モーションクラスの設定
//
//**************************************************************************************************
#ifndef _MOTION_H_			// このマクロ定義がされてなかったら
#define _MOTION_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectX;

//=============================================================================
// モーションクラス
// Author : 唐﨑結斗
// 概要 : モーション設定を行うクラス
//=============================================================================
class CMotion
{
public:
	//***************************************************************************
	// 定数定義
	//***************************************************************************
	static const unsigned int MOTION_BLEND_FRAM;		// モーションブレンドのフレーム数	

	//***************************************************************
	// キー構造体を定義
	//***************************************************************
	typedef struct
	{
		D3DXVECTOR3 pos;	// 現在位置
		D3DXVECTOR3 rot;	// 現在向き
	}MyKey;

	//***************************************************************
	// キー設定構造体を定義
	//***************************************************************
	typedef struct
	{
		int nFrame;					// フレーム数
		std::vector<MyKey> pKey;	// キー情報
	}MyKeySet;

	//***************************************************************
	// モーション設定構造体を定義
	//***************************************************************
	typedef struct
	{
		int nNumKey;		// キー数
		int nCntKeySet;		// キーセットカウント
		int nCntFrame;		// フレームカウント
		bool bLoop;			// ループ使用状況
		bool bMotion;		// モーションを行っているか
		std::vector<MyKeySet> pKeySet;	// キー設定情報
	}MyMotion;

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotion(const char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void Init();	// 初期化
	void Update();	// 更新
	void Uninit(void);	// 終了

	void ReloadMotion(const char *pFileName);	// モーションの再読み込み

	// モーションの有無
	void SetUseMotion(bool isMotion) { m_bMotion = isMotion; }		// モーションを行っているか設定
	bool GetMotion() { return m_bMotion; }							// モーションを行っているか取得

	// モーションブレンドを行なっているか
	bool GetMotionBlend() { return m_bMotionBlend; }				// モーションブレンドを行っているか取得
	void SetMotionBlend(bool isBlend) { m_bMotionBlend = isBlend; }	// モーションブレンドを行っているか設定

	// Setter
	void SetPartsOrigin();									// パーツをもとの場所に配置する
	void SetMotion(const unsigned int nCntMotionSet);		// モーションの初期設定
	void SetParts(D3DXMATRIX mtxWorld);						// パーツの設定
	void SetNumMotion(const unsigned int nNumMotion);		// モーション番号の設定

	void SetSizeMag(const D3DXVECTOR3& size);

	// Getter
	int GetMaxParts() { return m_nMaxParts; }					// パーツの最大数の取得
	std::vector<CObjectX*> GetParts() { return m_parts; }		// パーツモデルの取得
	CObjectX* GetParts(int index) { return m_parts[index]; }	// パーツのオブジェクトを取得

	void ChangeModel(int index, std::string path);

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void PlayMotion();	// モーションの再生
	void MotionBlend();	// モーションブレンド
	void LoodSetMotion(const char *pFileName);	// モーション読み込み
	void LoodTxt(const char *pFileName);		// モーション読み込み(.txt)
	void LoodJson(const char *pFileName);		// モーション読み込み(.json)
	void CntReset(const int nNumMotionOld);		// カウントリセット

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	std::vector<MyMotion> m_motion;			// モーション
	std::vector<CObjectX*> m_parts;			// パーツ
	std::vector<std::string> m_partsFile;	// パーツのXファイル名
	int m_nMaxParts;		// パーツ数
	int m_nNumMotion;		// 現在行っているモーション
	bool m_bMotion;			// モーションを行うか
	bool m_bMotionBlend;	// モーションブレンド
};
#endif

