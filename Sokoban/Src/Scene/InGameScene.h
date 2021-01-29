
#ifndef INGAME_SCENE_H
#define INGAME_SCENE_H

#include "SceneBase.h"
#include "../Difinition.h"
#include "../Manager/GameManager.h"

const int PlayerMax = 4;

class InGameScene:public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Exec();
	virtual void Draw();

	virtual bool IsEnd() const;

	int m_Count = 0;

private:
	// �J�n�W���O��
	void step_StartJingle();

	// ���͎�t
	void step_Input();

	// �N���A�W���O��
	void step_ClearJingle();

// �q�ɔԂɊ֌W����֐��Q
private:
	// �Q�[���̃N���A���
	bool IsClear() const;
	// ������ԂɃ��Z�b�g
	void Reset();
	// �ړ�����
	void Move( DirType dir_ );

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX; // �z����x
	int m_PlayerY; // �z����y
	int m_CrateMax;

	DirType m_PlayerCurrectDirection;
	GameManager* gameMng = nullptr;

	// �摜�n���h��
	int GroundGraph;
	int WallGraph;
	int TargetGraph;
	int UnsetCrateGraph;
	int SetCrateGraph;
	int ClearGraph;
	int PlayerGraph[PlayerMax];
};

#endif // !INGAME_SCENE_H
