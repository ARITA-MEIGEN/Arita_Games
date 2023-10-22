//================================================
//
//背景 [Bg.h]
//Author : Kishimoto Eiji
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
class CBg : public CObject
{
public: /* 静的メンバ関数 */
	static CBg *Create();	//生成

public: /* コンストラクタ・デストラクタ */
	explicit CBg(int nPriority = 4);
	~CBg() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void Circle_Pop();	//出現中のサークル
	void Circle_Move();	//移動中のサークル
	
private: /* メンバ変数 */
	CObject2D* m_pBg;		//背景
	CObject2D* m_pCircle;	//サークル

	bool m_bPop;	//出現中かどうか
};

#endif