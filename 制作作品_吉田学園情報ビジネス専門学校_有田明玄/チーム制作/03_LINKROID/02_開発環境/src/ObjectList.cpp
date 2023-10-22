//=============================================================================
//
// マネージャー
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "ObjectList.h"
#include "Object.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// 静的メンバー変数の宣言
//-----------------------------------------------------------------------------
CObjectList* CObjectList::instance = nullptr;

//=============================================================================
// コンストラクタ
// Author : Yuda Kaito
//=============================================================================
CObjectList::CObjectList() :
	m_priorityNumber(0),
	m_isPouseStop(false)
{
	m_list.clear();
}

//=============================================================================
// デストラクタ
// Author : Yuda Kaito
//=============================================================================
CObjectList::~CObjectList()
{
}

//=============================================================================
// 初期化
// Author : Yuda Kaito
//=============================================================================
HRESULT CObjectList::Init()
{
	return S_OK;
}

//=============================================================================
// 全てのタスクに処理を行う
// Author : Yuda Kaito
//=============================================================================
void CObjectList::AllProcess(std::function<void(CObject*)> func)
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		PriorityProcess(i, func);
	}
}

//=============================================================================
// 指定されたpriorityにあるタスク全ての処理を行う
// Author : Yuda Kaito
//=============================================================================
void CObjectList::PriorityProcess(int cnt, std::function<void(CObject*)> func)
{
	if (m_list.count(cnt) == 0)
	{
		return;
	}

	int objectCnt = 0;

	CObject* now = m_list.at(cnt).top;

	while (now != nullptr)
	{
		CObject* next = now->GetNext();

		func(now);
		objectCnt++;

		now = next;
	}
}

//=============================================================================
// 終了
// Author : Yuda Kaito
//=============================================================================
void CObjectList::Uninit()
{
	AllProcess([](CObject* object)
	{
		object->Release();
	});

	DeleteObject();	// タスクリストの削除

	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//=============================================================================
// 更新
// Author : Yuda Kaito
//=============================================================================
void CObjectList::Update()
{
	AllProcess([this](CObject* object)
	{
		if (!object->IsRelease())
		{
			if (!m_isPouseStop || object->IsActivityAtPouse())
			{
				object->Update();
			}
		}
	});

	DeleteObject();	// タスクリストの削除
}

//=============================================================================
// 描画
// Author : Yuda Kaito
//=============================================================================
void CObjectList::Draw()
{
	AllProcess([](CObject* object)
	{
		if (!object->IsRelease())
		{
			object->Draw();
		}
	});
}

//=============================================================================
// 所持しているタスクの破棄
// Author : Yuda Kaito
//=============================================================================
void CObjectList::AllRelease()
{
	AllProcess([](CObject* object)
	{
		object->Release();
	});

	DeleteObject();	// タスクリストの削除
}

//=============================================================================
// 絶対にタスクを破棄
// Author : Yuda Kaito
//=============================================================================
void CObjectList::AbsolutelyRelease()
{
	AllProcess([](CObject* object) {object->Release(); });
}

//=============================================================================
// 指定したpriorityのタスクを破棄
// Author : Yuda Kaito
//=============================================================================
void CObjectList::PriorityRelease(const EPriority inPriotity)
{
	if (m_list.count(inPriotity) == 0)
	{
		return;
	}

	CObject* now = m_list.at(inPriotity).top;

	while (now != nullptr)
	{
		now->Release();
		now = now->GetNext();
	}
}

//=============================================================================
// リストの最後にタスクを入れる
// Author : Yuda Kaito
//=============================================================================
void CObjectList::SetPushCurrent(CObject * inObject, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		inList.top = nullptr;
		inList.current = nullptr;
		m_list.insert(std::make_pair(inPriority, inList));

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	SList* list = &m_list.at(inPriority);

	if (list->current == nullptr && list->top == nullptr)
	{
		list->top = inObject;
		list->current = inObject;
	}
	else
	{
		CObject* current = list->current;		// 前回末尾
		list->current = inObject;				// 新規末尾
		list->current->SetPrev(current);	// 新規末尾の前に前回末尾を設定
		current->SetNext(list->current);	// 前回末尾の後に新規末尾を設定
	}
}

//=============================================================================
// リストの最初にタスクを入れる
// Author : Yuda Kaito
//=============================================================================
void CObjectList::SetPushTop(CObject * inObject, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		m_list.insert(std::make_pair(inPriority, inList));
		m_list.at(inPriority).top = nullptr;
		m_list.at(inPriority).current = nullptr;

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	if (m_list.at(inPriority).current == nullptr && m_list.at(inPriority).top == nullptr)
	{
		m_list.at(inPriority).top = inObject;
		m_list.at(inPriority).current = inObject;
	}
	else
	{
		CObject* top = m_list.at(inPriority).top;		// 前回先頭
		m_list.at(inPriority).top = inObject;			// 新規先頭
		m_list.at(inPriority).top->SetNext(top);	// 新規先頭の次に前回先頭を設定
		top->SetPrev(m_list.at(inPriority).top);	// 新規先頭の後に新規先頭を設定
	}
}

//=============================================================================
// 参照したタスクの次にタスクを入れる
// Author : Yuda Kaito
//=============================================================================
void CObjectList::SetNextObject(CObject* inReference, CObject* inObject)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inObject, 0);
		return;
	}

	CObject* currentNext = inReference->GetNext();	// nextの保存

	if (currentNext != nullptr)
	{
		inObject->SetNext(currentNext);
		inObject->SetPrev(inReference);
		inReference->SetNext(inObject);
		currentNext->SetPrev(inObject);
	}
	else
	{
		m_list.at((int)inReference->GetPriority()).current = inObject;
		inObject->SetNext(nullptr);
		inObject->SetPrev(inReference);
		inReference->SetNext(inObject);
	}
}

//=============================================================================
// 参照したタスクの前にタスクを入れる
// Author : Yuda Kaito
//=============================================================================
void CObjectList::SetPrevObject(CObject* inReference, CObject* inObject)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inObject);
		return;
	}

	CObject* currentPrev = inReference->GetPrev();	// nextの保存

	if (currentPrev != nullptr)
	{
		inObject->SetNext(inReference);
		inObject->SetPrev(currentPrev);
		currentPrev->SetNext(inObject);
		inReference->SetPrev(inObject);
	}
	else
	{
		m_list.at((int)inReference->GetPriority()).top = inObject;
		inObject->SetNext(inReference);
		inObject->SetPrev(nullptr);
		inReference->SetPrev(inObject);
	}

}

//=============================================================================
// ポーズ中に更新を止めるobjectの更新を止める
// Author : Yuda Kaito
//=============================================================================
void CObjectList::Pause(bool isPause)
{
	m_isPouseStop = isPause;
}

//=============================================================================
// タスクの削除
// Author : Yuda Kaito
//=============================================================================
void CObjectList::DeleteObject()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		// 削除
		auto Delete = [i, this](CObject* tack)
		{
			CObject* next = tack->GetNext();
			CObject* prev = tack->GetPrev();

			if (!tack->IsRelease())
			{
				return;
			}

			// 前後の状態を取得
			bool isNextNullptr = (next == nullptr);
			bool isPrevNullptr = (prev == nullptr);

			if (!isNextNullptr && !isPrevNullptr)
			{ // 前後にタスクが入っている場合
				next->SetPrev(prev);
				prev->SetNext(next);
			}
			else if (!isNextNullptr && isPrevNullptr)
			{ // 後のみタスクが入っている場合
				m_list.at(i).top = next;
				next->SetPrev(nullptr);
			}
			else if (isNextNullptr && !isPrevNullptr)
			{ // 前のみタスクが入っている場合
				m_list.at(i).current = prev;
				prev->SetNext(nullptr);
			}
			else
			{ // 前後にタスクが入っていない場合
				m_list.at(i).current = nullptr;
				m_list.at(i).top = nullptr;
				m_list.erase(i);
			}

			tack->Uninit();	// 終了
			delete tack;	// 削除
		};

		// priorityの全てのTackに引数の関数を行う
		PriorityProcess(i, Delete);
	}
}
