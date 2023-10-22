#include "sky_bg.h"

CSkyBg::CSkyBg() : CObject3D(2)
{
}

CSkyBg::~CSkyBg()
{
}

HRESULT CSkyBg::Init()
{
	CObject3D::Init();
	m_uPos = 0.0f;
	SetPos(D3DXVECTOR3(200.0f, 500.0f, 1700.0f));
	SetSiz(D3DXVECTOR3(6000.0f, 0.0f, 8500.0f));
	SetRot(D3DXVECTOR3(-1.57f, 0.0f, 0.0f));
	SetTextureKey("SKY");
	return S_OK;
}

void CSkyBg::Update()
{
	CObject3D::Update();

	m_uPos += 0.00025f;

	SetUV(m_uPos, m_uPos + 1.0f,0.0f,1.0f);
}

CSkyBg * CSkyBg::Create()
{
	CSkyBg* sky = new CSkyBg;

	sky->Init();

	return sky;
}
