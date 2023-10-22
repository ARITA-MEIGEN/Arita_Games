//=================================================
// Content	(ゲームの設定)(camera.h)
// Author	: 有田明玄
//=================================================
#ifndef _CAMERA_H_	// このマクロ定義がされてなかったら
#define _CAMERA_H_	// 二重インクルード防止のマクロ定義

class CCamera
{
private:
	static const float CAMERA_NEAR;		// 移動速度
	static const float CAMERA_FAR;		// 追従の係数
	static const float FIELD_OF_VIEW;	// 視野角
public:
	CCamera();
	~CCamera();

	//プロトタイプ宣言
	virtual void Init();		// 初期化
	virtual void Uninit();		// 終了
	virtual void Update();		// 更新
	void Set();					// 設定
	void NormalizeRadian();		// 角度の正規化

	static CCamera* Create();	// 生成

	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; };	//視点
	D3DXVECTOR3 GetPosV() { return m_posV; };	//視点
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; };	//注視点
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		//向き
	void SetVecU(D3DXVECTOR3 vec) { m_vecU = vec; };

	void AddPos(D3DXVECTOR3 move);

	D3DXVECTOR3 CalculateRotFromPos(const D3DXVECTOR3& inPos);	// 位置からカメラに向くための角度を算出
protected:
	D3DXVECTOR3 m_posV;				// 視点
	D3DXVECTOR3 m_posVDest;			// 視点の目的地
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_posRDest;			// 注視点の目的地
	D3DXVECTOR3 m_vecU;				// 上方向ベクトル
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_rotDest;			// 向きの目的の角度
	float m_fDistance;				// 距離
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス

	D3DVIEWPORT9 m_viewPort;
};

#endif
