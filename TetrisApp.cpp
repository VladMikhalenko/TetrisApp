#include "TetrisApp.h"
#include <ctime>
TetrisApp::TetrisApp():Parent(50,30)
{
	srand((unsigned)time(NULL));

	X_FIELD_SIZE = X_SIZE/2;
	Y_FIELD_SIZE = Y_SIZE - 4;
	X_NEXT_SIZE = 8;
	Y_NEXT_SIZE = 6;

	//field_init_point = {(short)(X_FIELD_SIZE/2),1 };
	field_init_point.X=(short)X_FIELD_SIZE/2;
	field_init_point.Y=1;
	//next_init_point = { (short)(X_FIELD_SIZE + X_NEXT_SIZE / 2)-1,(short)(Y_NEXT_SIZE / 2)-1 };
	next_init_point.X = (short)(X_FIELD_SIZE + X_NEXT_SIZE / 2)-1;
	next_init_point.Y=(short)(Y_NEXT_SIZE / 2)-1;
	Initialization();
	
}

TetrisApp::~TetrisApp()
{
}

void TetrisApp::KeyPressed(int btnCode)
{	
	COORD down={0,1};
	
	COORD left={-1,0};

	COORD right={1,0};

	if (btnCode == VK_DOWN || btnCode == 40 || btnCode == 80)
		MoveTetramino(br, down);//COORD{ 0,1 });
	else if (btnCode == VK_LEFT || btnCode == 37 || btnCode == 75)
		MoveTetramino(br,left); //COORD{ -1,0 });
	else if (btnCode == VK_RIGHT || btnCode == 39 || btnCode == 77)
		MoveTetramino(br, right);//COORD{ 1,0 });
	else if (btnCode = VK_SPACE)
		RotateTetramino(br);
	else
		return;
}

void TetrisApp::UpdateF(float deltaTime)
{
	SetCharTetramino(br, L'*');
	if (HasReachedBottom(br))
	{
		br.GenerateInitialBricks(field_init_point, nextBr.GetTetraminoType());
		GetNextTetramino();	
		if (GameOver())
		{
			Initialization();
			return;
		}
	}
	SetCharTetramino(br, L'*');
	oldBr=br;
}

void TetrisApp::OneSecondAction()
{
	COORD down={0,1};
	if(MoveTetramino(br, down))//COORD{ 0,1 }))
		SetCharTetramino(oldBr, '.');
	ControlLine();
}

bool TetrisApp::MoveTetramino(TetraminoBrick &brick,COORD coord)
{
	bool res = false;
	if (CanMove(brick,coord))
	{
		transformer.Translate(brick, coord);
		SetCharTetramino(oldBr, '.');
		res = true;
	}
	return res;
	
}
bool TetrisApp::RotateTetramino(TetraminoBrick & brick)
{
	IsCloseToBorder(brick);
	transformer.Rotate(brick);
	SetCharTetramino(oldBr, '.');
	return true;
}

void TetrisApp::SetCharTetramino(TetraminoBrick &brick,wchar_t c)
{
	for (int i = 0; i < 4; i++)
	{
		Brick part = brick.GetBrickByIndex(i);
		SetChar(part.GetPosition().X, part.GetPosition().Y, c);
	}	
}

void TetrisApp::GetNextTetramino()
{
	int nextTet =rand()%7;
	nextBr.GenerateInitialBricks(next_init_point, (BrickType)nextTet);
	
	COORD zero={(short)X_FIELD_SIZE,0};

	SetCharGameFieldBorders(X_NEXT_SIZE, Y_NEXT_SIZE,zero); //COORD{(short)X_FIELD_SIZE ,0 });
	SetCharTetramino(nextBr, '*');
}

bool TetrisApp::HasReachedBottom(TetraminoBrick brick)
{
	for (int i = 0; i < 4; i++)
	{
		Brick b = brick.GetBrickByIndex(i);
		short x = b.GetPosition().X;
		short y= b.GetPosition().Y;
		COORD point={x,y+1};
		if (y+1 == Y_FIELD_SIZE - 1 ||
			(GetChar(x, y+1) == '*' && !brick.ContainCoord(point)))//COORD{ x,y+1 })))
		{
			return true;
		}
	}
	return false;
}

bool TetrisApp::CanMove(TetraminoBrick tbrick,COORD coord)
{
	TetraminoBrick copy = tbrick;
	transformer.Translate(copy, coord);
	for (int i = 0; i < 4; i++)
	{
		Brick b = copy.GetBrickByIndex(i);
		short x = b.GetPosition().X;
		short y = b.GetPosition().Y;
		COORD point={x,y};
		if ((GetChar(x, y) == '*' && !tbrick.ContainCoord(point))||//COORD{ x,y })) || 
			y== Y_FIELD_SIZE - 1 || 
			x==0 || 
			x==X_FIELD_SIZE)
			return false;
	}
	return true;
}

bool TetrisApp::CanRotate(TetraminoBrick brick)
{
	transformer.Rotate(brick);
	for (int i = 0; i < 4; i++)
	{
		Brick b = brick.GetBrickByIndex(i);
		short x = b.GetPosition().X;
		short y = b.GetPosition().Y;
		COORD point={x,y};
		if ((GetChar(x, y) == '*' && !brick.ContainCoord(point)))//||//COORD{ x,y })) || 
			//y == Y_FIELD_SIZE - 1 //|| GetChar(x, y)=='#')
			return false;
	}
	return true;
}


void TetrisApp::ControlLine()
{
	for (int y = Y_FIELD_SIZE-2; y > 0; y--)
	{
		if (IsLine(y))
		{
			ClearLine(y);
			y = Y_FIELD_SIZE - 1;
		}
	}
}

void TetrisApp::ClearLine(int y)
{
	while (ContainBricks(y))
	{
		for (int x = 1; x <= X_FIELD_SIZE; x++)
			SetChar(x, y, GetChar(x, y-1));
		y--;
	}
}

bool TetrisApp::GameOver()
{
	for (int y = 1; y < Y_FIELD_SIZE - 2; y++)
		if (!ContainBricks(y))
			return false;
	return true;
}

bool TetrisApp::ContainBricks(int y)
{
	for (int x = 1; x < X_FIELD_SIZE - 1; x++)
		if (GetChar(x, y) == '*')
			return true;
	return false;
}

bool TetrisApp::IsLine(int y)
{
	for (int x = 1; x < X_FIELD_SIZE; x++)
		if (GetChar(x, y) != '*')
			return false;
	return true;
}

void TetrisApp::SetCharGameFieldBorders(int width,int height, COORD bgnPoint)
{
	SHORT bX = bgnPoint.X;
	SHORT bY = bgnPoint.Y;
	for (int y = 0; y < height;y++)
	{
		for (int x = 0; x <= width;x++)
		{
			if (y == 0 || (y + 1) == height || x==0 || x==width)
			{
				SetChar(bX+x, bY+y, L'#');
			}
			else{
				SetChar(bX+x, bY+y, L'.');
			}
		}
	}
}

void TetrisApp::Initialization()
{
	COORD fZero={0,0};
	COORD nZero={(short)X_FIELD_SIZE,0};
	
	SetCharGameFieldBorders(X_FIELD_SIZE, Y_FIELD_SIZE, fZero);//COORD{ 0,0 });//заполняем буфер игровым полем
	SetCharGameFieldBorders(X_NEXT_SIZE, Y_NEXT_SIZE, nZero);//COORD{ (short)X_FIELD_SIZE,0 });//заполняем буфер полем для отображения след. фигуры

	GetNextTetramino();//генерируем первую фигуру
	br.GenerateInitialBricks(field_init_point, nextBr.GetTetraminoType());//генерируем первую фигуру в игровом поле
	oldBr = br;//запоминаем текущую фигуру
	GetNextTetramino();//генерируем следующую
}

void TetrisApp::IsCloseToBorder(TetraminoBrick &brick)
{
	if(CanRotate(brick))
	{
		BrickType type=brick.GetTetraminoType();
		COORD rotP=brick.GetBrickByIndex(0).GetPosition();
		COORD moveP={0,0};
		if(type==L || type==J ||type==T || type==S || type==Z)
		{
			if(rotP.X==1)
				moveP.X=1;
			else if(rotP.X==X_FIELD_SIZE-1)
				moveP.X=-1;
		}
		else if(type==I)
		{
			if(rotP.X==1)
				moveP.X=1;
			else if(rotP.X==X_FIELD_SIZE-1)
				moveP.X=-2;
			if(rotP.Y<3)
				moveP.Y=3-rotP.Y;
		}
		transformer.Translate(brick,moveP);
	}
	
}