//**************************************************
// 
// light.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LIGHT_H_	//このマクロ定義がされてなかったら
#define _LIGHT_H_	//２重インクルード防止のマクロ定義

//==================================================
// クラス
//==================================================
class CLight
{
	/* ↓定義↓ */
private:
	static const int MAX_LIGHT = 3;	// ライトの最大値

	/* ↓静的メンバ関数↓ */
public:
	static CLight** CreateAll();	// 全ての生成
	static void ReleaseAll();		// 全ての解放
	static CLight* Get(int num);	// 取得

private:
	static CLight* Create(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec);	// 生成

		/* ↓静的メンバ変数↓ */
private:
	static CLight* m_pLight[MAX_LIGHT];	// ライトの情報

	/* ↓メンバ関数↓ */
public:
	CLight();	// デフォルトコンストラクタ
	~CLight();	// デストラクタ

public:
	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Set(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec);	// 設定
	D3DXVECTOR3 GetDir();	// 方向の取得

	/* ↓メンバ変数↓ */
private:
	D3DLIGHT9 m_light;	// ライトの情報
};

#endif // !_LIGHT_H_
