#pragma once
#include "TetraminoBrick.h"
class Transformer2D
{
public:
	Transformer2D();
	~Transformer2D();
	//����������� ���������
	void Translate(TetraminoBrick &brick, COORD coord);
	//������� ���������
	void Rotate(TetraminoBrick &brick);

};

