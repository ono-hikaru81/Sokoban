
#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "SceneBase.h"
#include "InGameScene.h"
#include "../Manager/GameManager.h"

class ResultScene :public SceneBase
{
public:
	ResultScene();
	~ResultScene();

	void Exec();
	void Draw();

	virtual bool IsEnd() const;

private:
	void step_Input();

private:
	GameManager* gameMng = nullptr;
	int m_Count;
};

#endif // !RESULT_SCENE_H

