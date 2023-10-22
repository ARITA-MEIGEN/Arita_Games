//================================================
//
//背景 [Bg.h]
//Author : Yuda Kaito
//
//================================================
#ifndef _BG_H_
#define _BG_H_

//***************************
//インクルード
//***************************
#include "Object.h"

//***************************
//前方宣言
//***************************
class CObject2D;

//***************************
//ステータス表示クラスの定義
//***************************
class CAreaWarning : public CObject
{
public: /* 静的メンバ関数 */
	static CAreaWarning* Create(const D3DXVECTOR3& inPos);	//生成

public: /* コンストラクタ・デストラクタ */
	explicit CAreaWarning();
	~CAreaWarning() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//更新

	void SetPos(const D3DXVECTOR3& inPos);
private: /* メンバ関数 */

private: /* メンバ変数 */
	CObject2D* m_text;	// 警告テキスト
	CObject2D* m_bg;	// 背景

	D3DXVECTOR3 m_pos;
};

#endif