
#ifndef KEY_DIFINITION_H
#define KEY_DIFINITION_H

#include "DxLib.h"

enum KeyType
{
	KeyType_Up,		// ��ړ�
	KeyType_Down,	// ���ړ�
	KeyType_Left,	// ���ړ�
	KeyType_Right,	// �E�ړ�
	KeyType_Enter,	// ����
	KeyType_Reset,	// ���Z�b�g

	KeyType_Max		// �L�[�̎�ނ̐�
};

// �Ώۂ̃L�[�̏��
enum InputState
{
	NoHold,		// �����ĂȂ����
	Pushed,		// �������u��
	Hold,		// �����Ă���
	Released,	// �������u��
	InValid		// ����
};


// �L�[�̎�ނɑΉ�����A���ۂ̓��͔z��
const int KEY_ASSIGN[KeyType_Max] =
{
	KEY_INPUT_UP,		// KeyType_Up
	KEY_INPUT_DOWN,		// KeyType_Down
	KEY_INPUT_LEFT,		// KeyType_Left
	KEY_INPUT_RIGHT,	// KeyType_Right
	KEY_INPUT_RETURN,	// KeyType_Enter
	KEY_INPUT_R,		// KeyType_Reset
};

#endif // !KEY_DIFINITION_H
