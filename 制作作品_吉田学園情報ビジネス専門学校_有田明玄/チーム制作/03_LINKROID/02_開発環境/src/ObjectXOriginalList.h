//=============================================================================
//
// オブジェクトXを読み込んで保存する処理 [objectX_group.h]
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _OBJECTX_ORIGINAL_LIST_H_
#define _OBJECTX_ORIGINAL_LIST_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include <string>
#include <vector>
#include <map>

//-----------------------------------------------------------------------------
//  ObjectX の原本を保存するクラス
//
//  ObjectX は std::string でのタグによって管理されている。
// 使用者はタグを知らないとデータにアクセスすることが出来ない。
// 全ての使用者は使用されているタグを知ることができるがそれがどのモデルに使用されているか分からない。
//-----------------------------------------------------------------------------
class CObjectXOriginalList
{
private: /* プライベート定数 */
	static const wchar_t* filePath;

public:

	// モデルデータ
	struct SModelData
	{
		LPD3DXMESH pMesh;		// メッシュへのポインタ
		LPD3DXBUFFER pBuffMat;	// マテリアル情報へのポインタ
		DWORD numMat;			// マテリアル情報の数
		D3DXVECTOR3 minVtx;		// モデルの座標の最小値
		D3DXVECTOR3 maxVtx;		// モデルの座標の最大値
		D3DXVECTOR3 size;		// 多きさ
	};

private:
	CObjectXOriginalList();
	static CObjectXOriginalList* m_originalList;
public:
	static CObjectXOriginalList* GetInstance();
	~CObjectXOriginalList();

	static void Uninit();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	void LoadAll();		// 全ての読み込み
	void UnloadAll();	// 全ての破棄
	SModelData Load(std::string inKey, std::string inFileName);	// 指定の読み込み
	SModelData Load(std::vector<std::string> inModel) { return Load(inModel[0], inModel[1]); }		// 指定の読み込み
	void Unload(std::string inKey);				// 指定の破棄

	// Getter
	SModelData GetModelData(std::string inKey) { return m_model[inKey]; }	// メッシュの取得
	LPD3DXMESH GetMesh(std::string inKey);		// メッシュの取得
	LPD3DXBUFFER GetBuffMat(std::string inKey);	// バッファーの取得
	DWORD GetNumMat(std::string inKey);			// マテリアル数の取得
	D3DXVECTOR3 GetMinVtx(std::string inKey);	// 最小頂点の取得
	D3DXVECTOR3 GetMaxVtx(std::string inKey);	// 最大頂点の取得
	D3DXVECTOR3 GetSize(std::string inKey);		// 大きさの取得
	std::string GetTag(int index);
	std::vector<std::string> GetTagList() { return m_tagList; };

private: /* プライベート関数 */
	bool ExistsKey(std::string inKey) { return m_model.count(inKey) != 0; }	// Map内に指定されたKeyが存在するか否か

private:
	std::map<std::string, SModelData, std::less<>> m_model;	// モデルの情報
	std::map<std::string, std::string, std::less<>> m_fileName;	// ファイル名の情報
	std::vector<std::string> m_tagList;	// タグリスト
};
#endif