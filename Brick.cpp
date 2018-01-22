#include "Brick.h"

Brick::Brick()
{
	COORD def={0,0};
	SetPosition(def);
}
Brick::Brick(COORD position)
{
	SetPosition(position);
}

Brick::~Brick()
{
}

void Brick::SetPosition(COORD coord)
{
	brickPos.X = coord.X;
	brickPos.Y = coord.Y;
}
COORD Brick::GetPosition()
{
	return brickPos;
}

void Brick::Move(COORD value)
{
	brickPos.X += value.X;
	brickPos.Y += value.Y;
}