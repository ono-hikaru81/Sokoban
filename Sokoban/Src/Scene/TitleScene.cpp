
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_LOGO_IN,	// ���S���͑҂�
	STEP_INPUT,		// ���͑҂�
	STEP_END		// �V�[���I��
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
	// @@Dummy �J�ڊm�F�p�̉�����
	/*m_Step++;
	if ( m_Step >= 120 )
	{
		SceneManager::SetNextScene( SceneID_InGame );
	}*/
}

void TitleScene::Draw()
{
	SetFontSize(96);
	DrawString(120, 120, "�������΂�", GetColor(255, 240, 255));
	SetFontSize(16);

	DrawString(350,300, "Enter�L�[�������Ă�", GetColor(250,250,220));
}

bool TitleScene::IsEnd() const
{
	// @@Dummy �J�ڊm�F�p�̉�����
	return ( m_Step == STEP_END );
}

// ���S����
void TitleScene::step_LogoIn()
{
	m_Step = STEP_INPUT;
}

// ���͎�t
void TitleScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPushed(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_InGame);
	}
}
