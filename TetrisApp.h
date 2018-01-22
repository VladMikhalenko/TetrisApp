#pragma once
#include "BaseApp.h"
#include "Transformer2D.h"

class TetrisApp :
	public BaseApp
{
	typedef BaseApp Parent;
	//������ �������� ����
	int X_FIELD_SIZE;
	//������ �������� ����
	int Y_FIELD_SIZE;
	//������ ������� �����������
	int X_NEXT_SIZE;
	//������ ������� �����������
	int Y_NEXT_SIZE;

	//��������� ����� ��������� ��������������� ������ � ������� ����
	COORD field_init_point;
	//����� ����������� ��������� �������
	COORD next_init_point;

	//�������� �� ������� � ����������� ��������� � ������������
	Transformer2D transformer;
	//������� ������
	TetraminoBrick br;
	//��������� ������, ������� ����� ���������� �� ������� ����
	TetraminoBrick nextBr;
	//���������� ������, ������������ ��� ������� ������ ������� ���������
	TetraminoBrick oldBr;

public:
	TetrisApp();
	~TetrisApp();
	
	void KeyPressed(int btnCode);
	void UpdateF(float deltaTime);
	//�������������� ����� �� �������� ������, �������� �� �� ��������� ����� ���������
	//� �������� ������� �����
	void OneSecondAction();

	//����������� ��������� �� ���������� coord, ���������� true- ���� ����������� ��������
	//����� - false
	bool MoveTetramino(TetraminoBrick &brick,COORD coord);
	//������� ��������� �� ���� ������� 90 ��������, true - ������� ��������, ����� false
	bool RotateTetramino(TetraminoBrick &brick);
	//��������� ��������� ������, ���������� nextBr ������������ ��������� ��� ��������� 
	void GetNextTetramino();

	//"����������" ��������� � ������ ��� �����������
	void SetCharTetramino(TetraminoBrick &brick,wchar_t c);
	//"����������" ������� ������ � ������ ��� ����������� ��� ������� ������� height � ������� width � ����� bgnPoint 
	void SetCharGameFieldBorders(int width,int height,COORD bgnPoint);
	//����� ��������� ������������� ����, �.�. ��������� ������ �������, �����
	void Initialization();
	//�������� ���������� ������� ��� �������� ����
	bool HasReachedBottom(TetraminoBrick brick);
	//�������� ����������� ����������� ������� � ������������ �� ���������� coord
	bool CanMove(TetraminoBrick brick,COORD coord);
	//�������� ����������� �������� �������
	bool CanRotate(TetraminoBrick brick);
	//����� �������� �� ������� ��������� �����
	void ControlLine();
	//�������� ����, ��� ������ y � �������� ���� �������� ������ ���� ���� ���������
	bool ContainBricks(int y);
	//�������� ����, �������� �� ������ y ��� �������� '*', �.�. �������� �������
	bool IsLine(int y);
	//������� ������ ��������� �� '*' ����� ������ �� 1 ����� ���� ���� ������������� �����,
	// � ������� ���������� ������ ���� ���� ���������
	void ClearLine(int y);
	//�������� ������������� �������� ����
	bool GameOver();
	//�������� ������ � ������ �������� ��� ��������
	void IsCloseToBorder(TetraminoBrick &brick);
};

