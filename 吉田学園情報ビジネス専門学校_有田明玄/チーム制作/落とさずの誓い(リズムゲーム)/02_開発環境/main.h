//**************************************************
// 
// main.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MAIN_H_	//このマクロ定義がされてなかったら
#define _MAIN_H_	//２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
#ifdef _DEBUG
//--------------------------------------------------
// FPS取得
//--------------------------------------------------
int GetFPS();
#endif // _DEBUG

#endif // !_MAIN_H_
