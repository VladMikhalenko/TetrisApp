#include "Transformer2D.h"
#define _USE_MATH_DEFINES
#include <cmath>


Transformer2D::Transformer2D()
{
}

Transformer2D::~Transformer2D()
{
}

void Transformer2D::Translate(TetraminoBrick &brick, COORD coord)
{
	for (int i = 0; i < 4; i++)
	{
		Brick brickPart = brick.GetBrickByIndex(i);
		brickPart.Move(coord);
		short new_x = brickPart.GetPosition().X;
		short new_y = brickPart.GetPosition().Y;
		brick.SetBrickByIndex(brickPart, i);
	}
}

void Transformer2D::Rotate(TetraminoBrick &tbrick)
{
	double angle;//угол поворота
	COORD center = tbrick.GetBrickByIndex(0).GetPosition();//точка поворота
	int curAngle = tbrick.GetRotationAngle();//текущий угол поворота тетрамины
	BrickType type = tbrick.GetTetraminoType();//тип тетрамины
	if (type == I || type == S || type == Z)//для I,S,Z только два возможных поворота
		angle = curAngle <= 0 ? 90 : -90;
	else if (type == J || type == L || type == T)// J,L,T крутяться как хотят:)
		angle = 90;
	else return;//O кубик вообще не поворачиваем
	tbrick.SetRotationAngle(angle);

	double rad = angle*M_PI / 180;
	double sinus = sin(rad);
	double cosin = cos(rad);
	
	for (int i = 0; i < 4; i++)
	{
		COORD mCenter={-center.X,-center.Y};
		Translate(tbrick, mCenter);//COORD{ -center.X,-center.Y });//перемещаем в центр оси координат
		Brick br = tbrick.GetBrickByIndex(i);//берем і-й блок тетрамины
		int x = br.GetPosition().X;
		int y= br.GetPosition().Y;
		//Формулы взяты из произведения матрицы поворота на вектор
		double dx = x*cosin - y*sinus;//считаем новую точку Х после поворота
		double dy = x*sinus + y*cosin;//считаем Y 
		COORD new_c;
		new_c.X = dx > 0 ? (short)(dx + 0.5): (short)(dx - 0.5);//округляем полученные координаты
		new_c.Y = dy>0?(short)(dy+0.5):(short)(dy-0.5);
		br.SetPosition(new_c);//COORD{ new_x, new_y });//перемещем i-ый блок в новую позицию
		tbrick.SetBrickByIndex(br, i);//присваиваем тетрамине новый i-ый блок
		Translate(tbrick, center);//перемещаем всю тетрамину обратно в исходную точку
	}
}
