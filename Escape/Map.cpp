#include "Map.h"

void Map::room_generator()
{
	for (int i = 0; i < 4; i++) {
		int start_x = (i % 2) * 20;
		int start_y = (i / 2) * 12;
		this->room[i].init(start_x, start_y);
	}
}

char Map::room_wall(int x, int y, bool* used_index) {
	for (int i = 0; i < 4; i++) {
		const int size = room[i].size;
		const int x_start = room[i].x_start;
		const int y_start = room[i].y_start;
		if (i == 1) {
			room[i].x_door_pos;
		//	std::cout << room[i].x_door_pos;
		}
		if ((x == x_start || x == x_start + size) && (y >= y_start && y <= y_start + size)) {
			return '|';
		}
		if ((y == y_start || y == y_start + size) && (x > x_start&& x < x_start + size)) {
			int i_x = x - x_start;
			if ((i_x) == room[i].x_door_pos && i<=1 && y==y_start+size) {
				return 'd';
			}
			else if ((i_x) == room[i].x_door_pos && i > 1 && y == y_start) {
				return 'd';
			}
			return '/';
		}
	}
	return ' ';
}


Map::Map(int width, int height, Player& hero, Enemy* enemy_arr, int size) {
	this->width = width;
	this->height = height;
	this->room_generator();
	update(hero, enemy_arr, size);

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
	bool used_index[4] = {false, false, false, false};
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			char ch = room_wall(j, i, used_index);
		
			if (ch == 'd') {
				this->map[i][j] = 'd';
				continue;
			}
			if (i == 0 || i == this->height - 1) {
				this->map[i][j] = '/';
			}
			else if (j == 0 || j == this->width - 1) {
				this->map[i][j] = '|';
			}
			else {
				if (ch != ' ') {
					this->map[i][j] = ch;
				}
				else {
					if (hero.x_pos == j && hero.y_pos == i) {
						this->map[i][j] = hero.look;
					}
					else if (int index = enemy_draw(enemy_arr, size, j, i) != -1) {
						this->map[i][j] = enemy_arr[index].look;
					}
					else {
						this->map[i][j] = ' ';
					}
				}
			}
		}
	}
	draw();
	hero.stats();
}

void Map::draw() {
	system("cls");
	for (int i = 0; i < this->height; i++) {
		std::cout << "\t\t\t";
		for (int j = 0; j < this->width; j++) {
			std::cout << this->map[i][j];
		}
		std::cout << std::endl;
	}
}

