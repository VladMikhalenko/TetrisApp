#pragma once
#include "TetraminoBrick.h"
class Transformer2D
{
public:
	Transformer2D();
	~Transformer2D();
	//Перемещение тетрамины
	void Translate(TetraminoBrick &brick, COORD coord);
	//Поворот тетрамины
	void Rotate(TetraminoBrick &brick);

};

