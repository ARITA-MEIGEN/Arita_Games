//=================================================
// Content     (ゲームの設定)(camera.cpp)
// Author     : 有田明玄
//=================================================

//インクルード
#include"camera.h"
#include "renderer.h"
#include"Application.h"
#include"InputKeyBoard.h"
#include"DebugProc.h"

//マクロ定義
#define	DISTANCE_X	((m_posV.x - m_posR.x)*(m_posV.x - m_posR.x))		//距離の計算用X
#define	DISTANCE_Y	((m_posV.y - m_posR.y)*(m_posV.y - m_posR.y))		//距離の計算用Y
#define DISTANCE_Z	((m_posV.z - m_posR.z)*(m_posV.z - m_posR.z))		//距離の計算用Z
#define CAMERA_SPEED	(5.0f)		//カメラの移動速度
#define CAMERA_FACTOR	(0.01f)		//カメラの追従の係数
#define CAMERA_ROTSPEED	(0.05f)		//カメラの旋回速度

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
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(40.0f, 0.0f, 10.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot.x = atan2f((m_posV.y - m_posR.y), (m_posV.z - m_posR.z));
	//m_fDistance=sqrtf(m_fDistance*m_fDistance+DISTANCE_Y);	
	m_fDistance = sqrtf(DISTANCE_X + DISTANCE_Y + DISTANCE_Z);

	m_posV = D3DXVECTOR3(-8.0f, 100.0f, 160.0f);
	m_posR = D3DXVECTOR3(-20.0f, 58.0f, 15.0f);
	m_rot = D3DXVECTOR3(1.8f, -3.0f, 0.0f);

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
	ControlPos();		//視点操作
	RadianPosR();		//注視点の旋回
	RadianPosV();		//視点の旋回
	//DestPos();		//カメラの追従
	NormalizeRadian();	//角度の正規化
}

//===========================
//カメラの設定処理
//===========================
void  CCamera::Set(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),								//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//アスペクト比
		1.0f,												//どこから
		2000.0f);											//どこまで描画するかの設定

															//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);									//プロジェクション座標行列の設定
}

//===========================
//注視点の旋回
//===========================
void CCamera::RadianPosR(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	//注視点の旋回
	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_rot.y -= CAMERA_ROTSPEED;
	}
	else if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_rot.y += CAMERA_ROTSPEED;
	}
	//縦
	if (pKeyboard->GetPress(DIK_I) == true)
	{//うえ 
		m_rot.x -= CAMERA_ROTSPEED;
	}
	else if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_rot.x += CAMERA_ROTSPEED;
	}
	//注視点の計算
	m_posR.z = m_posV.z + sinf(m_rot.x)*cosf(m_rot.y)*m_fDistance;
	m_posR.x = m_posV.x + sinf(m_rot.x)*sinf(m_rot.y)*m_fDistance;
	m_posR.y = m_posV.y +cosf(m_rot.x)*m_fDistance;

	CDebugProc::Print("カメラの注視点の旋回 I/J/K/L:X:%f Y:%f Z:%f", m_posR.z, m_posR.x,m_posR.y);

}

//===========================
//視点の旋回
//===========================
void CCamera::RadianPosV(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	//視点の旋回
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= CAMERA_ROTSPEED;
	}
	else if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += CAMERA_ROTSPEED;
	}
	if (pKeyboard->GetPress(DIK_R) == true)
	{
		m_rot.x += CAMERA_ROTSPEED;
	}
	else if (pKeyboard->GetPress(DIK_F) == true)
	{
		m_rot.x -= CAMERA_ROTSPEED;
	}

	//視点の旋回
	m_posV.z = m_posR.z - sinf(m_rot.x)*cosf(m_rot.y)*m_fDistance;
	m_posV.x = m_posR.x - sinf(m_rot.x)*sinf(m_rot.y)*m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x)*m_fDistance;

	CDebugProc::Print("カメラの視点の旋回 Q/E/R/F x:%f y:%f z:%f", m_posV.x, m_posV.y, m_posV.z);
}

//===========================
//角度の正規化
//===========================
void CCamera::NormalizeRadian(void)
{
	//角度の正規化
	if (m_rot.y >= D3DX_PI)
	{//y
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x >= D3DX_PI)
	{//x
		m_rot.x = D3DX_PI;
	}
	else if (m_rot.x <= -D3DX_PI)
	{
		m_rot.z = -D3DX_PI;
	}

	if (m_rot.z > D3DX_PI)
	{//z
		m_rot.z = -D3DX_PI;
	}
	else if (m_rot.z < -D3DX_PI)
	{
		m_rot.z = D3DX_PI;
	}
}

//===========================
//カメラの位置の操作
//===========================
void CCamera:: ControlPos(void)
{
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	//カメラの位置の操作
	if (pKeyboard->GetPress(DIK_W) == true)
	{//前
	 //先にsinf/cosfで角度を求めてから速度をかける
		m_posV.x += sinf(D3DX_PI*0.0f + m_rot.y) *CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI*0.0f + m_rot.y) *CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) *m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) *m_fDistance;
	}
	else if (pKeyboard->GetPress(DIK_S) == true)
	{//後ろ
		m_posV.x += sinf(D3DX_PI*1.0f + m_rot.y)*CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI*1.0f + m_rot.y)*CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y)*m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y)*m_fDistance;
	}
	if (pKeyboard->GetPress(DIK_D) == true)
	{//右
		m_posV.x += sinf(D3DX_PI*0.5f + m_rot.y)*CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI*0.5f + m_rot.y)*CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y)*m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y)*m_fDistance;
	}
	else if (pKeyboard->GetPress(DIK_A) == true)
	{//左
		m_posV.x += sinf(D3DX_PI*-0.5f + m_rot.y)*CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI*-0.5f + m_rot.y)*CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y)*m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y)*m_fDistance;
	}
	//else if (pKeyboard->GetPress(DIK_Z) == true)
	//{//上

	//}
	//else if (pKeyboard->GetPress(DIK_X) == true)
	//{//下

	//}

	CDebugProc::Print("カメラの視点の移動 W/A/S/D");
}

//===========================
//向きの取得
//===========================
D3DXVECTOR3 CCamera::Getrot(void)
{
	return m_rot;
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
