
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../KeyDifinition.h"
#include "../Singleton.h"

// ���͊Ǘ��N���X
class InputManager : public Singleton<InputManager>
{
private:
	struct KeyState
	{
		bool previous;	// �O��`�F�b�N���̃t���O���

		bool pushed;	// �����ꂽ�u��
		bool hold;		// ������Ă�����
		bool released;	// �����ꂽ�u��

		KeyState()
			: previous(false)
			, pushed(false)
			, hold(false)
			, released(false)
		{}
	};

public:
	InputManager();
	~InputManager();

	// �L�[���͍X�V
	void Update();

	// �L�[�������ꂽ��
	bool IsPushed( KeyType key ) const;

	// �L�[����������Ă��邩
	bool IsHold( KeyType key ) const;

	// �L�[�������ꂽ��
	bool IsReleased( KeyType key ) const;

private:
	KeyState m_State[KeyType_Max];
};

#endif // !INPUT_MANAGER_H
