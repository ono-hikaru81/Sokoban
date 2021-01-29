
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	// 処理内容はクラスごとに違うので、
	// 純粋仮想関数として宣言しておく
	virtual void Exec() = 0;
	virtual void Draw() = 0;

	virtual bool IsEnd() const = 0; // シーンが終了したかどうかを返す

protected:
	int m_Step;	// 処理内容を管理する変数
};

#endif // !SCENE_BASE_H
