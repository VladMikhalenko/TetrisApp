#pragma once
#include <windows.h>

class Brick
{
	//������� ������� �����
	COORD brickPos;
public:
	Brick();
	Brick(COORD position);// = {0,0});
	~Brick();
	void SetPosition(COORD coord);
	COORD GetPosition();
	//���������� ���� �� ���������� value: � ������� ����������
	//������������ value
	void Move(COORD value);
};

