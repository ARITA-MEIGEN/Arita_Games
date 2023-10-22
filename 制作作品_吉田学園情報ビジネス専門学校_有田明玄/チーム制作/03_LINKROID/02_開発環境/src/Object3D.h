//=============================================================================
//
// 3Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//インクルード
#include"main.h"
#include"Object.h"

// 頂点フォーマット
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CApplication;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点データ
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標;
};

class CObject3D : public CObject
{
public:
	//メンバ関数
	explicit CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CObject3D*Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, int Priority);
	void BindTexture(LPDIRECT3DTEXTURE9 tex);

	//セッター
	void SetPos(const D3DXVECTOR3& pos);
	void SetSiz(const D3DXVECTOR3& siz);
	void SetRot(const D3DXVECTOR3& rot) { m_Rot = rot; };
	void SetCol(const D3DXCOLOR& col);
	void SetBackCulling(const bool isCulling) { m_isBackCulling = isCulling; }
	void SetMatrixWorld(const D3DXMATRIX& inMatrixWorld) { m_mtxWorld = inMatrixWorld; }
	void OnBillboard() { m_isBillboard = true; }
	void SetUV(float U1, float U2, float V1, float V2);

	//ゲッター
	const D3DXVECTOR3 GetPos() const { return m_Pos; }
	const D3DXVECTOR3 GetSiz() const { return m_Siz; }
	const D3DXVECTOR3 GetRot() const { return m_Rot; }
	const D3DXCOLOR GetCol() const { return m_Col; }
	const D3DXMATRIX GetMatrixWorld() const { return m_mtxWorld; }

	void SetTextureKey(const std::string key) { m_textureKey = key; }
private:
	//メンバ変数
	std::string m_textureKey;			// テクスチャにアクセスするキー
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//ポリゴンの頂点バッファ
	float m_fLength;					//対角線の長さ
	float m_fAngle;						//対角線の角度
	D3DXVECTOR3 m_Rot;					//回転
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_Pos;					//位置
	D3DXVECTOR3 m_Siz;					//大きさ
	D3DXCOLOR m_Col;					//色
	bool m_isBackCulling;				// 背面カリングの使用有無
	bool m_isBillboard;
};
#endif // !_OBJECT_H_


