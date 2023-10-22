//**************************************************************************************************
//
// モーション処理(motion.cpp)
// Auther：唐﨑結斗
// Author : Yuda Kaito
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include <stdio.h>
#include <assert.h>
#include "application.h"
#include "motion.h"	
#include "objectX.h"
#include "texture.h"
#include "utility.h"
#include "renderer.h"

#include <fstream>
#include <iostream>
#include <string>

//***************************************************************************
// 定数定義
// Author : Yuda Kaito
//***************************************************************************
const unsigned int CMotion::MOTION_BLEND_FRAM = 5;	// モーションブレンドのフレーム数	

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// Author : Yuda Kaito
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CMotion::CMotion(const char * pFileName)
{
	// パーツ名の初期化
	m_partsFile.clear();

	// モーションの初期化
	m_motion.clear();

	// パーツの初期化
	m_parts.clear();

	// パーツ数の初期化
	m_nMaxParts = 0;

	// 扱うモーション
	m_nNumMotion = 0;

	// モーションを行うか
	m_bMotion = false;

	// モーションブレンド
	m_bMotionBlend = false;

	// モーションの読み込み
	LoodSetMotion(pFileName);
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CMotion::~CMotion()
{
}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : パーツ情報のXファイル読み込み
//=============================================================================
void CMotion::Init()
{
	for (int nCntMotion = 0; nCntMotion < (int)m_motion.size(); nCntMotion++)
	{// カウントのリセット
		CntReset(nCntMotion);
	}
	m_bMotion = true;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : メモリの解放
//=============================================================================
void CMotion::Uninit(void)
{
	m_motion.clear();

	for (int i = 0; i < m_nMaxParts; i++)
	{
		if (m_parts[i] != nullptr)
		{
			m_parts[i] = nullptr;
		}
	}
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : モーションの更新
//=============================================================================
void CMotion::Update()
{
	if (m_bMotionBlend)
	{
		MotionBlend();
	}
	else if (m_bMotion && !m_bMotionBlend)
	{
		PlayMotion();
	}
}

//=============================================================================
// モーションの設定
// Author : 唐﨑結斗
// 概要 : モーションの初期位置に設定
//=============================================================================
void CMotion::SetMotion(const unsigned int nCntMotionSet)
{
	CMotion::MyMotion& motion = m_motion[nCntMotionSet];

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// 変数宣言
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
		D3DXVECTOR3 posOrigin = m_parts[nCntParts]->GetPosDefault();	// 元の位置
		D3DXVECTOR3 rotOrigin = m_parts[nCntParts]->GetRotDefault();	// 元の向き

		// 位置の設定
		pos = (posOrigin + motion.pKeySet[motion.nCntKeySet].pKey[nCntParts].pos);

		//	向きの設定
		rot = (rotOrigin + motion.pKeySet[motion.nCntKeySet].pKey[nCntParts].rot);

		// 角度の正規化
		rot.x = NormalizeAngle(rot.x);
		rot.y = NormalizeAngle(rot.y);
		rot.z = NormalizeAngle(rot.z);

		// 情報の更新
		m_parts[nCntParts]->SetPos(pos);
		m_parts[nCntParts]->SetRot(rot);
	}
}

//=============================================================================
// パーツの設定
// Author : 唐﨑結斗
// 概要 : 行列を利用して、パーツの親子関係と描画設定を行う
//=============================================================================
void CMotion::SetParts(D3DXMATRIX /*mtxWorld*/)
{
	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{// モデルの描画
		if (m_parts[nCntParts]->GetParent() != nullptr)
		{
			m_parts[nCntParts]->Draw();
		}
		else
		{
//			m_parts[nCntParts]->Draw(mtxWorld);
		}
	}

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::getInstance()->GetRenderer()->GetDevice();

	// 新規深度値とZバッファの深度値が同じ値ならテスト成功にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// モデルの切り替え
// Author : Yuda Kaito
// 概要 : 使用しているモデルの切り替え
//=============================================================================
void CMotion::ChangeModel(int index, std::string path)
{
	assert(!(index < 0 || index >= m_parts.size()));

	m_parts[index]->BindModel(path);
}

//=============================================================================
// モーションの再生
// Author : 唐﨑結斗
// 概要 : 目的の位置まで特定のフレーム数で到着する処理をパーツごとに行う
//=============================================================================
void CMotion::PlayMotion()
{
	CMotion::MyMotion& motion = m_motion[m_nNumMotion];	// 現在モーション

	MyKeySet& nowKeySet = motion.pKeySet[motion.nCntKeySet];

	for (int nCntParts = 0; nCntParts < (int)m_parts.size(); nCntParts++)
	{
		if (m_parts.size() <= nCntParts)
		{
			return;
		}

		if (nowKeySet.pKey.size() <= nCntParts)
		{
			return;
		}

		// 変数宣言
		D3DXVECTOR3 pos = m_parts[nCntParts]->GetPos();			// 位置
		D3DXVECTOR3 rot = m_parts[nCntParts]->GetRot();			// 向き
		D3DXVECTOR3 posDest = m_parts[nCntParts]->GetPosDest();	// 目的の位置
		D3DXVECTOR3 rotDest = m_parts[nCntParts]->GetRotDest();	// 目的の向き

		if (motion.nCntFrame == 0)
		{// フレームカウントが0の時
			// 変数宣言
			D3DXVECTOR3 posOrigin = m_parts[nCntParts]->GetPosDefault();		// 元の位置
			D3DXVECTOR3 rotOrigin = m_parts[nCntParts]->GetRotDefault();		// 元の向き

			// 目的の位置と向きの算出
			posDest = (posOrigin + nowKeySet.pKey[nCntParts].pos) - pos;
			rotDest = (rotOrigin + nowKeySet.pKey[nCntParts].rot) - rot;

			// 角度の正規化
			rotDest.x = NormalizeAngle(rotDest.x);
			rotDest.y = NormalizeAngle(rotDest.y);
			rotDest.z = NormalizeAngle(rotDest.z);

			// 情報の更新
			m_parts[nCntParts]->SetPosDest(posDest);
			m_parts[nCntParts]->SetRotDest(rotDest);
		}

		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(nowKeySet.nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(nowKeySet.nFrame));

		// 位置の加算
		pos += addPos;

		//	向きの加算
		rot += addRot;

		// 角度の正規化
		rot.x = NormalizeAngle(rot.x);
		rot.y = NormalizeAngle(rot.y);
		rot.z = NormalizeAngle(rot.z);

		// 情報の更新
		m_parts[nCntParts]->SetPos(pos);
		m_parts[nCntParts]->SetRot(rot);
	}

	// フレームカウントの加算
	motion.nCntFrame++;

	if (motion.nCntFrame >= nowKeySet.nFrame)
	{// フレームカウントが指定のフレーム数を超えた場合
	 // フレーム数の初期化
		motion.nCntFrame = 0;

		// 再生中のキー番号数の加算
		motion.nCntKeySet++;

		if (motion.nCntKeySet >= motion.nNumKey && motion.bLoop)
		{// 再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している
			// 再生中のキー数カウントを初期化
			motion.nCntKeySet = 0;

		}
		else if (motion.nCntKeySet >= motion.nNumKey)
		{
			motion.nCntKeySet = 0;
			m_bMotion = false;
		}
	}
}

//=============================================================================
// モーションブレンド
// Author : 唐﨑結斗
// 概要 : モーションとモーションのつなぎ目を調整する
// 返り値 : モーションブレンド使用の可否
//=============================================================================
void CMotion::MotionBlend()
{
	CDebugProc::Print("BlendNow\n");
	CMotion::MyMotion& motion = m_motion[m_nNumMotion];

	for (int nCntParts = 0; nCntParts < (int)m_parts.size(); nCntParts++)
	{
		if (motion.pKeySet[motion.nCntKeySet].pKey.size() <= nCntParts)
		{
			return;
		}

		// 変数宣言
		D3DXVECTOR3 pos = m_parts[nCntParts]->GetPos();			// 位置
		D3DXVECTOR3 rot = m_parts[nCntParts]->GetRot();			// 向き
		D3DXVECTOR3 posDest = m_parts[nCntParts]->GetPosDest();	// 目的の位置
		D3DXVECTOR3 rotDest = m_parts[nCntParts]->GetRotDest();	// 目的の向き

		if (motion.nCntFrame == 0)
		{// フレームカウントが0の時
			// 変数宣言
			D3DXVECTOR3 posOrigin = m_parts[nCntParts]->GetPosDefault();		// 元の位置
			D3DXVECTOR3 rotOrigin = m_parts[nCntParts]->GetRotDefault();		// 元の向き

			// 目的の位置と向きの算出
			CMotion::MyKey myKey = motion.pKeySet[motion.nCntKeySet].pKey[nCntParts];
			posDest = posOrigin + myKey.pos - pos;
			rotDest = rotOrigin + myKey.rot - rot;

			// 角度の正規化
			rotDest.x = NormalizeAngle(rotDest.x);
			rotDest.y = NormalizeAngle(rotDest.y);
			rotDest.z = NormalizeAngle(rotDest.z);

			// 情報の更新
			m_parts[nCntParts]->SetPosDest(posDest);
			m_parts[nCntParts]->SetRotDest(rotDest);
		}

		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(MOTION_BLEND_FRAM));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(MOTION_BLEND_FRAM));

		// 位置の加算
		pos += addPos;

		//	向きの加算
		rot += addRot;

		// 角度の正規化
		rot.x = NormalizeAngle(rot.x);
		rot.y = NormalizeAngle(rot.y);
		rot.z = NormalizeAngle(rot.z);

		// 情報の更新
		m_parts[nCntParts]->SetPos(pos);
		m_parts[nCntParts]->SetRot(rot);
	}

	// フレームカウントの加算
	motion.nCntFrame++;

	if (motion.nCntFrame >= MOTION_BLEND_FRAM)
	{// フレームカウントが指定のフレーム数を超えた場合

		motion.nCntFrame = 0;	// フレーム数の初期化
		motion.nCntKeySet++;	// 再生中のキー番号数の加算

		m_bMotionBlend = false;
	}
}

//=============================================================================
// パーツとモーションの読み込み
// Author : 唐﨑結斗
// Author : 有田明玄
// Author : Yuda Kaito
// 概要 : パーツとモーションの読み込み、初期化を呼び出す
//=============================================================================
void CMotion::LoodSetMotion(const char *pFileName)
{
	// ファイルを開く
	std::ifstream fileBasicData;
	std::string filename = pFileName;
	fileBasicData.open(filename, std::ios::in);

	char tag[2048];
	std::string readLineBasicData;

	int	modelnumber = 0;		// モデルの番号
	int Idx = 0;

	// 読み込んだ文字列との一致を調べる
	auto StringMatched = [&readLineBasicData](std::string b)
	{
		return readLineBasicData.find(b) != std::string::npos;
	};

	while (std::getline(fileBasicData, readLineBasicData))
	{
		// "END_SCRIPT" なら繰り返しをここで終了する
		if (StringMatched("END_SCRIPT"))
		{
			break;
		}

		// "SCRIPT" ではないなら繰り返しをここでもう一度最初から繰り返す
		if (!StringMatched("SCRIPT"))
		{
			continue;
		}

		while (std::getline(fileBasicData, readLineBasicData))
		{
			//モデルの初期設定
			if (StringMatched("END_SCRIPT"))
			{
				break;
			}
			else if (StringMatched("NUM_MODEL"))
			{
				int num = 0;
				sscanf(readLineBasicData.c_str(), "%s = %d", tag, &num);	//読み込んだ文字ごとに設定する
				m_parts.resize(num);
			}
			else if (StringMatched("MODEL_FILENAME"))
			{
				char pass[1024];

				sscanf(readLineBasicData.c_str(), "%s = %s", tag, pass);	//モデルのパスの設定

				std::string modelKey = "MODEL" + std::to_string(modelnumber);
				m_parts[modelnumber] = CObjectX::Create();
				m_parts[modelnumber]->BindModel(CObjectXOriginalList::GetInstance()->Load(modelKey, pass));
				modelnumber++;
			}
			else if (StringMatched("CHARACTERSET"))
			{//初期位置の設定

				//キャラクターの設定
				while (std::getline(fileBasicData, readLineBasicData))//一行読み込み
				{
					// 繰り返し終了条件
					if (StringMatched("END_CHARACTERSET"))
					{
						break;
					}

					// "PARTSSET" ではないなら繰り返しをここでもう一度最初から繰り返す
					if (StringMatched("PARTSSET"))
					{
						continue;
					}

					while (std::getline(fileBasicData, readLineBasicData))	//読み込みループ //一行読み込み
					{//パーツの設定	
						if (StringMatched("END_PARTSSET"))
						{//パーツの設定終了
							Idx++;
							break;
						}
						else if (StringMatched("INDEX"))
						{//インデックスの設定
							sscanf(readLineBasicData.c_str(), "%s = %d", tag, &Idx);	// モデルのパスの設定
						}
						else if (StringMatched("PARENT"))
						{//親モデルの設定
							int Parent;
							sscanf(readLineBasicData.c_str(), "%s = %d", tag, &Parent);	// モデルのパスの設定

							if (Parent >= 0 && Parent < (int)m_parts.size())
							{
								m_parts[Idx]->SetParent(m_parts[Parent]);
							}
						}
						else if (StringMatched("POS"))
						{//位置
							D3DXVECTOR3 pos;
							sscanf(readLineBasicData.c_str(), "%s = %f%f%f", tag, &pos.x, &pos.y, &pos.z);	//座標の取得
							m_parts[Idx]->SetPos(pos);
							m_parts[Idx]->SetPosDefault(pos);
						}
						else if (StringMatched("ROT"))
						{//向き
							D3DXVECTOR3 rot;
							sscanf(readLineBasicData.c_str(), "%s = %f%f%f", tag, &rot.x, &rot.y, &rot.z);
							m_parts[Idx]->SetRot(rot);
							m_parts[Idx]->SetRotDefault(rot);
						}
					}
				}
			}
			else if (StringMatched("MOTIONSET"))
			{//モーションの設定
				while (std::getline(fileBasicData, readLineBasicData))	//読み込み用ループ
				{
					if (StringMatched("END_MOTIONSET"))
					{
						break;
					}
					else if (StringMatched("MOTION"))
					{
						std::ifstream fileMotionData;
						char motionFilePass[1024];
						sscanf(readLineBasicData.c_str(), "%s = %s", tag, motionFilePass);	//ファイル読み込み
						fileMotionData.open(motionFilePass, std::ios::in);

						while (std::getline(fileMotionData, readLineBasicData))	//読み込み用ループ
						{
							if (!StringMatched("MOTIONSET"))
							{
								continue;
							}

							MyMotion motion;
							while (std::getline(fileMotionData, readLineBasicData))	//読み込み用ループ
							{
								if (StringMatched("END_MOTIONSET"))
								{
									m_motion.push_back(motion);
									break;
								}

								if (StringMatched("NUM_KEY"))
								{
									sscanf(readLineBasicData.c_str(), "%s = %d", tag, &motion.nNumKey);	//キーの総数
								}
								else if (StringMatched("LOOP"))
								{//ループするかしないか
									int loop = 0;
									sscanf(readLineBasicData.c_str(), "%s = %d", tag, &loop);	//ループするかどうか

									motion.bLoop = loop == 1;
								}
								else if (StringMatched("KEYSET"))
								{
									MyKeySet myKeySet;
									while (std::getline(fileMotionData, readLineBasicData))
									{
										//keyはモデルのキーの番号
										if (StringMatched("END_KEYSET"))
										{
											motion.pKeySet.push_back(myKeySet);
											break;
										}
										else if (StringMatched("FRAME"))
										{//キーの再生時間の設定
											sscanf(readLineBasicData.c_str(), "%s = %d", tag, &myKeySet.nFrame);	//再生時間の設定
										}
										else if (StringMatched("KEY"))
										{//キー設定
											MyKey myKey;
											while (std::getline(fileMotionData, readLineBasicData))
											{
												if (StringMatched("END_KEY"))
												{
													myKeySet.pKey.push_back(myKey);
													break;
												}
												else if (StringMatched("POS"))
												{
													sscanf(readLineBasicData.c_str(), "%s = %f%f%f", tag, &myKey.pos.x, &myKey.pos.y, &myKey.pos.z);
												}
												else if (StringMatched("ROT"))
												{
													sscanf(readLineBasicData.c_str(), "%s = %f%f%f", tag, &myKey.rot.x, &myKey.rot.y, &myKey.rot.z);
												}
											}
										}
									}
								}
							}
							break;	//読み込みが終わったらループ脱出
						}
					}
				}
			}
			else if (StringMatched("#"))
			{
				continue;
			}
		}
	}

	// 初期化
	Init();
}

//=============================================================================
// パーツの位置をもとの位置に戻す
// Author : 唐﨑結斗
// 概要 : パーツの位置をもとの位置に戻す
//=============================================================================
void CMotion::SetPartsOrigin()
{
	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// 位置の設定
		m_parts[nCntParts]->SetPos(m_parts[nCntParts]->GetPosDefault());

		//	向きの設定
		m_parts[nCntParts]->SetRot(m_parts[nCntParts]->GetRotDefault());
	}
}

//=============================================================================
// カウントのリセット
// Author : 唐﨑結斗
// 概要 : カウントのリセット
//=============================================================================
void CMotion::CntReset(const int nNumMotionOld)
{
	m_motion[nNumMotionOld].nCntFrame = 0;
	m_motion[nNumMotionOld].nCntKeySet = 0;
}

//=============================================================================
// モーション番号の設定
// Author : 唐﨑結斗
// 概要 : モーションの番号の設定
//=============================================================================
void CMotion::SetNumMotion(const unsigned int nNumMotion)
{
	// モーションカウントのリセット
	CntReset(m_nNumMotion);

	// モーション番号の設定
	m_nNumMotion = nNumMotion;

	// モーションブレンドを行う
	m_bMotionBlend = true;
	m_bMotion = true;
}

void CMotion::SetSizeMag(const D3DXVECTOR3 & size)
{
	int partsSize = m_parts.size();
	for (int i = 0; i < partsSize; i++)
	{
		m_parts[i]->SetSizeMag(size);
	}
}
