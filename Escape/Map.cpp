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


Map::Map(int width, int height, Player& hero, Enemy* enemy_arr, int size, bool generate) {
	this->width = width;
	this->height = height;
	if (generate) {
		this->room_generator();
	}
	if (this->height < 20) {
		this->height = 20;
	}
	if (this->width < 40) {
		this->width = 40;
	}

	this->map = new char* [this->height];
	for (int i = 0; i < this->height; i++) {
		this->map[i] = new char[this->width];
	}
	if (generate) {
		update(hero, enemy_arr, size);
	}

}

Map::~Map()
{
	for (int i = 0; i < this->height; i++) {
		delete[] this->map[i];
	}
	delete[] this->map;
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
	bool used_index[4] = { false, false, false, false }; 
	Enemy focus;
	bool is_focus = false;
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			char ch = room_wall(j, i, used_index);
			int index = enemy_draw(enemy_arr, size, j, i);
		
			if (ch == 'd') {
				this->map[i][j] = 'd';
				if (index != -1) {
					enemy_arr[index].is_hidden = true;
				}
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
					if (index != -1) {
						enemy_arr[index].is_hidden = true;
					}
				}
				else {
					if (hero.x_pos == j && hero.y_pos == i) {
						this->map[i][j] = hero.look;
					}
					else if (index != -1) {
						
						this->map[i][j] = enemy_arr[index].look;
						if (enemy_arr[index].is_focus) {
							focus = enemy_arr[index];
							is_focus = true;
						}
					}
					else {
						this->map[i][j] = ' ';
					}
				}
			}
		}
	}
	draw(focus, is_focus);
	hero.stats();
}

// metoda odpowiedzalna za rysowanie mapy
void Map::draw(Enemy& fcs, bool is_focus) {
	
	system("cls");
	for (int i = 0; i < this->height; i++) {
		std::cout << "\t\t\t";
		for (int j = 0; j < this->width; j++) {
			std::cout << this->map[i][j];
			
			
		}
		if (is_focus && i < 5) {
			std::cout << "\t\t";
			if (i == 0) std::cout << "Przeciwnik ";
			if (i == 1) std::cout << "ID: " << fcs.id;
			if (i == 2) std::cout << "Zdrowie: " << fcs.health;
			if (i == 3) std::cout << "sila: " << fcs.power;
			if (i == 4) std::cout << "obrona: " << fcs.defense;
		}
		std::cout << std::endl;
	}
}


// metoda odpowiedzialna za poruszanie sie gracza
void Map::move_player(Player& hero, int direction) {
	int y = hero.y_pos;
	int x = hero.x_pos;
	if (direction == 0) {
		char target = this->map[y - 1][x];
		if (target == ' ' || target == 'd') {
			hero.y_pos--;
		}
	}
	else if (direction == 1) {
		char target = this->map[y + 1][x];
		if (target == ' ' || target == 'd') {
			hero.y_pos++;
		}
	}
	else if (direction == 2) {
		char target = this->map[y][x + 1];
		if (target == ' ' || target == 'd') {
			hero.x_pos++;
		}
	}
	else if (direction == 3) {
		char target = this->map[y][x - 1];
		if (target == ' '|| target=='d' ) {
			hero.x_pos--;
		}
	}

}

void Map::loadRoom(int x, int y, int size, int index)
{
	this->room[index].x_door_pos = 2;
	this->room[index].x_start = x;
	this->room[index].y_start = y;
	this->room[index].size = size;
}



