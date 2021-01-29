
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_LOGO_IN,	// ロゴ入力待ち
	STEP_INPUT,		// 入力待ち
	STEP_END		// シーン終了
};

TitleScene::TitleScene()
{
	m_Step = STEP_LOGO_IN;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Exec()
{
	switch ( m_Step )
	{
	case STEP_LOGO_IN: step_LogoIn(); break;
	case STEP_INPUT:   step_Input();  break;
	default:						  break;
	}
	// @@Dummy 遷移確認用の仮処理
	/*m_Step++;
	if ( m_Step >= 120 )
	{
		SceneManager::SetNextScene( SceneID_InGame );
	}*/
}

void TitleScene::Draw()
{
	SetFontSize(96);
	DrawString(120, 120, "そうこばん", GetColor(255, 240, 255));
	SetFontSize(16);

	DrawString(350,300, "Enterキーをおしてね", GetColor(250,250,220));
}

bool TitleScene::IsEnd() const
{
	// @@Dummy 遷移確認用の仮処理
	return ( m_Step == STEP_END );
}

// ロゴ入場
void TitleScene::step_LogoIn()
{
	m_Step = STEP_INPUT;
}

// 入力受付
void TitleScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPushed(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_InGame);
	}
}
