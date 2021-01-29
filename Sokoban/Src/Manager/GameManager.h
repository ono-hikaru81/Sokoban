
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../Singleton.h"

// �Q�[���S�̂̊Ǘ��N���X
class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	// �V�[���Ԃł���肵�����f�[�^�̐ݒ�A�擾�֐���K��ǉ�
	void SetCount(int count_) { m_Count = count_; }
	int GetCount() const { return m_Count; }

private:
	// �V�[���Ԃł���肷��f�[�^��ێ����Ă����ϐ���K�X�ǉ�
	int m_Count;
};

#endif // !GAME_MANAGER_H
