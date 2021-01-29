
#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_INPUT,
	STEP_END
};

ResultScene::ResultScene()
{
	m_Step = STEP_INPUT;
	gameMng = GameManager::GetInstance();
	m_Count = gameMng->GetCount();
}

ResultScene::~ResultScene()
{
	gameMng = nullptr;
}

void ResultScene::Exec()
{
	switch (m_Step)
	{
	case STEP_INPUT:   step_Input();  break;
	default:						  break;
	}

	// @@Dummy �J�ڊm�F�p�̉�����
	/*m_Step++;
	if (m_Step >= 120)
	{
		SceneManager::GetInstance()->SetNextScene(SceneID_Title);
	}*/
}

void ResultScene::Draw()
{
	SetFontSize(32);
	DrawFormatString(200, 200, GetColor(255, 200, 200), "���������菇�� %d", m_Count);
	DrawString(100, 300, "Enter�L-�Ń^�C�g���ɂ��ǂ��", GetColor(255, 200, 200));
	SetFontSize(16);
}

bool ResultScene::IsEnd() const
{
	// @@Dummy �J�ڊm�F�p�̉�����
	return (m_Step == STEP_END);
}

void ResultScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPushed(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_Title);
	}
}
