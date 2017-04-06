#include "Block.h"

namespace SNAKE {

HANDLE Block::hOut = 0;

               /**********ÐÅÀËÈÇÀÖÈß ÊËÀÑÑÀ ÁËÎÊ*************/
Block::Block(int x, int y, tyb color)
{
	FDir = 3; // 1 - up, 2 - down, 3 - right, 4 - left
	symb = (char)219;
	CreatHOut();
	SetBlock(x, y, color);
}

void Block::SetPos(int x, int y){
	SetX(x); SetY(y);
}

void Block::SetX(int x){
	Fx = x > 0 && x < 80? x: 1;
}

void Block::SetY(int y){
	Fy = y > 0 && y < 50? y: 1;
}

void Block::SetColor(int color){
	FColor = color >= 0 && color < 16? color: 1;
}

void Block::SetBlock(int x, int y, int color){
	SetX(x); SetY(y); SetColor(color);
}

void Block::Show(){
	COORD point;
	point.X = Fx;
	point.Y = Fy;
	SetConsoleCursorPosition(hOut, point);
	SetConsoleTextAttribute(hOut, (WORD)(FColor));
	printf("%c", symb);
}

void Block::Hide() {
	int c = GetColor();
	SetColor(0);
	Show(); SetColor(c);
}

void Block::SetSymb(char s){
	symb = s > 0 && s < 255? s: (char)219;
}

                                 /**********ÐÅÀËÈÇÀÖÈß ÊËÀÑÑÀ ÇÌÅÉÊÀ*************/

Snake::Snake(tyb size, tyb color)
: FSize(size>0&&size<100? size: 5),
FColor(color>0&&color<16? color: 1),
FBlock(15, 15, FColor)
{
	for(int i = 0; i < FSize; ++i){
		FSnake.push_back(FBlock);
		FSnake[i].SetX(FSnake[i].GetX() - i);
	}
	FSnake[0].SetSymb('@');
	FDir = FSnake[0].GetDir();
}
void Snake::Show(){
	for(int i = 0; i < FSize; ++i){
		FSnake[i].Show();
	}
}

void Snake::SetDir(short d){
	if (d > 0 && d < 5) {
		if(FDir == 1 || FDir == 2)
			FDir = (d == 3 || d == 4) ? d : FDir;
		if(FDir == 3 || FDir == 4)
			FDir = (d == 1 || d == 2) ? d : FDir;
	}
}

void Snake::Go(){
	int x, y, xx, yy;
	int size = FSnake.size();
	FSnake[size - 1].Hide();
	for(int i = 0; i < size; ++i){
		if(i == 0){
			x = FSnake[i].GetX(); y = FSnake[i].GetY();
			if(FDir == 1)FSnake[i].SetY(y > 1 ? y-1 : y);
			if(FDir == 2)FSnake[i].SetY(y < 50 ? y+1 : y);
			if(FDir == 3)FSnake[i].SetX(x < 80 ? x+1 : x);
			if(FDir == 4)FSnake[i].SetX(x > 1 ? x-1 : x);
		}
		else{
			xx = FSnake[i].GetX(); yy = FSnake[i].GetY();
			FSnake[i].SetX(x); FSnake[i].SetY(y);
			x = xx; y = yy;
		}
	}
	FBlock.SetBlock(x, y, FColor);
	Show();
}


bool Snake::crash() const{
	if(FSize >= 4)
		for (int i = 4; i < FSize; ++i) {
			if (PosEqual(FSnake[0], FSnake[i])) return true;
		}
	return false;
}

bool Snake::crash(Block b) const{
	for (int i = 0; i < FSize; ++i) {
		if (PosEqual(b, FSnake[i])) return true;
	}
	return false;
}

void Snake::operator++() {
	FSnake.push_back(FBlock);
	FSize++;
}

}