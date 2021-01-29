
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Difinition.h"
#include "../Singleton.h"

// �V�[���Ǘ��N���X
class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Exec();	// �V�[���̎��s
	void Draw();	// �V�[���̕`��

	void SetNextScene(SceneID next_); // ���̃V�[���ݒ�


private:
	class SceneBase* create_NextScene();

private:
	class SceneBase* m_pScene;		// ���s���̃V�[��
	static SceneID   m_NextSceneID;	// ���ɍ��V�[����ID
};

// �V���O���g���f�U�C���p�^�[�� (�N���X�ɒu���ꍇ)
//---------------------------------------
#if 0
	//
private:
	// �������g�̃|�C���^�ϐ�(�������g�̗B��̎���)
	static SceneManager* m_pInstance;

public:
	// ���̂����֐�
	static void CreateInstansce()
	{
		// ���łɍ���Ă���Ȃ�V�������Ȃ����Ƃ�ۏ�
		if (m_pInstance == nullptr)
		{
			m_pInstance = new SceneManager();
		}
	}
	// ���̂�j�󂷂�֐�
	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	// ���̂��擾����֐�
	static SceneManager* GetInstance()
	{
		return m_pInstance;
	}
	// ���̂����݂��邩�m�F����֐�
	static bool IsNull()
	{
		return (m_pInstance == nullptr);
	}
};
// static �����o�ϐ���������
SceneManager* SceneManager::m_pInstance = nullptr;
#endif //if 0

#endif // !SCENE_MANAGER_H