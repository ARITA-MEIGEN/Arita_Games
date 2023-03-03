//**************************************************
// 
// camera.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CAMERA_H_	// このマクロ定義がされてなかったら
#define _CAMERA_H_	// ２重インクルード防止のマクロ定義

//==================================================
// クラス/
//==================================================
class CCamera
{
	/* ↓定義↓ */
public:

	/* ↓メンバ関数↓ */
public:
	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デストラクタ

public:
	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Set();		// 設定
	void SetPos(const D3DXVECTOR3& pos);	// 位置の設定
	const D3DXVECTOR3& GetPos() const;		// 位置の取得
	const D3DXMATRIX& GetProj() const;		// プロジェクションの取得
	const D3DXMATRIX& GetView() const;		// ビューの取得

	/* ↓メンバ変数↓ */
private:
	D3DXMATRIX m_mtxProj;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;	// ビューマトリックス
	D3DXVECTOR3 m_posV;		// 視点
	D3DXVECTOR3 m_posR;		// 注視点
	D3DXVECTOR3 m_vecU;		// 上方向ベクトル
	float m_fFogValue;		// フォグの密度
	float m_fFogDensity;	// フォグ
};

#endif // !_CAMERA_H_
