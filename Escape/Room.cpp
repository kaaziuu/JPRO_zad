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
	if (x < 1 && y == 1) {
		y++;
	}
	int size = (rand() % 3) +4;
	this->x_start = x;
	this->y_start = y;
	this->x_door_pos = 2;
	this->size = size;
}