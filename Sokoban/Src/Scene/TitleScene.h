
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "SceneBase.h"

class TitleScene:public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Exec();
	virtual void Draw();

	virtual bool IsEnd() const;

private:
	// タイトルロゴ入場
	void step_LogoIn();

	// 入力受付
	void step_Input();
};


#endif // !TITLE_SCENE_H
