
#include "DxLib.h"
#include "../Src/Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

const int WindowWidth  = (STAGE_WIDTH * CHIP_WIDTH) * 2;
const int WindowHeight = STAGE_HEIGHT * CHIP_HEIGHT; 
const int ColorBit = 32;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// DXLibrary初期化関数
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WindowWidth, WindowHeight, ColorBit);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(125, 125, 125);
	SetMainWindowText("そうこばん");

	if (DxLib_Init() == -1){ return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	DrawPixel(320, 240, GetColor(255, 0, 0));

	// 管理クラスの作成
	GameManager::CreateInstansce();
	InputManager::CreateInstansce();
	SceneManager::CreateInstansce();

	while (true)
	{
		if (ProcessMessage() != 0) { break; }

		// 画面クリア
		ClearDrawScreen();
		clsDx();

		// 処理
		InputManager::GetInstance()->Update();
		SceneManager::GetInstance()->Exec();

		// 描画
		SceneManager::GetInstance()->Draw();

		// 画面更新
		ScreenFlip();
	}

	// 管理クラスの後始末
	SceneManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
