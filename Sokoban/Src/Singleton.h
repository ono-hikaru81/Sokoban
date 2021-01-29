
#ifndef SINGLETON_H
#define SINGLETON_H

// シングルトンデザインパターン
template< class T >
class Singleton
{
protected:
	Singleton(){ }				// コンストラクタ抑制
	virtual ~Singleton(){ }		// デストラクタ抑制

private:
	// 自分自身のポインタ変数(自分自身の唯一の実体)
	static T* m_pInstance;

public:
	// 実体を作る関数
	static void CreateInstansce()
	{
		// すでに作られているなら新しく作らないことを保証
		if ( m_pInstance == nullptr )
		{
			m_pInstance = new T();
		}
	}
	// 実体を破壊する関数
	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	// 実体を取得する関数
	static T* GetInstance()
	{
		return m_pInstance;
	}
	// 実体が存在するか確認する関数
	static bool IsNull()
	{
		return (m_pInstance == nullptr);
	}
};
// staticなメンバ変数を初期化(コンストラクタではやらない)
template< class T >
T* Singleton<T>::m_pInstance = nullptr;

#endif // !SINGLETON_H

