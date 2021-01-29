
#ifndef DIFINITION_H
#define DIFINITION_H

//---------------------------------
enum SceneID
{
	SceneID_Title,	// タイトル
	SceneID_InGame,	// インゲーム
	SceneID_Result,	// リザルト


	SceneID_Max,
	SceneID_Invalid // 無効値
};

//---------------------------------

//ステージ情報
const int STAGE_WIDTH  = 11;
const int STAGE_HEIGHT = 13;

// マップチップの縦横サイズ
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;

// オブジェクト種類
//		0	地面
//		1	壁
//		2	プレイヤーの初期位置
//		3	クレート配置場所
//		4	未配置のクレート
//		7	配置済みのクレート
//			(配置場所'3' + 未配置クレート'4' = 7)

enum ObjectType
{
	ObjectType_Ground,			// 0
	ObjectType_Wall,			// 1
	ObjectType_Player,			// 2
	ObjectType_Target,			// 3
	ObjectType_UnsetCrate,		// 4
	ObjectType_SetCrate = 7,	// 7
};

// 移動方向
enum DirType
{
	DirType_Up,		// 上
	DirType_Down,	// 下
	DirType_Left,	// 左
	DirType_Right,	// 右

	// 画像読み込みで使用する
	DirType_Max,
};

#endif // !DIFINITION_H
