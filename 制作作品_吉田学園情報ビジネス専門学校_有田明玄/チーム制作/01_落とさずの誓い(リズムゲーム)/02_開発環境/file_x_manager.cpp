//**************************************************
// 
// file_x_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "file_x_manager.h"
#include "file_x.h"

//==================================================
// 定義
//==================================================
namespace
{
const string FILE_PATH[] =
{// テクスチャのパス
	"data/MODEL/NeedleBall.x",			// 鉄球
	"data/MODEL/Daruma_Head.x",			// ダルマの頭
	"data/MODEL/Daruma_Body.x",			// ダルマの身体
	"data/MODEL/Daruma_Body_Orange.x",	// ダルマの身体(オレンジ)
	"data/MODEL/Daruma_Body_Yellow.x",	// ダルマの身体(イエロー)
	"data/MODEL/Wing.x",				// 羽根
	"data/MODEL/Hummer.x",				// ハンマー
	"data/MODEL/Bamboo.x",				// 門松
	"data/MODEL/Hagoita.x",				// 羽子板
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CFileXManager::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CFileXManager::CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		m_pFileX[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CFileXManager::~CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		assert(m_pFileX[i] == nullptr);
	}
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CFileXManager::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CFileXManager::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの読み込みがされている
		return;
	}

	// 生成
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CFileXManager::Load(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの読み込みがされている
		return;
	}

	// 生成
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CFileXManager::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 解放
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CFileXManager::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの情報の解放
		m_pFileX[label]->Uninit();
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CFileXManager::Release(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの情報の解放
		m_pFileX[label]->Uninit();
		delete m_pFileX[label];
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CFileX* CFileXManager::Get(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CFileX* CFileXManager::Get(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// 変換
//--------------------------------------------------
const string& CFileXManager::Change(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	return FILE_PATH[label];
}

//--------------------------------------------------
// 変換
//--------------------------------------------------
CFileXManager::ELabel CFileXManager::Change(const string& str)
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (FILE_PATH[i] == str)
		{// パスと同じ
			return (ELabel)i;
		}
	}

	return LABEL_NONE;
}
