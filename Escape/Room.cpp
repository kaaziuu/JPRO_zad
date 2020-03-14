#include "Room.h"

void Room::init(int start_x, int start_y) {
	// maksymalna pocz¹tkowa warotoœæ na danej pozycji 
	int max_x = 5;
	int max_y = 5;
	//start_x = (i % 2) * 10;
	//start_y = (i / 2)* 10;
	int x = (rand() % max_x) + start_x;
	int y = (rand() % max_y) + start_y;
	if (x == 1 && y == 1) {
		x++;
	}
	int size = (rand() & 3) + 5;
	this->x_start = x;
	this->y_start = y;
	this->size = size;
}