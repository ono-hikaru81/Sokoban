
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	// �������e�̓N���X���ƂɈႤ�̂ŁA
	// �������z�֐��Ƃ��Đ錾���Ă���
	virtual void Exec() = 0;
	virtual void Draw() = 0;

	virtual bool IsEnd() const = 0; // �V�[�����I���������ǂ�����Ԃ�

protected:
	int m_Step;	// �������e���Ǘ�����ϐ�
};

#endif // !SCENE_BASE_H
