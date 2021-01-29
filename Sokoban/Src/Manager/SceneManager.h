
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Difinition.h"
#include "../Singleton.h"

// シーン管理クラス
class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Exec();	// シーンの実行
	void Draw();	// シーンの描画

	void SetNextScene(SceneID next_); // 次のシーン設定


private:
	class SceneBase* create_NextScene();

private:
	class SceneBase* m_pScene;		// 実行中のシーン
	static SceneID   m_NextSceneID;	// 次に作るシーンのID
};

// シングルトンデザインパターン (クラスに置く場合)
//---------------------------------------
#if 0
	//
private:
	// 自分自身のポインタ変数(自分自身の唯一の実体)
	static SceneManager* m_pInstance;

public:
	// 実体を作る関数
	static void CreateInstansce()
	{
		// すでに作られているなら新しく作らないことを保証
		if (m_pInstance == nullptr)
		{
			m_pInstance = new SceneManager();
		}
	}
	// 実体を破壊する関数
	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	// 実体を取得する関数
	static SceneManager* GetInstance()
	{
		return m_pInstance;
	}
	// 実体が存在するか確認する関数
	static bool IsNull()
	{
		return (m_pInstance == nullptr);
	}
};
// static メンバ変数を初期化
SceneManager* SceneManager::m_pInstance = nullptr;
#endif //if 0

#endif // !SCENE_MANAGER_H