//=================================================
// Content     (ゲームの設定)(main.cpp)
// Author     : 有田明玄
// Since      : (作成日2021/07/06)
//=================================================
#include"main.h"
#include"block.h"
#include"input.h"
#include"playereffect.h"
#include"player.h"
#include"mapload.h"
#include"game.h"
#include"result.h"
#include"title.h"
#include"fade.h"
#include"sound.h"
#include"ranking.h"
#include"tutorial.h"

//グローバル変数
LPDIRECT3D9		g_pD3D = NULL;					//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;						//現在のモード
LPD3DXFONT g_pFont = NULL;						//フォントへのポイント
int g_nCountFPS = 0;							//FPSカウンタ
//=================
//メイン関数
//=================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdshow)
{
	DWORD dwCurrentTime;					//現在時刻
	DWORD dwExecLastTime;					//最後に処理した時刻
	DWORD dwFrameCount;						//フレームカウント
	DWORD dwFPSLastTime;					//最後にFPSを計測した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウプロシージャ
		0,
		0,
		hInstance,							//インスタンスハンドル(識別子)
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//ファイルのアイコン
	};
	HWND hWnd;		//ウィンドウハンドル(識別子)	
	MSG msg;	    //メッセージを格納する変数
	RECT rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_CLASSNAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上X座標
		CW_USEDEFAULT,				//ウィンドウの左上Y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウのＩＤ
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{//初期化処理に失敗した場合
		return-1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;							//初期化する

	dwExecLastTime = timeGetTime();				//現在時刻を取得(保存)

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdshow);					//ウィンドウの表示状態を設定

	UpdateWindow(hWnd);							//クライアント領域を更新

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受けとったらメッセージループを抜ける
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);				//仮想キーメッセージを文字メッセージへ変換

				DispatchMessage(&msg);				//ウィンドウプロシージャへメッセージを送出
			}

		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();			//現在時刻取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//FPSを測定した時刻を保存

				dwFrameCount = 0;					//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻(現在時刻)を保存

				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;						//フレームカウントを加算
			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//===================================
//ウィンドウプロシージャ
//===================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:		//ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:		//escキー入力された
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を返す
}
//==============================
//初期化処理
//==============================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理と頂点処理をソフトウェアで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//ポリゴンの大きさに併せてきれいにテクスチャをはる
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャ座標Uが1.0を超えた場合繰り返すかどうかを決める
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//テクスチャ座標Vが1.0を超えた場合繰り返すかどうかを決める

	//テクスチャステージステートの設定	下記の三行で1セット
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	//OPはオペレーションの意 ポリゴンとテクスチャの色を混ぜる
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//テクスチャのアルファ値を参照する
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//ポリゴンのアルファ値を参照する

	//デバッグ表示用フォントの生成														
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);


//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	InitJoypad();
	
	//サウンドの初期化処理
	InitSound(hWnd);

	//ランキングの初期化処理
	InitRanking();

	//各種オブジェクトの初期化処理
	InitFade(g_mode);

	return S_OK;
}
//==================================
//終了処理
//==================================
void Uninit(void)
{
//各オブジェクトの終了処理
	//タイトル画面の終了処理
	UninitTitle();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//チュートリアル画面
	UninitTutorial();

	//フェードの終了処理
	UninitFade();

	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//ランキングの終了処理
	UninitRanking();

	//サウンドの終了処理
	UninitSound();

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}
	//Direct3Dデバイスの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;

	}
}
//===========================
//更新処理
//===========================
void Update(void)
{
//各オブジェクトの更新処理
	UpdateKeyboard();		//キーボードの更新処理
	Updatejoypad();			//ジョイパッドの更新処理
						
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UpdateTitle();
		break;

	case MODE_TUTOLIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:		//ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT:	//リザルト画面
		UpdateResult();
		break;

	case MODE_RANKING:	//ランキング画面
		UpdateRanking();
		break;
	}
	//フェードの更新処理
	UpdateFade();
}
//=================================
//描画処理
//=================================
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//各種オブジェクトの描画処理
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;

		case MODE_TUTOLIAL:	//チュートリアル画面
			DrawTutorial();
			break;

		case MODE_GAME:		//ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT:	//リザルト画面
			DrawResult();
			break;

		case MODE_RANKING:	//ランキング画面
			DrawRanking();	
			break;
		}
		//フェードの描画処理
		DrawFade();

#ifdef  _DEBUG
		//FPSの表示
		DrawFPS();
#endif //  _DEBUG
		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//======================================================
//モードの設定
//======================================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UninitTitle();
		break;

	case MODE_TUTOLIAL:	//チュートリアル画面
		UninitTutorial();
		break;

	case MODE_GAME:		//ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:	//リザルト画面
		UninitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		//UninitRanking();
		break;
	}

	g_mode = mode;	//現在の画面(モード)を切り替える

	StopSound();

	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:	//タイトル画面
		InitTitle();
		break;

	case MODE_TUTOLIAL:	//チュートリアル画面
		InitTutorial();
		break;

	case MODE_GAME:		//ゲーム画面
		InitGame();
		break;

	case MODE_RESULT:	//リザルト画面
		InitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		ResetRanking();	
		break;
	}
}
//======================================================
//デバイスの取得
//======================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//======================================================
//FPSの表示
//======================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0],"FPS:%3d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}	