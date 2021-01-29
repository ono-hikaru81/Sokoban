
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

	// @@Dummy 遷移確認用の仮処理
	/*m_Step++;
	if (m_Step >= 120)
	{
		SceneManager::GetInstance()->SetNextScene(SceneID_Title);
	}*/
}

void ResultScene::Draw()
{
	SetFontSize(32);
	DrawFormatString(200, 200, GetColor(255, 200, 200), "かかった手順は %d", m_Count);
	DrawString(100, 300, "Enterキ-でタイトルにもどるよ", GetColor(255, 200, 200));
	SetFontSize(16);
}

bool ResultScene::IsEnd() const
{
	// @@Dummy 遷移確認用の仮処理
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
