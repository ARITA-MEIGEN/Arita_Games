//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "area.h"
#include "Map.h"
#include "Application.h"
#include "area_warning.h"
#include "Object3D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CArea::CArea(int nPriority) : CObject(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CArea::~CArea()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CArea::Init()
{
	isBeginUpdate = true;
	m_warning = CAreaWarning::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.6f,50.0f,0.0f));
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CArea::Uninit()
{
}

//=============================================================================
// 更新
//=============================================================================
void CArea::Update()
{
	if (isBeginUpdate)
	{
		m_functionAtSignsBegin();
		isBeginUpdate = false;
	}

	m_time--;
	m_signsTime--;
	
	if (m_signsTime <= 0)
	{
		m_functionAtSignsEnd();

		if (m_warning != nullptr)
		{
			m_warning->Release();
			m_warning = nullptr;
		}
	}

	if (m_time <= 10)
	{
		m_functionAtDied();
	}

	if (m_time <= 0)
	{
		Release();		// 破棄予定
		return;
	}
}

//=============================================================================
// 生成
//=============================================================================
CArea * CArea::Create(D3DXVECTOR2 index, const unsigned int inRange, const unsigned int inSignsTime, const unsigned int inDiedTime)
{
	CArea* area = new CArea;

	// 生成出来なければ
	assert(area != nullptr);

	area->Init();
	area->m_centerIndex = index;
	area->m_time = inSignsTime + inDiedTime;
	area->m_signsTime = inSignsTime;
	area->m_range = inRange;
	return area;
}
