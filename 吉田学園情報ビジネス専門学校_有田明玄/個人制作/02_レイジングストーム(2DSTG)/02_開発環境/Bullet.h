//=============================================================================
//
// 2Dオブジェクト
// Author : 有田明玄
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

//インクルード
#include"main.h"
#include"Object2D.h"

class CEnemy;

//マクロ定義
#define BULLET_TEX				(5)			//テクスチャの枚数
#define BULLET_WIDTH_RED		(20.0f)		//赤弾の横幅
#define BULLET_HEIGHT_RED		(70.0f)		//赤弾の縦幅
#define BULLET_WIDTH_BLUE		(20.0f)		//青弾の横幅
#define BULLET_HEIGHT_BLUE		(40.0f)		//青弾の縦幅
#define BULLET_WIDTH_YELLOW		(20.0f)		//黄弾の横幅
#define BULLET_HEIGHT_YELLOW	(70.0f)		//黄弾の縦幅
#define	BULLET_SIZ				(20.0f)		//敵の弾の大きさ
#define BULLET_LIFE				(500)		//弾の寿命
#define BEAM_WIDTH				(120.0f)	//合体ビームの横幅
#define RED_SPEED				(20.0f)		//赤ビームの速度
#define BLUE_SPEED				(10.0f)		//ミサイル速度
#define YELLOW_SPEED			(5.0f)		//ドリル速度
#define ENEMY_SPEED				(6.0f)		//敵の弾速(自機狙い)
#define CANNON_SPEED			(6.0f)		//敵の弾速(固定砲台)
#define RED_DAMAGE				(150)		//赤の威力
#define BLUE_DAMAGE				(125)		//青の威力
#define YELLOW_DAMAGE			(200)		//黄の威力
#define FUSION_DAMAGE			(50)		//合体の威力
#define DEFAULT_HIT				(1)			//デフォルトヒット数
#define YELLOW_HIT				(3)			//黄ドリルのヒット数
#define DEFAULT_NEXTHIT			(1)			//ヒットしてからダメージ判定が復活するまでの時間


//前方宣言
//=============================================================================
// 構造体定義
//=============================================================================
class CBullet : public CObject2D
{
public:
	enum EBULLETTYPE
	{
		BTYPE_REDBEAM = 0,		//赤機体用
		BTYPE_BLUEMSSILE,		//青機体用
		BTYPE_YELLOWDRILL,		//黄機体用
		BTYPE_FUSIONSHOT,		//合体機体用
		ENEMY_BULLET,			//敵
		ENEMY_CANNON01,			//直線1方向
		ENEMY_CANNON02,			//直線2方向
		ENEMY_CANNON03,			//直線3方向
		ENEMY_CANNON04,			//直線4方向
		ENEMY_CANNON06,			//直線6方向
		ENEMY_CANNON07,			//直線7方向
		ENEMY_CANNON08,			//直線8方向
		ENEMY_CANNON09,			//直線9方向
		ENEMY_BEAMCANNON,		//コアキャノンのビーム
		BTYPE_INVALID,			//未使用
		BTYPE_MAX
	};

	CBullet();
	~CBullet()override;
	HRESULT Init(float Width, float Height)override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static HRESULT Load();
	static void Unload();
	static CBullet *Create(D3DXVECTOR3 pos, EBULLETTYPE type);
	HRESULT Hit();
	void Lockon();		//ホーミングのターゲット設定
	void SetHorming();
	void Offscreen();
	static void SetBeam(bool use);
	void FusionBeam();
	static void GetPlayerPos(D3DXVECTOR3 pos);


private:
	//メンバ関数
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLET_TEX];
	D3DXVECTOR3 m_Move;
	int m_nMoveCnt;					//行動制御用
	int m_Target;					//ミサイルのターゲット
	EBULLETTYPE m_eType;			//弾の種類
	static bool m_bUse;				//撃ってるかどうか
	static D3DXVECTOR3 m_playerpos;	//プレイヤーの位置
	bool m_bEnemy;					//敵の弾かどうか
	int m_HitCount;					//残りヒット回数
	int m_NextHItTime;				//ダメージ判定が復活するまでの時間
};
#endif // !_OBJECT_H_



