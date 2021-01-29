
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_START_JINGLE,
	STEP_INPUT,		// ���͑҂�
	STEP_CREAR_JINGLE,
	STEP_END		// �V�[���I��
};

// �q�ɔԂ̃T���v���X�e�[�W
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

	// �X�e�[�W�f�[�^��������
	/*
		g_SampleStage�̒��g��
		m_StageData�փR�s�[(�ǂݍ���)����
		���̎��A�z��̒��g�� ObjectType_Player ��������A
		���̎���x,y��m_PlayerX(Y)�֑�����Am_StageData�ւ� ObjectType_Ground ��������
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
	
	// ������@
	DrawString((STAGE_WIDTH * CHIP_WIDTH) + 100,  50, " �\���L�[ �ړ�"    , GetColor(200, 250, 250));
	DrawString((STAGE_WIDTH * CHIP_WIDTH) + 100, 100, "    R�L�[ ���Z�b�g", GetColor(200, 250, 250));
	DrawFormatString((STAGE_WIDTH * CHIP_WIDTH) + 100, 200, GetColor(200, 250, 250), "�萔 %d", m_Count);

	if (IsClear() == true)
	{
		DrawGraph(0, 0, ClearGraph, TRUE);
		DrawString(200, 300, "Enter�L�[�������Ă�", GetColor(200, 250, 250));
	}
}

bool InGameScene::IsEnd() const
{
	// @@Dummy �J�ڊm�F�p�̉�����
	return ( m_Step == STEP_END );
}

// �J�n�W���O���҂�
void InGameScene::step_StartJingle()
{
	m_Step = STEP_INPUT;
}

// ���͑҂�
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


// �Q�[���̃N���A����
// true  = �N���A���Ă���
// false = ���N���A
bool InGameScene::IsClear() const
{
	// �Q�dfor����m_StageData�̔z����������A
	// �P�ł�ObjectType_UnsetCrate������������false��Ԃ�
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

	// for���𔲂��Ă�����objectType_UnsetCrate���Ȃ��������ƂɂȂ�A
	// �t���I�ɑS��ObjectType_SetCrate��ԂɂȂ��Ă���(==�Q�[���N���A)
	return true; // @@Dummy
}

void InGameScene::Reset()
{
	// g_SampleStage���g���ăX�e�[�W�f�[�^��������
	// ���O���f�[�^��ǂ݂��񂾂�A�X�e�[�W�𑝂₷�ꍇ�͏������e���l����K�v������
	// �R���X�g���N�^�̓��e�����̂܂܃R�s�[���āA
	// �R���X�g���N�^�ł�Reset���Ăяo������

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
	// DirType���͈͊O�������珈���I��
	if (dir_ < DirType_Up && dir_ >= DirType_Max)
	{
		return;
	}

	int next_x  = m_PlayerX;
	int next_y  = m_PlayerY;
	int next2_x = m_PlayerX;
	int next2_y = m_PlayerY;

	// �ړ����@�ɉ����č��W��ݒ�
	// next_x(y), next2_x(y)�̒l�����ꂼ��ݒ肷��
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

	// �����ɓ��B�������Anext_(y),next2_x(y)�ɂ́A
	// �㉺���E���ꂼ��̈ړ��悪�����Ă��邪�A
	// �����I�ɂ́A�����ϐ������g�����Ƃ��ł���

	// �ړ��悪��ʊO�Ȃ�A�֐��𔲂���
	if (next_x < 0 ||
		next_y < 0 ||
		next_x > (STAGE_WIDTH  - 1) ||
		next_y > (STAGE_HEIGHT - 1))
	{
		return;
	}

	// �ʏ�ړ�
	// �ړ��悪�v���C���[�̏���}�b�v�`�b�v��������Am_PlayerX(Y)��next_x(y)�ŏ㏑��
	if (m_StageData[next_y][next_x] == ObjectType_Ground ||
		m_StageData[next_y][next_x] == ObjectType_Target)
	{
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	// �ړ���ɔ�(�N���[�g)������ꍇ
	else if (m_StageData[next_y][next_x] == ObjectType_UnsetCrate ||
			 m_StageData[next_y][next_x] == ObjectType_SetCrate)
	{
		// �Q�悪��ʊO���`�F�b�N
		if (next2_x < 0 ||
			next2_y < 0 ||
			next2_x >(STAGE_WIDTH - 1) ||
			next2_y >(STAGE_HEIGHT - 1))
		{
			return;
		}

		// 2�悪�ړ��ł��Ȃ����̂��`�F�b�N
		// �ړ��ł���}�b�v�`�b�v�łȂ��Ƃ����ꍇ
		if (m_StageData[next2_y][next2_x] != ObjectType_Ground &&
			m_StageData[next2_y][next2_x] != ObjectType_Target)
		{
			return;
		}

		// �����ɓ��B�����ꍇ�A�K�����������ԂɂȂ��Ă���

		// �ׂ̈ʒu��ύX����
		if (m_StageData[next_y][next_x] == ObjectType_UnsetCrate)
		{
			m_StageData[next_y][next_x] = ObjectType_Ground;
		}
		else
		{
			m_StageData[next_y][next_x] = ObjectType_Target;
		}

		// �Q��ɔ���z�u����
		if (m_StageData[next2_y][next2_x] == ObjectType_Ground)
		{
			m_StageData[next2_y][next2_x] = ObjectType_UnsetCrate;
		}
		else if(m_StageData[next2_y][next2_x] != ObjectType_Ground)
		{
			m_StageData[next2_y][next2_x] = ObjectType_SetCrate;
		}

		// �v���C���[���ړ�������
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
}
