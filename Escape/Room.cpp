#include "Room.h"

Room::Room() {
	int max_x = 5;
	int max_y = 5;
	int start_x = 0;
	int start_y = 0;
	for (int i = 0; i < 4; i++) {
		start_x = (i % 2) * 10;
		start_y = (i / 2) * 10;
		int x = (rand() % max_x) + start_x;
		int y = (rand() % max_y) + start_y;
		if (x == 1 && y == 1) {
			x++;
		}
		int size = (rand() & 3) + 3;
		this->x_start = x;
		this->y_start = y;
		this->size = size;
	}
}