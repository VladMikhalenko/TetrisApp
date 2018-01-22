#include "TetraminoBrick.h"


TetraminoBrick::TetraminoBrick()
{
	rotation = 0;
}

TetraminoBrick::TetraminoBrick(const TetraminoBrick &brick)
{
	for (int i = 0; i < 4; i++)
		this->SetBrickByIndex(brick.GetBrickByIndex(i),i);
	currentType = brick.GetTetraminoType();
	rotation = brick.GetRotationAngle();
}

TetraminoBrick::~TetraminoBrick()
{
}

void TetraminoBrick::GenerateInitialBricks(COORD init_point,BrickType type)
{
	short X = init_point.X;
	short Y = init_point.Y;
	currentType = type;
	COORD rot;
	COORD b1;
	COORD b2;
	COORD b3;
	switch (type)
	{
		case I: {
			//XXXX
			rot.X=X + 1;
			rot.Y=Y;
			b1.X=X;
			b1.Y=Y;
			b2.X=X+2;
			b2.Y=Y;
			b3.X=X+3;
			b3.Y=Y;
		}break;
		case J: {
			//X
			//XXX
			rot.X=X + 1;
			rot.Y=Y+1;
			
			b1.X=X;
			b1.Y=Y;
			
			b2.X=X;
			b2.Y=Y+1;
			
			b3.X=X+2;
			b3.Y=Y+1;
		}break; 
		case L: {
			//  X
			//XXX
			rot.X=X + 1;
			rot.Y=Y+1;
			
			b1.X=X;
			b1.Y=Y+1;
			
			b2.X=X+2;
			b2.Y=Y+1;
			
			b3.X=X+2;
			b3.Y=Y;
		}break;
		case O: {
			//XX
			//XX
			rot.X=X ;
			rot.Y=Y;
			
			b1.X=X;
			b1.Y=Y+1;
			
			b2.X=X+1;
			b2.Y=Y+1;
			
			b3.X=X+1;
			b3.Y=Y;
		}break;
		case S: {
			// XX
			//XX
			rot.X=X + 1;
			rot.Y=Y+1;
			
			b1.X=X;
			b1.Y=Y+1;
			
			b2.X=X+1;
			b2.Y=Y;
			
			b3.X=X+2;
			b3.Y=Y;
		}break;
		case T: {
			// X
			//XXX
			rot.X=X + 1;
			rot.Y=Y+1;
			
			b1.X=X;
			b1.Y=Y+1;
			
			b2.X=X+1;
			b2.Y=Y;
			
			b3.X=X+2;
			b3.Y=Y+1;
		}break;
		case Z: {
			//XX
			// XX
			rot.X=X + 1;
			rot.Y=Y+1;
			
			b1.X=X;
			b1.Y=Y;
			
			b2.X=X+1;
			b2.Y=Y;
			
			b3.X=X+2;
			b3.Y=Y+1;
		}break;
	}
	bricks[0].SetPosition(rot);//COORD{ X + 1,Y });
	bricks[1].SetPosition(b1);//COORD{ X ,Y });
	bricks[2].SetPosition(b2);//COORD{ X+2 ,Y });
	bricks[3].SetPosition(b3);//COORD{ X+3 ,Y });
}

Brick TetraminoBrick::GetBrickByIndex(int index) const
{
	if(index>-1 && index<4)
		return bricks[index];
	else throw EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
}

void TetraminoBrick::SetBrickByIndex(Brick br,int index)
{
	if (index > -1 && index < 4)
		bricks[index] = br;
	else
		throw EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
}

BrickType TetraminoBrick::GetTetraminoType() const
{
	return currentType;
}

int TetraminoBrick::GetRotationAngle() const
{
	return rotation;
}

void TetraminoBrick::SetRotationAngle(int angle)
{
	rotation = angle;
}

bool TetraminoBrick::ContainCoord(COORD coord)
{
	for (int i=0;i<4;i++)
	{
		if (bricks[i].GetPosition().X == coord.X && bricks[i].GetPosition().Y == coord.Y)
			return true;
	}
	return false;
}