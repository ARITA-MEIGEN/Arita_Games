//=============================================================================
//
// マップデータ読み込み
// Author : 有田明玄
//
//=============================================================================

//インクルード
#include"Mapdata.h"
#include"Enemy.h"
#include"Item.h"
#include<string>
#include"EnemyManager.h"

//静的メンバ変数
CEnemyManager*CMapdata::m_pEManager = nullptr;
//=============================================================================
// コンストラクタ
//=============================================================================
CMapdata::CMapdata()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapdata::~CMapdata()
{

}

//=============================================================================
//更新
//=============================================================================
void CMapdata::Update()
{
	m_pEManager->Update();
}

//=============================================================================
// マップデータ読み込み
//=============================================================================
void CMapdata::Load()
{
	m_pEManager = new CEnemyManager;
	const int lenLine = 1024;	//1単語の最大数
	char strLine[lenLine];		//読み込み用の文字列
	//DEBUG_MAPDATA
	//FILE_MAPDATA
	FILE*fp = fopen(FILE_MAPDATA, "r");		//ファイル読み込み
	if (fp != NULL)
	{
		for (int i = 0; i < lenLine; i++)
		{
			fgets(strLine, lenLine, fp);
			if (strncmp(strLine, "Object", 6) == 0)	//六文字比較して一致するかどうか調べる
			{
				bEnd = false;
				while (bEnd == false)
				{
					fscanf(fp, "%s", &strLine[0]);	//読み込んだ文字ごとに設定する

					if (strncmp(strLine, "#", 1) == 0)
					{
						return;
					}
					else if (strncmp(strLine, "Enemy", 5) == 0)
					{
						m_type = OBJ_ENEMY;
					}
					else if (strncmp(strLine, "Item", 4) == 0)
					{
						m_type = OBJ_ITEM;
					}
					else if (strncmp(strLine, "Pos", 3) == 0)
					{
						fscanf(fp, "%f%f%f", &m_pos.x, &m_pos.y, &m_pos.z);
					}
					else if (strncmp(strLine, "Time", 4) == 0)
					{
						fscanf(fp, "%d", &m_frame);
					}
					else if (strncmp(strLine, "Ptn", 3) == 0)
					{
						fscanf(fp, "%d", &m_ptn);
					}
					else if (strncmp(strLine, "End", 3) == 0)
					{
						switch (m_type)
						{//タイプによって分ける
						case CMapdata::OBJ_ENEMY:
							m_pEManager->SetEnemy((CEnemy::MOVEPATTERN)m_ptn, m_pos,m_frame);
							break;
						case CMapdata::OBJ_ITEM:
							CItem::Create((CItem::ITEMTYPE)m_ptn, m_pos);
							break;
						default:
							break;
						}
						bEnd = true;
						break;
					}
				}
			}
		}
		fclose(fp);
	}
}
