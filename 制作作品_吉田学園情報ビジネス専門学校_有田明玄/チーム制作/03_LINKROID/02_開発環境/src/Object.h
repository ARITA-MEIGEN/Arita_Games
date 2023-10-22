//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

// include
#include "ObjectList.h"

#include <functional>

// マクロ定義
#define UPDATE_FUNC_CAST(func) (static_cast<void(CObject::*)()>(&(func)))

class CObject
{
public:
	//構造体
	enum EType
	{
		OBJTYPE_NONE = -1,
		OBJTYPE_MAP = 0,
		OBJTYPE_PLANET,
		OBJTYPE_GOAL,
		OBJTYPE_BLOCK,
		OBJTYPE_MODEL,
		OBJTYPE_GIMMICK,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX,
	};

	//メンバ関数
	explicit CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;		// 初期化
	virtual void Uninit() = 0;		// 終了
	virtual void Update();		// 更新
	virtual void Draw() = 0;		// 描画
	void SetType(EType Type);		// 種類の設定

	int GetPriority() { return m_nPriority; }
	
	/* 破棄状況 */
	void Release() { m_bDead = true; }		// 破棄予定
	bool IsRelease() { return m_bDead; }	// 破棄予定なのか

	/* リスト構造 */
	void SetPrev(CObject* inTask) { m_pPrev = inTask; }
	CObject* GetPrev() { return m_pPrev; }
	void SetNext(CObject* inTask) { m_pNext = inTask; }
	CObject* GetNext() { return m_pNext; }


	/* ポーズ */
	void AttachActivityAtPouse() { m_isActivityAtPouse = true; }
	bool IsActivityAtPouse() { return m_isActivityAtPouse; }

protected:
	using UPDATE_FUNC = void(CObject::*)();
public:
	void InitStateFunc(const UPDATE_FUNC *funcList, int numFunc);

protected:
	void SetState(int inState) { m_nState = inState; }
	int GetState() const { return m_nState; }

protected:
	int m_frame;		// 生成されてからの時間

private:	//メンバ変数
	const UPDATE_FUNC *m_funcList;
	int m_numFunc;
	int m_nState;

	int m_nPriority;	// 描画の優先順位
	CObject* m_pPrev;	// 前のオブジェクト
	CObject* m_pNext;	// 次のオブジェクト
	bool m_bDead;		// 死亡フラグ
	EType m_type;		// タイプ

	bool m_isActivityAtPouse;
};

#endif // !_OBJECT_H_
