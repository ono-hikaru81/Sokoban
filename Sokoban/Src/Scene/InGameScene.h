
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
	// 開始ジングル
	void step_StartJingle();

	// 入力受付
	void step_Input();

	// クリアジングル
	void step_ClearJingle();

// 倉庫番に関係する関数群
private:
	// ゲームのクリア状態
	bool IsClear() const;
	// 初期状態にリセット
	void Reset();
	// 移動処理
	void Move( DirType dir_ );

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX; // 配列上のx
	int m_PlayerY; // 配列上のy
	int m_CrateMax;

	DirType m_PlayerCurrectDirection;
	GameManager* gameMng = nullptr;

	// 画像ハンドル
	int GroundGraph;
	int WallGraph;
	int TargetGraph;
	int UnsetCrateGraph;
	int SetCrateGraph;
	int ClearGraph;
	int PlayerGraph[PlayerMax];
};

#endif // !INGAME_SCENE_H
