#include "Map.h"

void Map::room_generator()
{
	for (int i = 0; i < 4; i++) {
		int start_x = (i % 2) * 20;
		int start_y = (i / 2) * 10;
		this->room[i].init(start_x, start_y);
	}
}

char Map::is_room_wall(int x, int y) {
	for (int i = 0; i < 4; i++) {
		const int size = room[i].size;
		const int x_start = room[i].x_start;
		const int y_start = room[i].y_start;
		if ((x == x_start || x == x_start + size) && (y >= y_start && y <= y_start + size)) {
			return '|';
		}
		if ((y == y_start || y == y_start + size) && (x > x_start&& x < x_start + size)) {
			return '/';
		}
	}
	return ' ';
}


Map::Map(int width, int height, Player& hero, Enemy* enemy_arr, int size) {
	this->width = width;
	this->height = height;
	this->room_generator();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char obj = is_room_wall(j, i);
			if (i == 0 || i == this->height - 1) {
				std::cout << '/';
			}
			else if (j == 0 || j == this->width - 1) {
				std::cout << "|";
			}
			else {
				char ch = is_room_wall(j, i);
				if (ch != ' ') {
					std::cout << ch;
				}
				else {
					if (hero.x_pos == j && hero.y_pos == i) {
						std::cout << hero.look;
					}
					else if (int index = enemy_draw(enemy_arr, size, j, i) != -1) {
						std::cout << enemy_arr[index].look;
					}
					else {
						std::cout << " ";
					}
				}
			}
		}
		std::cout << std::endl;

	}
	hero.stats();
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

