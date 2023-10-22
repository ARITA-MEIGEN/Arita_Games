//=============================================================================
//
// オブジェクト
// Author : 有田明玄
// Author : Yuda Kaito
//
//=============================================================================

//-----------------------------------------------------------------------------
//include
//-----------------------------------------------------------------------------
#include "Object.h"
#include "ObjectList.h"

//=============================================================================
// コンストラクタ
//=============================================================================
 CObject::CObject(int nPriority /*=3*/)
 {
	 m_nState = -1;
	 m_numFunc = 0;
	 m_isActivityAtPouse = false;
	 m_nPriority = nPriority;

	 CObjectList* taskGroup = CObjectList::GetInstance();

	 taskGroup->SetPushCurrent(this, m_nPriority);

	 m_bDead = false;
 }

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// 更新
//=============================================================================
void CObject::Update()
{
	//int state = GetState();
	//assert((state >= 0) && (state < m_numFunc));
	//(this->*(m_funcList[state]))();
}

void CObject::InitStateFunc(const UPDATE_FUNC * funcList, int numFunc)
{
	m_funcList = funcList;
	m_numFunc = numFunc;

}
