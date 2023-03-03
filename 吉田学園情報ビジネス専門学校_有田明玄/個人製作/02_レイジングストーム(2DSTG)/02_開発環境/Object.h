//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//インクルード
#include"main.h"

#define MAX_TYPE (12)

class CObject
{
public:
	//構造体
	enum EObjType
	{
		OBJTYPE_BG=0,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_OPTION,
		OBJTYPE_PLAYER,
		OBJTYPE_EFFECT,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ITEM,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_INVALID,
		OBJTYPE_MAX
	};

	//メンバ関数
	explicit CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init(float Width, float Height) = 0;	//初期化
	virtual void Uninit() = 0;								//終了
	virtual void Update() = 0;								//更新
	virtual void Draw() = 0;								//描画
	static void ReleaseAll();								//全体の破棄
	static void UpdateAll();								//全体の更新
	static void DrawAll();									//全体の描画
	static CObject* GetObj(int m_nNumber, int nType);		//オブジェクトの取得　引数はオブジェクトの番号
	 EObjType GetObjType(int m_nNumber, int nType);	//オブジェクトの種類の設定	
	static int NumAll();									//全体の数の取得
	void Release();											//破棄
	 void SetObjType(EObjType Type);						//種類の設定

protected:
	int m_frame;										//生成されてからの時間


private:
	//メンバ変数
	 EObjType m_ObjType;								//オブジェクトのタイプ
	static CObject*m_apObject[MAX_TYPE][MAX_POLYGON];	//配列	優先順位とオブジェクトの最大数
	static int m_nNumAll;								//全体の数
	int m_nID;											//個体識別番号
	int m_nPriority;									//描画の優先順位

};

#endif // !_OBJECT_H_
