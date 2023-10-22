//=================================================
// Content     (ゲームの設定)(camera.cpp)
// Author     : 有田明玄
//=================================================

//-----------------------------------------------------------------------------
//インクルード
//-----------------------------------------------------------------------------
#include "camera.h"
#include "renderer.h"
#include "Application.h"
#include "DebugProc.h"
#include "Player.h"
#include "input.h"
#include "utility.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define	DISTANCE_X	((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x))		//距離の計算用X
#define	DISTANCE_Y	((m_posV.y - m_posR.y) * (m_posV.y - m_posR.y))		//距離の計算用Y
#define DISTANCE_Z	((m_posV.z - m_posR.z) * (m_posV.z - m_posR.z))		//距離の計算用Z

//-----------------------------------------------------------------------------
//静的変数宣言
//-----------------------------------------------------------------------------
const float CCamera::CAMERA_NEAR = 1.0f;	// ニア
const float CCamera::CAMERA_FAR = 3500.0f;	// ファー
const float CCamera::FIELD_OF_VIEW = D3DXToRadian(45.0f);	// 視野角

//===========================
//コンストラクタ
//===========================
CCamera::CCamera()
{
}

//===========================
//デストラクタ
//===========================
CCamera::~CCamera()
{
}

//===========================
//カメラの初期化処理
//===========================
void CCamera::Init(void)
{
	//視点・注視点・上方向を設定
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot.x = atan2f((m_posV.y - m_posR.y), (m_posV.z - m_posR.z));

	m_viewPort.MinZ = 0.0f;
	m_viewPort.MaxZ = 1.0f;

	//引数を代入
	m_viewPort.X = 0;
	m_viewPort.Y = 0;
	m_viewPort.Width = SCREEN_WIDTH;
	m_viewPort.Height = SCREEN_HEIGHT;

	m_fDistance = sqrtf(DISTANCE_X + DISTANCE_Y + DISTANCE_Z);
}

//===========================
//カメラの終了処理
//===========================
void  CCamera::Uninit(void)
{

}

//===========================
//カメラの更新処理
//===========================
void  CCamera::Update(void)
{
	NormalizeRadian();	//角度の正規化

#ifdef _DEBUG

	CDebugProc::Print("カメラの視点の角度 x:%f y:%f z:%f\n",m_posV.x,m_posV.y,m_posV.z);
	CDebugProc::Print("カメラの注視点の角度 x:%f y:%f z:%f", m_posR.x, m_posR.y, m_posR.z);

#endif // _DEBUG

}

//===========================
//カメラの設定処理
//===========================
void  CCamera::Set(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	// ビューポートの設定
	pDevice->SetViewport(&m_viewPort);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	//float width = (float)SCREEN_WIDTH * 0.25f;
	//float height = (float)SCREEN_HEIGHT * 0.25f;
	//D3DXMatrixOrthoLH(&m_mtxProjection, width, height, CAMERA_NEAR, CAMERA_FAR);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		FIELD_OF_VIEW,						// 視野角
		(float)m_viewPort.Width / (float)m_viewPort.Height,	// アスペクト比
		CAMERA_NEAR,								// どこから
		CAMERA_FAR);								// どこまで描画するかの設定

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);	// プロジェクション座標行列の設定
}

//===========================
//角度の正規化
//===========================
void CCamera::NormalizeRadian(void)
{
	//角度の正規化
	m_rot.x = NormalizeAngle(m_rot.x);
	m_rot.y = NormalizeAngle(m_rot.y);
	m_rot.z = NormalizeAngle(m_rot.z);
}

//===========================
//生成
//===========================
CCamera * CCamera::Create(void)
{
	CCamera* pCamera = new CCamera;
	if (pCamera != nullptr)
	{
		pCamera->Init();
	}

	return pCamera;
}

void CCamera::AddPos(D3DXVECTOR3 move)
{
	m_posV += move;
	m_posR += move;
}

D3DXVECTOR3 CCamera::CalculateRotFromPos(const D3DXVECTOR3 & inPos)
{
	D3DXVECTOR3 rot;

	rot.y = atan2(inPos.x - m_posV.x, inPos.z - m_posV.z);
	rot.x = atan2(inPos.y - m_posV.y, inPos.z - m_posV.z);
	rot.z = 0.0f;

	//D3DXVECTOR3 vec = m_posV - inPos;

	//D3DXVec3Normalize(&vec,&vec);

	return rot;
}
