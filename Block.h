#ifndef BLOCK_H
#define BLOCK_H

#include<stdio.h>
#include<windows.h>
#include<vector>
using std::vector;

namespace SNAKE {

typedef unsigned short tyb;

class Block // ����� �� ������� �������� ������� �� �������
{
	char symb; //������ �����
	int Fx; // ����������
	int Fy; // ����������
	short FDir; // ����������� �������� �����
	tyb FColor; // ���� �����
	static HANDLE hOut; // ���������� ������
	static void CreatHOut() { // �������� ���������� ������
		if(!hOut)
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	}
public:
	Block(int x = 0, int y = 0, tyb color = 0);
	void SetX(int x);
	void SetY(int y);
	void SetColor(int color);
	void SetPos(int x, int y);
	void SetBlock(int x, int y, int color);
	int GetX(){return Fx;}
	int GetY(){return Fy;}
	int GetColor() { return FColor; }
	void Show();
	void Hide();
	void SetDir(short d){FDir = d>0&&d<5?d:3;}
	short GetDir(){return FDir;}
	void SetSymb(char s); // ��������� ������ �����, �� ��������� (char)219
};

typedef vector<Block> blocks; // ��� ������� �� ������

class Snake // �������� ������ ����
{
	blocks FSnake;
	tyb FSize;
	tyb FColor;
	Block FBlock;
	Block RBlock(){FBlock.SetX(5);}
	short FDir;
public:
	Snake(tyb size = 5, tyb color = 1);
	void Show();
	void Go(); // �������� ������ � �������� �����������
	int GetX() { return FSnake[0].GetX(); } // FSnake[0] - ������ ����
	int GetY() { return FSnake[0].GetY(); }
	void SetDir(short d);
	template<typename T1, typename T2>
	friend bool PosEqual(T1 a, T2 b);
	bool crash() const;
	bool crash(Block b) const;
	void operator++();
	/*friend void BegDir(short d);*/
};

template<typename T1, typename T2>
bool PosEqual(T1 a, T2 b) {
	return (a.GetX() == b.GetX() && a.GetY() == b.GetY()) ? true : false;
}

}

#endif