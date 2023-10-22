//=============================================================================
//
// オブジェクトの集まり
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _OBJECT_LIST_H_			// このマクロ定義がされてなかったら
#define _OBJECT_LIST_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>
#include <functional>

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CObject;

//=============================================================================
// タスククラス
//=============================================================================
class CObjectList
{
public:
	// リスト構造体
	struct SList
	{
		CObject* top;
		CObject* current;
	};

	// 優先順位
	enum EPriority
	{
		LEVEL_SYSTEM = 0,
		LEVEL_3D_1,
		LEVEL_2D_1,
		LEVEL_2D_2,
		LEVEL_DEBUG,
		LEVEL_DEBUG1,
		LEVEL_DEBUG3,
		LEVEL_2D_UI,
		LEVEL_FADE,
		LEVEL_MAX
	};

	// 追加方法
	enum EPushMethod
	{
		PUSH_CURRENT = 0,
		PUSH_TOP,
		PUSH_NEXT,
		PUSH_PREV
	};

private:
	static CObjectList* instance;
public:
	static CObjectList* GetInstance() { return instance != nullptr ? instance : instance = new CObjectList;}
private:
	CObjectList();
public:
	~CObjectList();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// Release
	void AllRelease();
	void AbsolutelyRelease();
	void PriorityRelease(const EPriority inPriotity);

	void AllProcess(std::function<void(CObject*)> func);
	void PriorityProcess(int cnt, std::function<void(CObject*)> func);

	// Setter
	void SetPushCurrent(CObject* inTask, int inPriority = 0);
	void SetPushTop(CObject* inTask, int inPriority = 0);
	void SetNextObject(CObject* inReference, CObject* inTask);
	void SetPrevObject(CObject* inReference, CObject* inTask);

	// Getter
	CObject* GetTop(int priority = 0) { return m_list.at(priority).top; }
	CObject* GetCurrent(int priority = 0) { return m_list.at(priority).current; }

	// 検索
	CObject* SearchRoleTop(int inRole, int inPriority);
	CObject* SearchRoleCurrent(int inRole, int inPriority);
	CObject* SearchSameRoleNext(CObject* inTask);
	CObject* SearchSameRolePrev(CObject* inTask);

	/* ポーズ状態にする */
	void Pause(bool isPause);

private:
	void DeleteObject();

private:
	std::unordered_map<int, SList> m_list;	// リスト一覧
	unsigned int m_createNumber;			// 合計生成数
	int m_priorityNumber;					// 描画順数

	bool m_isPouseStop;
};
#endif
