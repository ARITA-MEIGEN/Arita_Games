//**************************************************
// 
// model.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "file_x_manager.h"

//==================================================
// クラス
//==================================================
class CModel : public CObject
{
	/* ↓定義↓ */
public:
	
	/* ↓静的メンバ関数↓ */
public:
	static CModel* Create(CFileXManager::ELabel label);	// 生成

	/* ↓メンバ関数↓ */
public:
	CModel();			// デフォルトコンストラクタ
	~CModel() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetPos(const D3DXVECTOR3& pos);			// 位置の設定
	const D3DXVECTOR3& GetPos() const;				// 位置の取得
	void SetRot(const D3DXVECTOR3& rot);			// 向きの設定
	const D3DXVECTOR3& GetRot() const;				// 向きの取得
	void SetLabel(CFileXManager::ELabel label);		// 使用するモデルの設定
	CFileXManager::ELabel SetLabel();				// 使用するモデルの取得
	void SetQuaternion(const D3DXVECTOR3& move);	// クォータニオンの設定
	void SetIsQuaternion(bool quaternion);			// クォータニオンを使用するかどうかの設定

private:
	void ShadowDraw(D3DXMATRIX mtxWorld);	// 影の描画

	/* ↓メンバ変数↓ */
private:
	D3DXQUATERNION m_quaternion;	// クォータニオン
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_rot;				// 向き
	CFileXManager::ELabel m_label;	// 使用するモデル
	bool m_isQuaternion;	// クォータニオンを使用するかどうか
};

#endif // !_MODEL_H_
