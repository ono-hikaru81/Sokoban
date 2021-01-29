
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../KeyDifinition.h"
#include "../Singleton.h"

// 入力管理クラス
class InputManager : public Singleton<InputManager>
{
private:
	struct KeyState
	{
		bool previous;	// 前回チェック時のフラグ状態

		bool pushed;	// 押された瞬間
		bool hold;		// 押されている状態
		bool released;	// 離された瞬間

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

	// キー入力更新
	void Update();

	// キーが押されたか
	bool IsPushed( KeyType key ) const;

	// キーが押下されているか
	bool IsHold( KeyType key ) const;

	// キーが離されたか
	bool IsReleased( KeyType key ) const;

private:
	KeyState m_State[KeyType_Max];
};

#endif // !INPUT_MANAGER_H
