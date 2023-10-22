//=================================================
// Content     (ゲームの設定)(camera.h)
// Author     : 有田明玄
//=================================================
#ifndef _CAMERA_GAME_H_		// このマクロ定義がされてなかったら
#define _CAMERA_GAME_H_		// 二重インクルード防止のマクロ定義

#include "Camera.h"

class CCameraGame : public CCamera
{
private:
	static const float SPEED;		// 移動速度
	static const float FACTOR;		// 追従の係数
	static const float ROTSPEED;	// 旋回速度
	static const float ZPOS;		// Z座標
public:
	CCameraGame();
	~CCameraGame();

	//プロトタイプ宣言
	void Init() override;		// 初期化
	void Update() override;		// 更新

	static CCameraGame* Create();	// 生成

private:
};

#endif
