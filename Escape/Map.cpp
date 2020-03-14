#include "Map.h"

void Map::room_generator() {
	int max_x = 5;
	int max_y = 5;
	int start_x = 0;
	int start_y = 0;
	for (int i = 0; i < 4; i++) {
		start_x = (i % 2) * 10;
		start_y = (i / 2) * 10;
		int x = (rand() % max_x)+start_x;
		int y = (rand() % max_y)+start_y;
		if (x == 1 && y == 1) {
			x++;
		}
		int size = (rand() & 3)+3;
		this->room_corner[i][0] = x;
		this->room_corner[i][1] = y;
		this->room_corner[i][2] = size;
	}
}

char Map::is_room_wall(int x, int y) {
	for (int i = 0; i < 4; i++) {
		
	}
	return ' ';
}

Map::Map(int width, int height, Player& hero, Enemy* enemy_arr, int size) {
	this->width = width;
	this->height = height;
	room_generator();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char obj = is_room_wall(j, i);
			if (obj != ' ') {

			}
		}
	}
}

int Map::enemy_draw(Enemy* enemy_arr, int size, int x, int y) {

	for (int i = 0; i < size; i++) {
		if (x == enemy_arr[i].x_pos && y == enemy_arr[i].y_pos) {
			return i;
		}
	}

	return -1;
}

void Map::update(Player& hero, Enemy* enemy_arr, int size) {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			int index_en = enemy_draw(enemy_arr, size, j, i);
			if (index_en != -1) {
				this->map[i][j] = enemy_arr[index_en].look;
				continue;
			}
			if (i == 0 || i == this->height - 1) {
				this->map[i][j] = '/';
			
			}
			else if (j == 0 || j == this->width - 1) {
				this->map[i][j] = '|';
			}
			else if (i == hero.y_pos && j == hero.x_pos) {
				this->map[i][j] = hero.look;
			}
			else {
				this->map[i][j] = ' ';
			}
		}
	}
	draw();
	hero.stats();
}

void Map::draw() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			std::cout << this->map[i][j];
		}
		std::cout << std::endl;
	}
}

