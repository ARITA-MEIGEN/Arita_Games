#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include"main.h"

class CObject2D;

#define NUM_TEXTR (2)	//âÊëúÇÃñáêî

class CTutorial
{
public:
	CTutorial();
	~CTutorial();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CTutorial::Load();
	void CTutorial::Unload();
private:
	CObject2D*m_apObject2D[NUM_TEXTR];
	static LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTR];
	float m_afAlpha[NUM_TEXTR];
	bool m_Next;
};

#endif
