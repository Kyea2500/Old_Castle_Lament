#include "DxLib.h"
#include"Scene/SceneManager/SceneManager.h"
#include"Scene/SceneClear/SceneClear.h"
#include"GameProcess/Game.h"
#include"resource.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// フルスクリーンではなく、ウィンドウモードで開くようにする
	ChangeWindowMode(Game::kDefaultWindowMode);

	SetWindowText(L"古城のラメン");
	SetWindowIconID(IDI_ICON3);
	
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// タイトルの変更
	
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	/*SceneGameClear* pScene = new SceneGameClear();*/
	SceneManager* pScene = new SceneManager();
	pScene->Init();

	//Player* m_player = new Player();	//コンストラクタに入る
	//m_player->Init();				//初期化処理に入る
	//Boss* m_boss = new Boss();
	//m_boss->Init();


	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// ループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面をクリアに
		ClearDrawScreen();

		// ここにゲームの処理を書く
		pScene->Update();
		pScene->Draw();
		
		//m_player->Update();//更新処理に入る
		//m_player->Draw();	//描画処理に入る

		//m_boss->Update();
		//m_boss->Draw();


		// 画面の切り替わりを待つ必要がある
		ScreenFlip();
		//FPS(Frame Per Second)60に固定

		// escキーで終了(いったん終了)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}

	}

	//m_player->End();//解放処理に入る

	//m_player = nullptr; //ポインタを無効値
	//delete(m_player);	//デストラクタが呼ばれる

	//m_boss = nullptr;
	//delete(m_boss);
	pScene->End();

	pScene = nullptr;
	delete(pScene);

	DxLib_End();		// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}