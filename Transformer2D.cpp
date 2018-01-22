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
	double angle;//���� ��������
	COORD center = tbrick.GetBrickByIndex(0).GetPosition();//����� ��������
	int curAngle = tbrick.GetRotationAngle();//������� ���� �������� ���������
	BrickType type = tbrick.GetTetraminoType();//��� ���������
	if (type == I || type == S || type == Z)//��� I,S,Z ������ ��� ��������� ��������
		angle = curAngle <= 0 ? 90 : -90;
	else if (type == J || type == L || type == T)// J,L,T ��������� ��� �����:)
		angle = 90;
	else return;//O ����� ������ �� ������������
	tbrick.SetRotationAngle(angle);

	double rad = angle*M_PI / 180;
	double sinus = sin(rad);
	double cosin = cos(rad);
	
	for (int i = 0; i < 4; i++)
	{
		COORD mCenter={-center.X,-center.Y};
		Translate(tbrick, mCenter);//COORD{ -center.X,-center.Y });//���������� � ����� ��� ���������
		Brick br = tbrick.GetBrickByIndex(i);//����� �-� ���� ���������
		int x = br.GetPosition().X;
		int y= br.GetPosition().Y;
		//������� ����� �� ������������ ������� �������� �� ������
		double dx = x*cosin - y*sinus;//������� ����� ����� � ����� ��������
		double dy = x*sinus + y*cosin;//������� Y 
		COORD new_c;
		new_c.X = dx > 0 ? (short)(dx + 0.5): (short)(dx - 0.5);//��������� ���������� ����������
		new_c.Y = dy>0?(short)(dy+0.5):(short)(dy-0.5);
		br.SetPosition(new_c);//COORD{ new_x, new_y });//��������� i-�� ���� � ����� �������
		tbrick.SetBrickByIndex(br, i);//����������� ��������� ����� i-�� ����
		Translate(tbrick, center);//���������� ��� ��������� ������� � �������� �����
	}
}
