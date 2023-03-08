//=============================================================================
//
// �}�b�v�f�[�^�ǂݍ���
// Author : �L�c����
//
//=============================================================================

//�C���N���[�h
#include"Mapdata.h"
#include"Enemy.h"
#include"Item.h"
#include<string>
#include"EnemyManager.h"

//�ÓI�����o�ϐ�
CEnemyManager*CMapdata::m_pEManager = nullptr;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapdata::CMapdata()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapdata::~CMapdata()
{

}

//=============================================================================
//�X�V
//=============================================================================
void CMapdata::Update()
{
	m_pEManager->Update();
}

//=============================================================================
// �}�b�v�f�[�^�ǂݍ���
//=============================================================================
void CMapdata::Load()
{
	m_pEManager = new CEnemyManager;
	const int lenLine = 1024;	//1�P��̍ő吔
	char strLine[lenLine];		//�ǂݍ��ݗp�̕�����
	//DEBUG_MAPDATA
	//FILE_MAPDATA
	FILE*fp = fopen(FILE_MAPDATA, "r");		//�t�@�C���ǂݍ���
	if (fp != NULL)
	{
		for (int i = 0; i < lenLine; i++)
		{
			fgets(strLine, lenLine, fp);
			if (strncmp(strLine, "Object", 6) == 0)	//�Z������r���Ĉ�v���邩�ǂ������ׂ�
			{
				bEnd = false;
				while (bEnd == false)
				{
					fscanf(fp, "%s", &strLine[0]);	//�ǂݍ��񂾕������Ƃɐݒ肷��

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
						{//�^�C�v�ɂ���ĕ�����
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
