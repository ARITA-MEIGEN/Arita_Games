//=============================================================================
//
// Xファイル読み込み
// Author : 有田明玄
//
//=============================================================================

#ifndef _MODEL_H_
#define _MODEL_H_

//インクルード
#include"main.h"
#include"ObjectX.h"

//マクロ定義
#define PLAYER_LEGPARTS	(13)
#define	NUM_PLAYERPARTS	(1+PLAYER_LEGPARTS)

//前方宣言
class CShadow;

class CModel
{
public:
	explicit CModel();
	~CModel();
	//プロトタイプ宣言
	HRESULT		Init();
	void		Uninit(void);
	void		Update(void);
	void		Draw(D3DXMATRIX pMtx);
	static		CModel*Create();
	void		Shadow();						//影(使わない)
	void		Siz();							//サイズ設定
	void		SetModel(char* Filename);		//モデルの設定
	void		SetParent(CModel*pModel) ;
	CModel*		GetParent();
	D3DXMATRIX	GetMtx();
	void		SetRot(D3DXVECTOR3 rot);	
	D3DXVECTOR3 GetRot();
	void		SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3	GetPos();
	float		GetWidth();
	void		SetIdx(int Idx) { m_nIdx = Idx; };
	int			GetIdx() { return m_nIdx; };
	void		SetDPos(D3DXVECTOR3 pos) { m_DefaultPos = pos; };	//初期位置を設定
	D3DXVECTOR3	GetDPos() { return m_DefaultPos; };					//初期位置を取得
	void		SetDRot(D3DXVECTOR3 rot) { m_DefaultRot = rot; };	//初期角度を設定
	D3DXVECTOR3	GetDRot() { return m_DefaultRot; };					//初期角度を取得
	void		SetCol(D3DXCOLOR col);
	void		SetEmi(D3DXCOLOR col);								//発光の設定
	void		SetDP(int dp) { dp = m_nDamagePoint; };				//ダメージ属性を設定
	int			GetDP() { return m_nDamagePoint; };					//ダメージ属性を設定




private:
	LPD3DXBUFFER		m_pBuffMat;		//マテリアル情報へのポインタ
	DWORD				m_nNumMat;		//マテリアル情報の数
	LPD3DXMESH			m_pMesh;		//メッシュへのポインタ
	D3DXMATRIX			m_mtxParent;	//親のワールドマトリックス
	D3DXMATRIX			m_mtxWorld;		//子のワールドマトリックス
	D3DXMATRIX			m_mtxShadow;	//影用ワールドマトリックス
	D3DXVECTOR3			m_pos;			//位置
	D3DXVECTOR3			m_posold;		//前回の位置
	D3DXVECTOR3			m_rotDest;		//目的の角度の保存
	D3DXVECTOR3			m_rot;			//向き
	D3DXVECTOR3			m_vtxMax;		//モデルの最大座標
	D3DXVECTOR3			m_vtxMin;		//モデルの座標の最小値
	int					m_nIdx;			//自身の番号
	CModel*				m_pParent;		//親のモデルへのポインタ
	D3DXVECTOR3			m_DefaultPos;	//初期位置
	D3DXVECTOR3			m_DefaultRot;	//初期位置
	D3DXCOLOR			m_col;
	D3DXCOLOR			m_Emi;

	D3DXVECTOR3			m_TempPos;						//編集用の仮座標
	D3DXVECTOR3			m_TempRot;						//編集用の仮座標
	int					m_nDamagePoint;					//当たり判定の属性


};

#endif

