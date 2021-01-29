
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../Singleton.h"

// ゲーム全体の管理クラス
class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	// シーン間でやり取りしたいデータの設定、取得関数を適宣追加
	void SetCount(int count_) { m_Count = count_; }
	int GetCount() const { return m_Count; }

private:
	// シーン間でやり取りするデータを保持しておく変数を適宜追加
	int m_Count;
};

#endif // !GAME_MANAGER_H
