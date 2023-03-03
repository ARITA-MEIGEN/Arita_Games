//===================================================
//
// メッシュの処理
// Author : Sato Teruto
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "mesh_field.h"
#include "application.h"
#include "renderer.h"
#include "object3D.h"

//=======================
// コンストラクタ
//=======================
CMeshField::CMeshField() : CMeshField(PRIORITY_3D)
{
}
CMeshField::CMeshField(EPriority nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_VtxPos[nMaxVtx] = {};						//頂点の位置
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//面法線ベクトル格納用
	m_VtxNor[nMaxVtx] = {};						//頂点の法線ベクトル格納用
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	m_nNumDivision = 0;		//ポリゴンの分割数
	m_nCntVtx = 0;			//頂点の分割数
	m_nNumVtx = 0;			//頂点数
	m_nNumPolygon = 0;		//ポリゴン数
	m_nNumIndex = 0;		//インデックス数
	m_fMaxWidth = 0.0f;		//メッシュフィールドの最大幅
	m_fMeshWidth = 0.0f;	//メッシュフィールドの幅
	m_fTexSize = 0.0f;		//テクスチャの分割サイズ

	m_pVtxBuff = nullptr;	//頂点バッファへのポインタ
	m_pIdxBuff = nullptr;	//インデックスバッファへのポインタ
}

//=======================
// デストラクタ
//=======================
CMeshField::~CMeshField()
{
	assert(m_pVtxBuff == nullptr);
	assert(m_pIdxBuff == nullptr);
}

//=======================
// 初期化
//=======================
void CMeshField::Init()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	//----------------------------------
	// メッシュを構成する情報の設定
	//----------------------------------
	m_nNumDivision = 9;					//ポリゴンの分割数
	m_nCntVtx = m_nNumDivision + 1;		//頂点の分割数
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//頂点数
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//ポリゴン数
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//インデックス数
	m_fMaxWidth = 1800.0f;								//メッシュフィールドの最大幅
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//メッシュフィールドの幅
	m_fTexSize = (1.0f / m_nNumDivision);				//テクスチャの分割サイズ


	//----------------------------------
	// 頂点バッファの生成
	//----------------------------------
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX) * m_nNumVtx,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								CObject3D::FVF_VERTEX,			//頂点フォーマット
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//----------------------------------
	// インデックスバッファの生成
	//----------------------------------
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,			//頂点フォーマット
								D3DPOOL_MANAGED,
								&m_pIdxBuff,
								NULL);

	CObject3D::VERTEX* pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//----------------------------------
	// 頂点情報の設定
	//----------------------------------
	for (int z = 0; z < m_nCntVtx; z++)
	{
		for (int x = 0; x < m_nCntVtx; x++)
		{
			//頂点座標の設定
			{
				D3DXVECTOR3 vtxPos(-(m_fMaxWidth / 2) + (m_fMeshWidth * x), 0.0f, (m_fMaxWidth / 2) - (m_fMeshWidth * z));
				pVtx[x + (z * (m_nCntVtx))].pos = vtxPos;
			}

			//各頂点の法線の設定(※ベクトルの大きさは必ず1にする必要がある)
			pVtx[x + (z * (m_nCntVtx))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[x + (z * (m_nCntVtx))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[x + (z * (m_nCntVtx))].tex = D3DXVECTOR2(0.0f + m_fTexSize * x, 0.0f + m_fTexSize * z);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//----------------------------------
	// インデックスの設定
	//----------------------------------
	int nCnt = 0;

	for (int Z = 0; Z < m_nNumDivision; Z++)
	{
		for (int X = 0; X < m_nCntVtx; X++)
		{
			//インデックスバッファの設定
			pIdx[nCnt] = (WORD(X + Z * (m_nCntVtx)+(m_nCntVtx)));
			pIdx[nCnt + 1] = (WORD(X + Z * (m_nCntVtx)));

			nCnt += 2;

			//縮退ポリゴンの追加
			if (X == m_nNumDivision)
			{
				pIdx[nCnt] = (WORD)(X + Z * m_nCntVtx);
				pIdx[nCnt + 1] = (WORD)((Z + 2) * m_nCntVtx);

				nCnt += 2;
			}
		}
	}

	pVtx += m_nNumVtx;
	pIdx += m_nNumIndex;

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

//=======================
// 終了
//=======================
void CMeshField::Uninit()
{
	//頂点バッファの破壊
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの破壊
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Release();
}

//=======================
// 更新
//=======================
void CMeshField::Update()
{

}

//=======================
// 描画
//=======================
void CMeshField::Draw()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	//------------------------------------
	// マトリックス
	//------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//------------------------------------
	// 頂点
	//------------------------------------
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(CObject3D::FVF_VERTEX);

	//------------------------------------
	// テクスチャ
	//------------------------------------
	//テクスチャの取得
	CTexture *pTexture = CApplication::GetInstance()->GetTexture();

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									0,
									0,
									m_nNumVtx,	//頂点数
									0,
									m_nNumPolygon);	//描画するプリミティブ数

	//テクスチャのリセット
	pDevice->SetTexture(0, NULL);
}

//=======================
// 生成
//=======================
CMeshField* CMeshField::Create(CTexture::ELabel texture)
{
	CMeshField *pMeshField = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pMeshField = new CMeshField;	//生成

	if (pMeshField != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pMeshField->m_texture = texture;

		//初期化
		pMeshField->Init();
	}

	return pMeshField;
}


//===========================
// 分割数と幅の設定
//===========================
void CMeshField::SetMeshSize(int nDivision, float fWidth)
{
	m_nNumDivision = nDivision;	//ポリゴンの分割数の設定
	m_fMaxWidth = fWidth;		//メッシュフィールドの最大幅の設定

	//----------------------------
	// メッシュの情報の再設定
	//----------------------------
	m_nCntVtx = m_nNumDivision + 1;		//頂点の分割数
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//頂点数
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//ポリゴン数
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//インデックス数
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//メッシュフィールドの幅
	m_fTexSize = (1.0f / m_nNumDivision);				//テクスチャの分割サイズ
}

//===========================
// テクスチャの設定
//===========================
void CMeshField::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}