//=============================================================================
// Content     (ゲームの設定)(player.cpp)
// Author     : 有田明玄
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "ObjectX.h"
#include "Application.h"
#include "renderer.h"
#include "Camera.h"
#include "Shadow.h"
#include "Light.h"
#include "Game.h"

//マクロ定義
#define MIN_SPEED		(0.1f)	//摩擦による最低速度

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_mtxParent = nullptr;
	//m_modelData = nullptr;
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CObjectX::~CObjectX()
{

}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CObjectX::Init()
{
	//情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 座標
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_sizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 向き
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 色
	//影の生成
//	m_Shadow = CShadow::Create(m_pos, D3DXVECTOR3(50.0f,0.0f,50.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CObjectX::Uninit(void)
{
	CObject::Release();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CObjectX::Update(void)
{
	m_posold = m_pos;		//前回の位置の保存
	m_pos += m_move;		//位置の更新

//	m_Shadow->SetPos(m_pos);

	//移動量更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * MIN_SPEED;
	m_move.z += (0.0f - m_move.z) * MIN_SPEED;
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルの情報

	//現在のマテリアルを維持
	pDevice->GetMaterial(&matDef);

	//パーツのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxTrans, m_sizeMag.x, m_sizeMag.y, m_sizeMag.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//パーツのモデルの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//パーツのモデルの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParrent;
	D3DXMatrixIdentity(&mtxParrent);

	//親のマトリックスと掛け合わせる
	if (m_pParent != nullptr)
	{
		mtxParrent = m_pParent->GetMatrix();
	}
	else if(m_mtxParent != nullptr)
	{
		mtxParrent = *m_mtxParent;
	}
	else
	{
	}

	//親の座標とかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParrent);

	//影の生成
	//Shadow()

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	//マテリアルの描画
	for (int nCnt2 = 0; nCnt2 < (int)m_modelData.numMat; nCnt2++)
	{
		D3DXCOLOR emisive = pMat[nCnt2].MatD3D.Emissive;
		D3DXCOLOR diffuse = pMat[nCnt2].MatD3D.Diffuse;

		pMat[nCnt2].MatD3D.Emissive = m_materialColor[nCnt2];
		pMat[nCnt2].MatD3D.Diffuse.a = m_materialColor[nCnt2].a;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnt2].MatD3D);

		//プレイヤーパーツの描画
		m_modelData.pMesh->DrawSubset(nCnt2);

		pMat[nCnt2].MatD3D.Emissive = emisive;
		pMat[nCnt2].MatD3D.Diffuse = diffuse;
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//-----------------------------------------------------------------------------
// 操作
//-----------------------------------------------------------------------------
CObjectX * CObjectX::Create()
{
	CObjectX*pObjectX;
	pObjectX = new CObjectX();
	pObjectX->Init();

	return pObjectX;
}

//-----------------------------------------------------------------------------
// モデル読み込み
//-----------------------------------------------------------------------------
void CObjectX::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuff, DWORD pNumMat)
{
	m_modelData.pBuffMat = pBuff;
	m_modelData.pMesh = pMesh;
	m_modelData.numMat = pNumMat;
}

//-----------------------------------------------------------------------------
// モデルの割り当て
//-----------------------------------------------------------------------------
void CObjectX::BindModel(CObjectXOriginalList::SModelData model)
{
	m_modelData = model;
	m_materialColor.clear();
	m_materialColor.resize(m_modelData.numMat);

	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	for (size_t i = 0; i < m_modelData.numMat; i++)
	{
		D3DXCOLOR col;
		col.r = pMat[i].MatD3D.Emissive.r;
		col.g = pMat[i].MatD3D.Emissive.g;
		col.b = pMat[i].MatD3D.Emissive.b;
		col.a = pMat[i].MatD3D.Diffuse.a;
		SetColorMaterial(i, col);
	}
}

//-----------------------------------------------------------------------------
// 影の作成
//-----------------------------------------------------------------------------
void CObjectX::Shadow()
{
	D3DXMATERIAL *pMat;			//マテリアルのなんか
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	D3DXCOLOR col[2];			//色と発光の設定

	//影を描画する処理
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxShadow);

	//ライトの逆方向最後の数値はディレクショナルライト以外の場合動かすらしい？
	D3DXVECTOR3 lightvec = CGame::GetLight()->GetVec(2);		//ライトの取得
	vecLight = D3DXVECTOR4(-lightvec.x, -lightvec.y, -lightvec.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&m_mtxShadow, &vecLight, &planeField);

	//モデルのマトリックスとの掛け算
	D3DXMatrixMultiply(&m_mtxShadow, &m_mtxShadow, &m_mtxWorld);

	//影の描画
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxShadow);

	for (int i = 0; i < (int)m_modelData.numMat; i++)
	{
		col[0] = pMat[i].MatD3D.Diffuse;
		col[1] = pMat[i].MatD3D.Emissive;

		pMat[i].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMat[i].MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//プレイヤーパーツの描画
		m_modelData.pMesh->DrawSubset(i);

		pMat[i].MatD3D.Diffuse = col[0];
		pMat[i].MatD3D.Emissive = col[1];
	}
}

//-----------------------------------------------------------------------------
// 親モデルの登録かつ、親に自身を子供として保存
//-----------------------------------------------------------------------------
void CObjectX::SetParent(CObjectX * pModel)
{
	m_pParent = pModel;
	m_pParent->SetChildren(this);
}
