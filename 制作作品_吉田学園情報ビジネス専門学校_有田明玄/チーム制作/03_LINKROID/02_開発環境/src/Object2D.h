//=============================================================================
//
// 2Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//インクルード
#include "Main.h"
#include "Object.h"
#include <string>

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CApplication;

class CObject2D : public CObject
{
private:
	// 頂点フォーマット
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// 頂点データ
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;	//テクスチャ座標
	};
public:
	//メンバ関数
	explicit CObject2D(int nPriority = 3);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static bool Hit(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos, D3DXVECTOR2 Siz, D3DXVECTOR2 TargetSiz);

	// 位置
	void SetPos(const D3DXVECTOR3& pos);
	void AddPos(const D3DXVECTOR3& add) { SetPos(m_Pos + add); }
	void SetSkillPos(const float &gauge);					//スキルゲージの設定
	D3DXVECTOR3 GetPos() { return m_Pos; }

	// 大きさ
	void SetSiz(D3DXVECTOR2 Siz);
	void AddSiz(D3DXVECTOR2 Siz) { SetSiz(m_Siz + Siz); }
	D3DXVECTOR2 GetSiz();

	// 色
	void SetCol(D3DXCOLOR col);
	void AddCol(D3DXCOLOR col) { SetCol(m_Col + col); };
	void SetColAlpha(float inAlpha) { SetCol(D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, inAlpha)); }
	D3DXCOLOR GetCol();

	// 角度
	void SetRot(float Rot);
	float GetRot();
	
	// テクスチャ
	void SetTextureKey(const std::string key) { m_textureKey = key; }
	void SetUV(float U1, float U2, float V1, float V2);
	D3DXVECTOR2 GetUV(int number);

	// 生成
	static CObject2D*Create(D3DXVECTOR3 pos, D3DXVECTOR2 siz, int Priority);
private:
	void VtxPos();
private:
	//メンバ変数
	std::string m_textureKey;			// テクスチャにアクセスするキー
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ポリゴンの頂点バッファ
	float m_fLength;					// 対角線の長さ
	float m_fAngle;						// 対角線の角度
	float m_Rot;						// 回転
	D3DXVECTOR3 m_Pos;					// 位置
	D3DXVECTOR2 m_Siz;					// 大きさ
	D3DXCOLOR m_Col;					// 色
	D3DXVECTOR2 m_UV[2];				// テクスチャ座標
};
#endif // !_OBJECT_H_

