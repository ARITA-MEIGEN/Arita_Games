//=============================================================================
//
// オブジェクト
// Author : 有田明玄
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//インクルード
#include "main.h"
#include "Application.h"
#include "Mode.h"
#include <vector>

//前方宣言
class CObject2D;
class CObject3D;
class CCamera;
class CLight;

class CTutorial : public CMode
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:
	CObject2D* m_pBg;
	std::vector<CObject3D*> m_tutorialBg;

	CCamera* m_camera;
	CLight* m_light;

	int m_count;
};

#endif


