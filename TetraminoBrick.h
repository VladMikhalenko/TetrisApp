#pragma once
#include "Brick.h"
//перечисление видов тетрамин
enum BrickType{I,J,L,O,S,T,Z};
//Основная фигура, котора задействована в игре Тетрис
class TetraminoBrick
{
	//Составляющие элементы тетрамины. Первый блок, это точка поворот
	Brick bricks[4];
	BrickType currentType;//текущий тип тетрамины
	int rotation;//текущее значение угла поворота, используется при повороте фигуры
public:
	TetraminoBrick();
	TetraminoBrick(const TetraminoBrick &brick);
	virtual ~TetraminoBrick();
	
	
	Brick GetBrickByIndex(int index) const;
	void SetBrickByIndex(Brick br,int index);
	BrickType GetTetraminoType() const;

	int GetRotationAngle() const;
	void SetRotationAngle(int angle);

	void GenerateInitialBricks(COORD coord, BrickType type);

	bool ContainCoord(COORD coord);
};

