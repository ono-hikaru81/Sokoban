
#include "Player.h"

Player::Player()
	: m_PosX(0)
	, m_PosY(0)
	, m_MoveSpeed(0)
{
}

Player::~Player()
{
}

void Player::Exec()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPushed(KeyType_Up))
	{
		direction = DirType_Up;


	}
	else if (pInputMng->IsPushed(KeyType_Down))
	{
		direction = DirType_Down;


	}
	else if (pInputMng->IsPushed(KeyType_Left))
	{
		direction = DirType_Left;

	}
	else if (pInputMng->IsPushed(KeyType_Right))
	{
		direction = DirType_Right;

	}
}

void Player::Draw()
{

}

void Player::SetPos(int x_, int y_)
{
	m_PosX = x_;
	m_PosY = y_;
}

void Player::SetMoveSpeed(int speed_)
{
	m_MoveSpeed = speed_;
}
