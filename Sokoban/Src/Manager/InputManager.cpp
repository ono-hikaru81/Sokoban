
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

// �L�[���͍X�V
void InputManager::Update()
{
	for (int i = 0; i < KeyType_Max; i++)
	{
		// ���݂̃L�[�̓��͏�Ԃ��擾
		const bool current = (CheckHitKey(KEY_ASSIGN[i]) == 1);
		// �O��̃L�[���Ɣ�r�����Č��݂̏�Ԃ��X�V
	    m_State[i].pushed = current && !m_State[i].previous;
		// m_State[i].pushed = (current == true) && (m_State[i].previous == false);
		m_State[i].hold = current;
	    m_State[i].released = !current && m_State[i].previous;
		// m_State[i].released = (current == false) && (m_State[i].previous == true);

		// ���݂̒l��previous�֑��
		m_State[i].previous = current;
	}
}

// �L�[�������ꂽ��
bool InputManager::IsPushed(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].pushed;
}

// �L�[����������Ă��邩
bool InputManager::IsHold(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].hold;
}

// �L�[�������ꂽ��
bool InputManager::IsReleased(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].released;
}
