
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
	// �^�C�g�����S����
	void step_LogoIn();

	// ���͎�t
	void step_Input();
};


#endif // !TITLE_SCENE_H
