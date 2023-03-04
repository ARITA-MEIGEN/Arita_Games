//===================================================
//
// メッセージの処理
// Author : Sato Teruto
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "message.h"
#include "renderer.h"

//=======================
// コンストラクタ
//=======================
CMessage::CMessage() : CObject2D(CObject::PRIORITY_2D)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	m_nCntTime = 0;		//時間カウント
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//=======================
// デストラクタ
//=======================
CMessage::~CMessage()
{

}

//=======================
// 初期化
//=======================
void CMessage::Init()
{
	CObject2D::Init();

	//オブジェクト情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetSize(D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f));
	CObject2D::SetTexture(CTexture::LAVEL_Tutorial);
}

//=======================
// 終了
//=======================
void CMessage::Uninit()
{
	CObject2D::Uninit();
}

//=======================
// 更新
//=======================
void CMessage::Update()
{
	CObject2D::Update();

	//カウントの加算
	m_nCntTime++;

	//-------------------
	// 徐々に透明にする
	//-------------------
	if (m_nCntTime >= 120)
	{
		m_col.a -= 0.05f;
		CObject2D::SetCol(m_col);
	}

	//-------------------
	// 完全に透明になった
	//-------------------
	if (m_col.a <= 0.0f)
	{
		CObject::SetRelease();
	}
}

//=======================
// 描画
//=======================
void CMessage::Draw()
{
	CObject2D::Draw();
}

//=======================
// 生成
// 引数：位置、幅、高さ
//=======================
CMessage *CMessage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMessage *pMessage = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pMessage = new CMessage;	//生成

	if (pMessage != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pMessage->m_pos = pos;
		pMessage->m_fWidth = fWidth;
		pMessage->m_fHeight = fHeight;

		//初期化
		pMessage->Init();
	}

	return pMessage;
}