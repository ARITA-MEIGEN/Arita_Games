//===================================================
//
// メッシュヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "object3d.h"
#include "renderer.h"

//================================
// メッシュクラス
//================================
class CMeshField : public CObject
{
public:
	CMeshField();
	explicit CMeshField(EPriority nPriority);	//コンストラクタ
	~CMeshField();						//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetMeshSize(int nDivision, float fWidth);	//最大幅の設定
	void SetTexture(CTexture::ELabel texture);		//テクスチャの設定

	//------------------
	// 静的メンバ関数
	//------------------
	static CMeshField* Create(CTexture::ELabel texture);

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxVtx = 256;	//頂点の最大数

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_VtxPos[nMaxVtx];	//頂点の位置
	D3DXVECTOR3 m_Normal;			//面法線ベクトル格納用
	D3DXVECTOR3 m_VtxNor[nMaxVtx];	//頂点の法線ベクトル格納用
	D3DXVECTOR3 m_rot;				//向き
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス

	/* ↓ メッシュを構成する情報 */
	int m_nNumDivision;		//ポリゴンの分割数
	int m_nCntVtx;			//頂点の分割数
	int m_nNumVtx;			//頂点数
	int m_nNumPolygon;		//ポリゴン数
	int m_nNumIndex;		//インデックス数
	float m_fMaxWidth;		//メッシュフィールドの最大幅
	float m_fMeshWidth;		//メッシュフィールドの幅
	float m_fTexSize;		//テクスチャの分割サイズ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	CTexture::ELabel m_texture;			//テクスチャ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファへのポインタ
};

#endif