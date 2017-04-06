#ifndef GAME_H
#define GAME_H


#include "Block.h"
#include "Features.h"
#include <ctime>
#include <conio.h>
#include<cstring>
#include<cstdlib>

using namespace SNAKE;

#include<iostream>
using namespace std;

extern HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Дополнительное устройство вывода для рамки и текстовых сообщений

void SnakeGame(); // Игра в змейку
void TextMessage(char* text, int c1 = 6, int c2 = 4); // Вывод текстовых сообщений в рамке. c1 - цвет рамки, с2 - цвет текста
void Frame(int FrameColor, int FrameHeight, int FrameWidth); // Рамка (цвет, выоста, ширина)
Block Food(const Snake snake); // Генерация еды на консоли

/*-----------------------------------------------------------------------------------------------------*/


void SnakeGame() {
	Snake snake(6, 2);
	srand(time(0));
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int fc = 3, fw = 80, fh = 50, //
		x, y; 
	Frame(fc, fh, fw);

	snake.Show();
	bool FoodFlag = false, LevelFlag = true;
	int FoodCount = 0;

	Block food; // еда
	int levels = 1; // Уровень
	int speed = 150; // задержка в милесекундах

	char put = 0;
	do {
		char level[2]; level[0] = char(levels + 48); level[1] = 0;
		if(LevelFlag){
			char Mess[15] = "Level ";
			strcat(Mess, level); Mess[7] = 0;
			TextMessage(Mess);
			Sleep(1500);
			TextMessage(Mess, 0 , 0);
			LevelFlag = false;
		}
		if (!FoodFlag) {
			food = Food(snake);
			FoodFlag = true;
		}
		if (PosEqual(food, snake)) {
			++snake; 
			snake.Show();
			food = Food(snake);
			++FoodCount;
			if(FoodCount % 5 == 0)
				{levels++; LevelFlag = true;
				speed -= 10;   }
		}
		if (_kbhit()) {
			put = _getch();
			if (put == -32) put = _getch();
			switch (put) {
			case 72: snake.SetDir(1);
				break;
			case 80: snake.SetDir(2);
				break;
			case 77: snake.SetDir(3);
				break;
			case 75: snake.SetDir(4); 
				break;
			case 'p': case 'з': _getch();
				break;
			//case 'f': case 'а': Food();
			}
		}
		x = snake.GetX(); y = snake.GetY();
		if (x == 1 || x == fw-1 || y == 1 || y == fh-1 || snake.crash()) {
			put = 27; TextMessage("Game Over!"); _getch();
		}
		else {
			snake.Go();
			Sleep(speed);
		}
	} while (put != 27);
}

void TextMessage(char* t, int c1, int c2) {
	COORD point;
	int i, x = 31, y = 21, size = strlen(t);
	c1 = c1 >= 0 && c1 < 16? c1: 6;
	c2 = c2 >= 0 && c2 < 16 ? c2 : 4;
	point.X = x;
	point.Y = y;
	Block b(x-1, y-1, c1); b.SetSymb('*');
	for (i = 0; i < size + 2; ++i) {
		b.Show(); b.SetX(b.GetX() + 1);
	}
	b.SetBlock(x - 1, y + 1, c1);
	for (i = 0; i < size + 2; ++i) {
		b.Show(); b.SetX(b.GetX() + 1);
	}
	b.SetBlock(x - 1, y, c1); b.Show();
	b.SetBlock(x + size, y, c1); b.Show();

	SetConsoleCursorPosition(hOut, point);
	SetConsoleTextAttribute(hOut, (WORD)(c2));
	cout << t;
}

void Frame(int FrameColor, int FrameHeight, int FrameWidth) {
	Block b(1, 1, FrameColor); b.SetSymb(219);
	int i;
	for (i = 0; i < FrameWidth; ++i) {
		b.Show(); b.SetX(b.GetX() + 1);
	}
	b.SetBlock(1, 49, FrameColor);
	for (i = 0; i < FrameWidth; ++i) {
		b.Show(); b.SetX(b.GetX() + 1);
	}
	b.SetBlock(1, 2, FrameColor); b.SetSymb(219);
	for (i = 0; i < FrameHeight; ++i) {
		b.Show(); b.SetY(b.GetY() + 1);
	}
	b.SetBlock(79, 2, FrameColor);
	for (i = 0; i < FrameHeight; ++i) {
		b.Show(); b.SetY(b.GetY() + 1);
	}
}

Block Food(const Snake snake) {
	static tyb color = 0;
	static Block food;
	if (color == 0) {
		do{
			int x = 2 + rand() % 77;
			int y = 2 + rand() % 47;
			color = 6;
			food.SetBlock(x, y, color); 
		} while(snake.crash(food));
		food.Show(); return food;
	}
	else {
		color = 0;
		food.SetColor(0); food.Show();
		return Food(snake);
	}
}

#endif