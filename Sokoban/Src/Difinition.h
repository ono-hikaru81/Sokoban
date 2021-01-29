
#ifndef DIFINITION_H
#define DIFINITION_H

//---------------------------------
enum SceneID
{
	SceneID_Title,	// �^�C�g��
	SceneID_InGame,	// �C���Q�[��
	SceneID_Result,	// ���U���g


	SceneID_Max,
	SceneID_Invalid // �����l
};

//---------------------------------

//�X�e�[�W���
const int STAGE_WIDTH  = 11;
const int STAGE_HEIGHT = 13;

// �}�b�v�`�b�v�̏c���T�C�Y
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;

// �I�u�W�F�N�g���
//		0	�n��
//		1	��
//		2	�v���C���[�̏����ʒu
//		3	�N���[�g�z�u�ꏊ
//		4	���z�u�̃N���[�g
//		7	�z�u�ς݂̃N���[�g
//			(�z�u�ꏊ'3' + ���z�u�N���[�g'4' = 7)

enum ObjectType
{
	ObjectType_Ground,			// 0
	ObjectType_Wall,			// 1
	ObjectType_Player,			// 2
	ObjectType_Target,			// 3
	ObjectType_UnsetCrate,		// 4
	ObjectType_SetCrate = 7,	// 7
};

// �ړ�����
enum DirType
{
	DirType_Up,		// ��
	DirType_Down,	// ��
	DirType_Left,	// ��
	DirType_Right,	// �E

	// �摜�ǂݍ��݂Ŏg�p����
	DirType_Max,
};

#endif // !DIFINITION_H
