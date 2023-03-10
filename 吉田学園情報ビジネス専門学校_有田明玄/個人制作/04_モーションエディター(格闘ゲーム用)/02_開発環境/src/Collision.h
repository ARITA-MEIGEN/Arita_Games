//=================================================
// Content     (ゲームの設定)(Line.h)
// Author     : 有田明玄
//=================================================
#ifndef _LINE_H_		//このマクロ定義がされてなかったら
#define _LINE_H_		//二重インクルード防止のマクロ定義
#include"main.h"
#include"Object.h"

//モデルの構造体
class CCollision :public CObject
{
public:
	enum COLLISION
	{
		COLLI_AXIS = 0,		//軸の判定
		COLLI_DAMAGE,		//ダメージ判定
		COLLI_SLOW,			//投げ判定
		COLLI_HURT,			//やられ判定
		COLLI_HURTSLOW,		//投げのやられ判定
	};

	//攻撃の属性
	enum EDAMAGE_POINT
	{
		DP_HIGH = 0,		//上段
		DP_MIDDLE,			//中段
		DP_LOW,				//下段
		DP_MAX,
	};

	explicit CCollision(int nPriority = 3);
	~CCollision();

	//プロトタイプ宣言
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	static CCollision* Create(D3DXVECTOR3 pos, COLLISION type);

	//ゲッターとセッター
	void SetSiz(D3DXVECTOR3 size) { m_width = size; };
	D3DXVECTOR3 GetSiz() { return m_width; };
	void SetPos(D3DXVECTOR3(pos)) { m_pos = pos; };
	D3DXVECTOR3 GetPos() { return m_pos; };
	void SwichUse() { bUse = !bUse; };						//オンオフの切り替え
	void SetUse(bool use) { bUse = use; };					//オンオフの切り替え
	void SetStartf(int start) { m_nStart = start; };		//開始フレーム
	int GetStartf() { return m_nStart; };					//開始フレーム
	void SetEndf(int end) { m_nEnd = end; };				//終了フレーム
	int GetEndf() { return m_nEnd; };						//終了フレーム
	void SetDPos(D3DXVECTOR3 pos) { m_defaultpos = pos; };	//初期位置
	void SetDRot(D3DXVECTOR3 rot) { m_defaultrot = rot; };	//初期向き
	D3DXVECTOR3 GetDPos() { return m_defaultpos; };			//初期位置
	D3DXVECTOR3 GetDRot() { return m_defaultrot; };			//初期向き
	void SetDMG(int dmg) { m_nDamage = dmg; };				//ダメージ
	int GetDMG() { return m_nDamage; };						//ダメージ
	void SetHitRig(int nRig) { m_nHitrig = nRig; };			//ヒット硬直
	int GetHitRig() { return m_nHitrig; };					//ヒット硬直
	void SetGuardRig(int nRig) { m_nGuardrig = nRig; };		//ガード硬直
	int GetGuardRig() { return m_nGuardrig; };				//ガード硬直
	void SetDp(EDAMAGE_POINT nDp) { m_nDp = nDp; };			//ダメージ属性設定
	EDAMAGE_POINT GetDp() { return m_nDp; };				//ダメージ属性設定
	void SetDown(bool down) { m_bDown = down; };			//ダウンする攻撃かどうかの設定
	bool GetDown() { return m_bDown; };						//ダウンする攻撃かどうかの設定

private:
	D3DXVECTOR3				m_pos;			//位置
	D3DXVECTOR3				m_width;		//幅
	D3DXVECTOR3				m_rot;			//向き
	D3DXCOLOR				m_col;			//色
	D3DXMATRIX				m_mtxWorld;		//ワールドマトリックス
	bool					bUse;			//使用しているかどうか
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;		//インデックスバッファ
	COLLISION				m_Colltype;		//当たり判定の種類
	int						m_nStart;		//開始フレーム
	int						m_nEnd;			//終了フレーム
	D3DXVECTOR3				m_defaultrot;	//向き
	D3DXVECTOR3				m_defaultpos;	//位置
	int						m_nDamage;		//ダメージ量
	int						m_nHitrig;		//ヒット硬直
	int						m_nGuardrig;	//ガード硬直
	EDAMAGE_POINT			m_nDp;			//ダメージ属性
	bool					m_bDown;		//ダウンさせる攻撃かどうか
};

#endif



