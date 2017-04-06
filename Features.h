#ifndef FEATURES_H
#define FEATURES_H

#include "Block.h"
#include "Game.h"
#include <cstdlib>
using namespace std;
using namespace SNAKE;

void Partitions(int H, int W, Snake S, int l); // Создает препядствия в рамке HxW















void Partitions(int H, int W, Snake S, int l){
	H-=3; W-=3;
	int size = 1 + rand() % 10;
	int x = 2 + rand() % W, y = 2 + rand() % H;
	
}


#endif









