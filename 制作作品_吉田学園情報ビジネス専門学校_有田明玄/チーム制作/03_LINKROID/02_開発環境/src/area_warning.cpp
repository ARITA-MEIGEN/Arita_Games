#include "area_warning.h"
#include "Object2D.h"

CAreaWarning * CAreaWarning::Create(const D3DXVECTOR3& inPos)
{
	CAreaWarning* warning = new CAreaWarning;

	assert(warning != nullptr);

	warning->Init();
	warning->SetPos(inPos);

	return warning;
}

CAreaWarning::CAreaWarning()
{
}

CAreaWarning::~CAreaWarning()
{
}

HRESULT CAreaWarning::Init()
{
	m_bg = CObject2D::Create(m_pos, D3DXVECTOR2(120.0f, 120.0f), 4);
	m_text = CObject2D::Create(m_pos, D3DXVECTOR2(100.0f, 100.0f), 4);
	m_text->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	return S_OK;
}

void CAreaWarning::Uninit()
{
	m_bg->Release();
	m_bg = nullptr;
	m_text->Release();
	m_text = nullptr;
}

void CAreaWarning::Update()
{
}

void CAreaWarning::Draw()
{
}

void CAreaWarning::SetPos(const D3DXVECTOR3 & inPos)
{
	m_pos = inPos;
	m_bg->SetPos(inPos);
	m_text->SetPos(inPos);
}
