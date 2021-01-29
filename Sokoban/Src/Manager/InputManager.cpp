
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

// キー入力更新
void InputManager::Update()
{
	for (int i = 0; i < KeyType_Max; i++)
	{
		// 現在のキーの入力状態を取得
		const bool current = (CheckHitKey(KEY_ASSIGN[i]) == 1);
		// 前回のキー情報と比較をして現在の状態を更新
	    m_State[i].pushed = current && !m_State[i].previous;
		// m_State[i].pushed = (current == true) && (m_State[i].previous == false);
		m_State[i].hold = current;
	    m_State[i].released = !current && m_State[i].previous;
		// m_State[i].released = (current == false) && (m_State[i].previous == true);

		// 現在の値をpreviousへ代入
		m_State[i].previous = current;
	}
}

// キーが押されたか
bool InputManager::IsPushed(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].pushed;
}

// キーが押下されているか
bool InputManager::IsHold(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].hold;
}

// キーが離されたか
bool InputManager::IsReleased(KeyType key) const
{
	if ( key == KeyType_Max ) { return false; }
	return m_State[key].released;
}
