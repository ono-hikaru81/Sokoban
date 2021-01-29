
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_START_JINGLE,
	STEP_INPUT,		// 入力待ち
	STEP_CREAR_JINGLE,
	STEP_END		// シーン終了
};

// 倉庫番のサンプルステージ
const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH]
{
	1,1,1,1,1,1,1,1,1,1,1,
	1,3,1,0,0,3,0,1,0,3,1,
	1,0,1,0,1,0,0,1,0,0,1,
	1,0,1,0,0,0,0,0,1,0,1,
	1,0,1,1,0,0,1,1,1,0,1,
	1,0,0,0,0,1,1,0,0,0,1,
	1,0,1,4,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,1,0,1,
	1,1,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,0,1,1,
	1,0,4,0,0,0,0,1,4,0,1,
	1,0,0,0,0,2,0,0,0,0,1,
	1,1,1,1,1,0,1,1,1,1,1,
};

InGameScene::InGameScene()
	:m_PlayerX( 0 )
	,m_PlayerY( 0 )
	,m_CrateMax( 3 )
	,m_PlayerCurrectDirection(DirType::DirType_Up)
{

	// ステージデータを初期化
	/*
		g_SampleStageの中身を
		m_StageDataへコピー(読み込み)する
		この時、配列の中身が ObjectType_Player だったら、
		その時のx,yをm_PlayerX(Y)へ代入し、m_StageDataへは ObjectType_Ground を代入する
	*/

	Reset();

	m_Step = STEP_START_JINGLE;

	GroundGraph		= LoadGraph("Res/Ground/ground.png");
	WallGraph		= LoadGraph("Res/Ground/block.png");
	TargetGraph		= LoadGraph("Res/Crate/crate_00.png");
	UnsetCrateGraph = LoadGraph("Res/Crate/crate_01.png");
	SetCrateGraph	= LoadGraph("Res/miniball.png");
	ClearGraph	    = LoadGraph("Res/Clear.png");
	for (int i = 0; i < PlayerMax; i++)
	{
		PlayerGraph[0] = LoadGraph("Res/Player/player_00.png");
		PlayerGraph[1] = LoadGraph("Res/Player/player_03.png");
		PlayerGraph[2] = LoadGraph("Res/Player/player_06.png");
		PlayerGraph[3] = LoadGraph("Res/Player/player_09.png");
	}

	gameMng = GameManager::GetInstance();
}

InGameScene::~InGameScene()
{
	DeleteGraph(GroundGraph);
	DeleteGraph(WallGraph);
	DeleteGraph(TargetGraph);
	DeleteGraph(UnsetCrateGraph);
	DeleteGraph(SetCrateGraph);
	DeleteGraph(ClearGraph);
	for (int i = 0; i < PlayerMax; i++)
	{
		DeleteGraph(PlayerGraph[i]);
	}
	gameMng->SetCount(m_Count);
	gameMng = nullptr;
}

void InGameScene::Exec()
{
	switch (m_Step)
	{
	case STEP_START_JINGLE:   step_StartJingle(); break;
	case STEP_INPUT		  :   step_Input();		  break;
	case STEP_CREAR_JINGLE:   step_ClearJingle(); break;
	default:									  break;
	}
}

void InGameScene::Draw()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (m_StageData[y][x] == ObjectType_Ground)
			{
				DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, GroundGraph, TRUE);
			}
			else if (m_StageData[y][x] == ObjectType_Wall)
			{
				DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, WallGraph, TRUE);
			}
			else if (m_StageData[y][x] == ObjectType_Target)
			{
				DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, TargetGraph, TRUE);
			}
			else if (m_StageData[y][x] == ObjectType_UnsetCrate)
			{
				DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, UnsetCrateGraph, TRUE);
			}
			else if (m_StageData[y][x] == ObjectType_SetCrate)
			{
				DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, SetCrateGraph, TRUE);
			}
		}
	}

	if (m_PlayerCurrectDirection == DirType_Up)
	{
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, PlayerGraph[0], TRUE);
	}
	else if (m_PlayerCurrectDirection == DirType_Down)
	{
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, PlayerGraph[1], TRUE);
	}
	else if (m_PlayerCurrectDirection == DirType_Left)
	{
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, PlayerGraph[2], TRUE);
	}
	else if (m_PlayerCurrectDirection == DirType_Right)
	{
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, PlayerGraph[3], TRUE);
	}
	
	// 操作方法
	DrawString((STAGE_WIDTH * CHIP_WIDTH) + 100,  50, " 十字キー 移動"    , GetColor(200, 250, 250));
	DrawString((STAGE_WIDTH * CHIP_WIDTH) + 100, 100, "    Rキー リセット", GetColor(200, 250, 250));
	DrawFormatString((STAGE_WIDTH * CHIP_WIDTH) + 100, 200, GetColor(200, 250, 250), "手数 %d", m_Count);

	if (IsClear() == true)
	{
		DrawGraph(0, 0, ClearGraph, TRUE);
		DrawString(200, 300, "Enterキーを押してね", GetColor(200, 250, 250));
	}
}

bool InGameScene::IsEnd() const
{
	// @@Dummy 遷移確認用の仮処理
	return ( m_Step == STEP_END );
}

// 開始ジングル待ち
void InGameScene::step_StartJingle()
{
	m_Step = STEP_INPUT;
}

// 入力待ち
void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();

	if ( pInputMng->IsPushed(KeyType_Reset) )
	{
		Reset();
	}
	else if ( pInputMng->IsPushed(KeyType_Up) )
	{
		Move(DirType_Up);
		m_PlayerCurrectDirection = DirType_Up;
		m_Count++;
	}
	else if ( pInputMng->IsPushed(KeyType_Down) )
	{
		Move(DirType_Down);
		m_PlayerCurrectDirection = DirType_Down;
		m_Count++;
	}
	else if ( pInputMng->IsPushed(KeyType_Left) )
	{
		Move(DirType_Left);
		m_PlayerCurrectDirection = DirType_Left;
		m_Count++;
	}
	else if ( pInputMng->IsPushed(KeyType_Right) )
	{
		Move(DirType_Right);
		m_PlayerCurrectDirection = DirType_Right;
		m_Count++;
	}

	if ( IsClear() == true)
	{
		m_Step = STEP_CREAR_JINGLE;
	}
}

// 
void InGameScene::step_ClearJingle()
{
	InputManager* pInputMng = InputManager::GetInstance();

	if (pInputMng->IsPushed(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_Result);
	}

}


// ゲームのクリア判定
// true  = クリアしている
// false = 未クリア
bool InGameScene::IsClear() const
{
	// ２重for文でm_StageDataの配列を検索し、
	// １つでもObjectType_UnsetCrateが見つかったらfalseを返す
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (m_StageData[y][x] == ObjectType_UnsetCrate)
			{
				return false;
			}
		}
	}

	// for文を抜けてきたらobjectType_UnsetCrateがなかったことになり、
	// 逆説的に全てObjectType_SetCrate状態になっている(==ゲームクリア)
	return true; // @@Dummy
}

void InGameScene::Reset()
{
	// g_SampleStageを使ってステージデータを初期化
	// ※外部データを読みこんだり、ステージを増やす場合は処理内容を考える必要がある
	// コンストラクタの内容をそのままコピーして、
	// コンストラクタではResetを呼び出しする

	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if (m_StageData[y][x] == ObjectType_Player)
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}
}

void InGameScene::Move(DirType dir_)
{
	// DirTypeが範囲外だったら処理終了
	if (dir_ < DirType_Up && dir_ >= DirType_Max)
	{
		return;
	}

	int next_x  = m_PlayerX;
	int next_y  = m_PlayerY;
	int next2_x = m_PlayerX;
	int next2_y = m_PlayerY;

	// 移動方法に応じて座標を設定
	// next_x(y), next2_x(y)の値をそれぞれ設定する
	switch (dir_)
	{
	case DirType_Up:
		next_y  -= 1;
		next2_y -= 2;
		break;
	case DirType_Down:
		next_y  += 1;
		next2_y += 2;
		break;
	case DirType_Left:
		next_x  -= 1;
		next2_x -= 2;
		break;
	case DirType_Right:
		next_x  += 1;
		next2_x += 2;
		break;
	}

	// ここに到達した時、next_(y),next2_x(y)には、
	// 上下左右それぞれの移動先が入っているが、
	// 処理的には、同じ変数名を使うことができる

	// 移動先が画面外なら、関数を抜ける
	if (next_x < 0 ||
		next_y < 0 ||
		next_x > (STAGE_WIDTH  - 1) ||
		next_y > (STAGE_HEIGHT - 1))
	{
		return;
	}

	// 通常移動
	// 移動先がプレイヤーの乗れるマップチップだったら、m_PlayerX(Y)をnext_x(y)で上書き
	if (m_StageData[next_y][next_x] == ObjectType_Ground ||
		m_StageData[next_y][next_x] == ObjectType_Target)
	{
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	// 移動先に箱(クレート)がある場合
	else if (m_StageData[next_y][next_x] == ObjectType_UnsetCrate ||
			 m_StageData[next_y][next_x] == ObjectType_SetCrate)
	{
		// ２つ先が画面外かチェック
		if (next2_x < 0 ||
			next2_y < 0 ||
			next2_x >(STAGE_WIDTH - 1) ||
			next2_y >(STAGE_HEIGHT - 1))
		{
			return;
		}

		// 2つ先が移動できないものかチェック
		// 移動できるマップチップでないという場合
		if (m_StageData[next2_y][next2_x] != ObjectType_Ground &&
			m_StageData[next2_y][next2_x] != ObjectType_Target)
		{
			return;
		}

		// ここに到達した場合、必ず動かせる状態になっている

		// 隣の位置を変更する
		if (m_StageData[next_y][next_x] == ObjectType_UnsetCrate)
		{
			m_StageData[next_y][next_x] = ObjectType_Ground;
		}
		else
		{
			m_StageData[next_y][next_x] = ObjectType_Target;
		}

		// ２つ先に箱を配置する
		if (m_StageData[next2_y][next2_x] == ObjectType_Ground)
		{
			m_StageData[next2_y][next2_x] = ObjectType_UnsetCrate;
		}
		else if(m_StageData[next2_y][next2_x] != ObjectType_Ground)
		{
			m_StageData[next2_y][next2_x] = ObjectType_SetCrate;
		}

		// プレイヤーを移動させる
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
}
