
#include "DxLib.h"
#include "../Src/Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

const int WindowWidth  = (STAGE_WIDTH * CHIP_WIDTH) * 2;
const int WindowHeight = STAGE_HEIGHT * CHIP_HEIGHT; 
const int ColorBit = 32;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// DXLibrary�������֐�
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WindowWidth, WindowHeight, ColorBit);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(125, 125, 125);
	SetMainWindowText("�������΂�");

	if (DxLib_Init() == -1){ return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	DrawPixel(320, 240, GetColor(255, 0, 0));

	// �Ǘ��N���X�̍쐬
	GameManager::CreateInstansce();
	InputManager::CreateInstansce();
	SceneManager::CreateInstansce();

	while (true)
	{
		if (ProcessMessage() != 0) { break; }

		// ��ʃN���A
		ClearDrawScreen();
		clsDx();

		// ����
		InputManager::GetInstance()->Update();
		SceneManager::GetInstance()->Exec();

		// �`��
		SceneManager::GetInstance()->Draw();

		// ��ʍX�V
		ScreenFlip();
	}

	// �Ǘ��N���X�̌�n��
	SceneManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
