
#ifndef PLAYER_H
#define PLAYER_H

#include "../Manager/TextureManager.h"
#include "../Manager/InputManager.h"
#include "../Difinition.h"

class Player
{
public:
	Player();
	~Player();

	void Exec();
	void Draw();

	void SetPos(int x_, int y_);
	void SetMoveSpeed(int speed_);

	int GetPosX() const { return m_PosX; }
	int GetPosY() const { return m_PosY; }
	int GetMoveSpeed() const { return m_MoveSpeed; }

	DirType direction = DirType_Up;

private:
	int m_PosX;
	int m_PosY;
	int m_MoveSpeed;
};

#endif // !PLAYER_H

