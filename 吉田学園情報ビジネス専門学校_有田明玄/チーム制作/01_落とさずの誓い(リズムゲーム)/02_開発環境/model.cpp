//**************************************************
// 
// model.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "model.h"
#include "application.h"
#include "file_x_manager.h"
#include "file_x.h"
#include "light.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CModel* CModel::Create(CFileXManager::ELabel label)
{
	CModel* pModel = new CModel;

	if (pModel == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pModel->Init();

	// 使用するモデルの設定
	pModel->SetLabel(label);

	return pModel;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CModel::CModel() : CObject(CObject::PRIORITY_3D),
	m_quaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_label(CFileXManager::LABEL_NONE),
	m_isQuaternion(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CModel::~CModel()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CModel::Init()
{
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_label = CFileXManager::LABEL_NONE;
	m_isQuaternion = false;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CModel::Uninit()
{
	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CModel::Update()
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CModel::Draw()
{
	if (m_label == CFileXManager::LABEL_NONE)
	{// 使用しない
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	if (m_isQuaternion)
	{// クォータニオンを使用する
		// クォータニオンの使用した向きを反映
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	}
	else
	{
		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	}

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// 影の描画
	ShadowDraw(mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	D3DMATERIAL9 matDef;	// 現在のマテリアル保存用
	
	// 現在のマテリアル保持
	pDevice->GetMaterial(&matDef);

	// Xファイルの情報の取得
	CFileX* pObj = CApplication::GetInstance()->GetFileXManager()->Get(m_label);

	// マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pObj->GetBuffMat()->GetBufferPointer();

	for (int i = 0; i < (int)pObj->GetNumMat(); i++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, pObj->GetTexture()[i]);

		// モデルパーツの描画
		pObj->GetMesh()->DrawSubset(i);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CModel::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CModel::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// 向きの設定
//--------------------------------------------------
void CModel::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// 向きの取得
//--------------------------------------------------
const D3DXVECTOR3& CModel::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// 使用するモデルの設定
//--------------------------------------------------
void CModel::SetLabel(CFileXManager::ELabel label)
{
	m_label = label;
}

//--------------------------------------------------
// 使用するモデルの取得
//--------------------------------------------------
CFileXManager::ELabel CModel::SetLabel()
{
	return m_label;
}

//--------------------------------------------------
// クォータニオンの設定
//--------------------------------------------------
void CModel::SetQuaternion(const D3DXVECTOR3& move)
{
	if (!m_isQuaternion)
	{// クォータニオンを使用しない
		return;
	}

	D3DXVECTOR3 axis;	// 回転軸
	D3DXVECTOR3 inverseVec = -move;	// 移動量を反対にする
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 外積で回転軸を算出
	D3DXVec3Cross(&axis, &inverseVec, &vecY);

	// クォータニオンの計算
	D3DXQUATERNION quaternion;

	// 回転軸と回転角度を指定
	D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);

	// クォータニオンを適用
	m_quaternion *= quaternion;

	// クォータニオンの正規化
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);
}

//--------------------------------------------------
// クォータニオンを使用するかどうかの設定
//--------------------------------------------------
void CModel::SetIsQuaternion(bool quaternion)
{
	m_isQuaternion = quaternion;
}

//--------------------------------------------------
// 影の描画
//--------------------------------------------------
void CModel::ShadowDraw(D3DXMATRIX mtxWorld)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	D3DXMATRIX mtxShadow;
	
	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	D3DXVECTOR3 light = CLight::Get(0)->GetDir();
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-light, 0.0f);

	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPLANE planeField;

	// 法線と平面の１点から平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ライトと平面から影行列を作成
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// 影のマトリックスを反映
	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// テクスチャの設定
	pDevice->SetTexture(0, nullptr);

	// Xファイルの情報の取得
	CFileX* pFileX = CApplication::GetInstance()->GetFileXManager()->Get(m_label);

	// マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pFileX->GetBuffMat()->GetBufferPointer();
	D3DMATERIAL9 matD3D = pMat->MatD3D;

	// 色を黒色に変更
	matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// マテリアルの設定
	pDevice->SetMaterial(&matD3D);

	for (int i = 0; i < (int)pFileX->GetNumMat(); i++)
	{
		// モデルパーツの描画
		pFileX->GetMesh()->DrawSubset(i);
	}
}
