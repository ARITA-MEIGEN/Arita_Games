//**************************************************
// 
// file_x.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FILE_X_H_	//このマクロ定義がされてなかったら
#define _FILE_X_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// クラス
//==================================================
class CFileX
{
	/* ↓定義↓ */
public:
	
	/* ↓静的メンバ関数↓ */
public:
	static CFileX* Create(const string& str);	// 生成

	/* ↓メンバ関数↓ */
public:
	CFileX();	// デフォルトコンストラクタ
	~CFileX();	// デストラクタ

public: 
	void Init();	// 初期化
	void Uninit();	// 終了

public:
	LPDIRECT3DTEXTURE9* GetTexture();		// テクスチャの取得
	LPD3DXMESH GetMesh();					// メッシュ情報の取得
	LPD3DXBUFFER GetBuffMat();				// マテリアル情報の取得
	DWORD GetNumMat();						// マテリアル情報の数の取得
	const D3DXVECTOR3& GetSize() const;		// サイズの取得
	const D3DXVECTOR3& GetVtxMin() const;	// 最小値の取得
	const D3DXVECTOR3& GetVtxMax() const;	// 最大値の取得

private:
	void Load(const string& str);	// 読み込み

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9* m_pTexture;	// テクスチャへのポインタ
	LPD3DXMESH m_pMesh;				// メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;		// マテリアル情報のポインタ
	DWORD m_numMat;					// マテリアル情報の数
	D3DXVECTOR3 m_size;				// サイズ
	D3DXVECTOR3 m_vtxMin;			// 最小値
	D3DXVECTOR3 m_vtxMax;			// 最大値
};

#endif // !_FILE_X_H_
