#pragma once
#include <windows.h>

class Brick
{
	//“екуща€ позици€ блока
	COORD brickPos;
public:
	Brick();
	Brick(COORD position);// = {0,0});
	~Brick();
	void SetPosition(COORD coord);
	COORD GetPosition();
	//ѕеремещает блок на координату value: к текущей координате
	//прибавл€етс€ value
	void Move(COORD value);
};

