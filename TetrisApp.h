#pragma once
#include "BaseApp.h"
#include "Transformer2D.h"

class TetrisApp :
	public BaseApp
{
	typedef BaseApp Parent;
	//Ширина игрового поля
	int X_FIELD_SIZE;
	//Высота игрового поля
	int Y_FIELD_SIZE;
	//Ширина области отображения
	int X_NEXT_SIZE;
	//Высота области отображения
	int Y_NEXT_SIZE;

	//Начальная точка появления сгенерированной фигуры в игровом поле
	COORD field_init_point;
	//Точка отображения следующей фигурки
	COORD next_init_point;

	//Отвечает за поворот и перемещение тетрамины в пространстве
	Transformer2D transformer;
	//Текущая фигура
	TetraminoBrick br;
	//Следующая фигура, которая будет отображена на игровом поле
	TetraminoBrick nextBr;
	//Предыдущая фигура, используется для очистки старой позиции тетрамины
	TetraminoBrick oldBr;

public:
	TetrisApp();
	~TetrisApp();
	
	void KeyPressed(int btnCode);
	void UpdateF(float deltaTime);
	//Переопределяет метод из базового класса, отвечает за по секундный спуск тетрамины
	//и контроль наличия линий
	void OneSecondAction();

	//Перемещение тетрамины на координату coord, возвращает true- если перемещение возможно
	//иначе - false
	bool MoveTetramino(TetraminoBrick &brick,COORD coord);
	//Поворот тетрамины на угол кратный 90 градусам, true - поворот возможен, иначе false
	bool RotateTetramino(TetraminoBrick &brick);
	//Генерация следующей вигуры, переменной nextBr генерируется случайный тип тетрамины 
	void GetNextTetramino();

	//"Прорисовка" тетрамины в буфере для отображения
	void SetCharTetramino(TetraminoBrick &brick,wchar_t c);
	//"Прорисовка" игровых границ в буфере для отображения для области высотой height и шириной width в точке bgnPoint 
	void SetCharGameFieldBorders(int width,int height,COORD bgnPoint);
	//Метод начальной инициализации игры, т.е. генерация первой фигурки, полей
	void Initialization();
	//Проверка достижения фигурой дна игрового поля
	bool HasReachedBottom(TetraminoBrick brick);
	//Проверка возможности перемещения фигурки в пространстве на координату coord
	bool CanMove(TetraminoBrick brick,COORD coord);
	//Проверка возможности поворота фигурки
	bool CanRotate(TetraminoBrick brick);
	//Метод отвечает за очистку собранных линий
	void ControlLine();
	//Проверка того, что строка y и игрового поля содержит хотябы один блок тетрамины
	bool ContainBricks(int y);
	//Проверка того, содержит ли строка y все элементы '*', т.е. подлежит очистке
	bool IsLine(int y);
	//Очищает строку состоящую из '*' путем спуска на 1 линию всех выше расположенных строк,
	// в которых содержится хотябы один блок тетрамины
	void ClearLine(int y);
	//Проверка заполненности игрового поля
	bool GameOver();
	//смещение фигуры в случае близости при повороте
	void IsCloseToBorder(TetraminoBrick &brick);
};

