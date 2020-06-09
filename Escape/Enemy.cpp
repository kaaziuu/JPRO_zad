#include "Enemy.h"

void Enemy::init(int x, int y, int id) {
	this->x_pos = x;
	this->y_pos = y;
	this->id = id;
	this->is_focus = false;
	this->health = 5;
	this->power = 2;
	this->defense = 1;
	this->behavior = rand() % 3;
	
}

// patrol state
void Enemy::patrol_state(char** map) {
	int direct = rand() % 4;
	int start_direct = direct;
	//random movment of enemy, enemy alway will be move if one og direct is bloced enemy will be to other
	do
	{
		if (direct == 0) {
			char target = map[this->y_pos - 1][this->x_pos];
			if (target == ' ' || target == 'd') {
				this->y_pos--;
				break;
			}
		}
		else if (direct == 1) {
			char target = map[this->y_pos + 1][this->x_pos];
			if (target == ' ' || target == 'd') {
				this->y_pos++;
				break;
			}
		}
		else if (direct == 2) {
			char target = map[this->y_pos][this->x_pos + 1];
			if (target == ' ' || target == 'd') {
				this->x_pos++;
				break;
			}
		}
		else if (direct == 3) {
			char target = map[this->y_pos][this->x_pos - 1];
			if (target == ' ' || target == 'd') {
				this->x_pos--;
				break;
			}
		}
		else {
			if (direct > 3) {
				direct = 0;
			}
		}
		direct++;
		if (direct == start_direct) {
			break;
		}

	} while (true);

}

int Enemy::scary(char** map, int player_pos[2])
{
	if (this->current_point > 0) {
		if (this->x_pos == player_pos[0] && (abs(player_pos[1] - this->y_pos) == 1)) {
			return this->power;
		}
		else if (this->y_pos == player_pos[1] && (abs(player_pos[0] - this->x_pos) == 1)) {
			return this->power;
		}
		else {
			if (this->y_pos >= player_pos[1] && map[this->y_pos + 1][this->x_pos] == ' ') {
				this->y_pos++;
			}
			else if (this->y_pos < player_pos[1] && map[this->y_pos - 1][this->x_pos] == ' ') {
				this->y_pos--;
			}
			else if (this->x_pos >= player_pos[0] && map[this->y_pos][this->x_pos + 1] == ' ') {
				this->x_pos++;
			}
			else if (this->x_pos < player_pos[0] && map[this->y_pos][this->x_pos - 1] == ' ') {
				this->x_pos--;
			}
		}

	}


	return 0;;
}

int Enemy::aggressive(char** map, int player_pos[2])
{
	if (this->current_point > 0) {
		if (this->x_pos == player_pos[0] && (abs(player_pos[1] - this->y_pos) == 1)) {
			return this->power;
		}
		else if (this->y_pos == player_pos[1] && (abs(player_pos[0] - this->x_pos) == 1)) {
			return this->power;
		}
		else {
			if (this->y_pos > player_pos[1] && map[this->y_pos - 1][this->x_pos] == ' ') {
				this->y_pos--;
			}
			else if (this->y_pos < player_pos[1] && map[this->y_pos + 1][this->x_pos] == ' ') {
				this->y_pos++;
			}
			else if (this->x_pos > player_pos[0] && map[this->y_pos][this->x_pos - 1] == ' ') {
				this->x_pos--;
			}
			else if (this->x_pos < player_pos[0] && map[this->y_pos][this->x_pos + 1] == ' ') {
				this->x_pos++;
			}
		}

	}


	return 0;
}

void Enemy::close_compan(int* compan_pos, char** map) {
	int map_height = (sizeof(map) / sizeof(*map));
	int map_width = (sizeof(*map) / sizeof(**map));
	int current_square_size = 3;
	bool is_find = true;
	int lock_lx = -1;
	int lock_rx = -1;
	int lock_dy = -1;
	int lock_ty = -1;
	while (!is_find)
	{
		int s_x;
		int s_y;
		int e_x;
		int e_y;
		if (lock_lx != -1) {
			s_x = lock_lx;
		}
		else {
			s_x = this->x_pos - (current_square_size / 2);
		}
		if (lock_ty != -1) {
			s_y = this->y_pos - (current_square_size / 2);
		}
		if (s_x < 0) {
			s_x = 0;
		}
		if (s_y < 0) {
			s_y = 0;
		}
		if (lock_rx != -1) {
			e_x = lock_rx;
		}
		else {
			e_x = this->x_pos + (current_square_size / 2);
		}
		if (lock_dy != -1) {
			e_y = lock_dy;
		}
		else
		{
			e_y = this->y_pos + (current_square_size / 2);
		}
		if (e_x >= map_width) {
			e_x = map_width - 1;
		}
		if (e_y >= map_height) {
			e_y = map_height - 1;
		}


		for (s_y; s_y <= e_y; s_y++) {
			for (s_x; s_x <= e_x; s_x++) {
				if (map[s_y][s_x] == '/') {
					if (s_y > this->y_pos) {
						lock_dy = s_y;
					}
					else {
						lock_ty = s_y;
					}
				}
				if (map[s_y][s_x] == '|') {
					if (s_x < this->x_pos) {
						lock_lx = s_x;
					}
					else {
						lock_rx = s_x;
					}
				}

				if (map[s_y][s_x] == 'o' || map[s_y][s_x] == 'x' || map[s_y][s_x] == 'X') {
					compan_pos[0] = s_x;
					compan_pos[1] = s_y;
					is_find = true;
				}
			}
		}
		if (current_square_size >= 7) {
			break;
		}
		else {
			current_square_size += 2;
		}
	
	}


}

int Enemy::tatician(char** map, int player_pos[2])
{
	int to_return = 0;
	if (this->current_point > 0) {
		int compan_pos[2] = { -1, -1 };
		int* pointer_compan_pos = compan_pos;
		close_compan(pointer_compan_pos, map);
		if (pointer_compan_pos[0] != -1) {
			float target_vector[2] = { this->x_pos - pointer_compan_pos[0], this->y_pos - pointer_compan_pos[1] };
			float distanse = sqrt(powf(target_vector[0], 2) + powf(target_vector[1], 2));
			if (distanse < 2) {
				if (this->x_pos == player_pos[0] && (abs(player_pos[1] - this->y_pos) == 1)) {
					return this->power;
				}
				else if (this->y_pos == player_pos[1] && (abs(player_pos[0] - this->x_pos) == 1)) {
					return this->power;
				}
				else {
					this->current_point++;
					return 0;
				}
			}
			else {
				if (this->y_pos > pointer_compan_pos[1] && map[this->y_pos - 1][this->x_pos] == ' ') {
					this->y_pos--;
				}
				else if (this->y_pos < pointer_compan_pos[1] && map[this->y_pos + 1][this->x_pos] == ' ') {
					this->y_pos++;
				}
				else if (this->x_pos > pointer_compan_pos[0] && map[this->y_pos][this->x_pos - 1] == ' ') {
					this->x_pos--;
				}
				else if (this->x_pos < pointer_compan_pos[0] && map[this->y_pos][this->x_pos + 1] == ' ') {
					this->x_pos++;
				}
			}
		}
		else {
			to_return = this->aggressive(map, player_pos);
		}

	}


	return to_return;
}



bool Enemy::update(char **map, int player_pos[]) {
	if (this->current_state == dead) {
		this->look = 'm';
		return false;
	}

	float target_vector[2] = { this->x_pos - player_pos[0], this->y_pos - player_pos[1] };
	float distanse = sqrtf(powf(target_vector[0], 2) + powf(target_vector[1], 2));
	bool is_wall = false;

	if(this->range_see >= distanse){
		int x = this->x_pos;
		int y = this->y_pos;
		while (x  != player_pos[0] || y != player_pos[1])
		{
			char check_point = map[y][x];
			if (check_point == 'd' || check_point == '|' || check_point == '/') {
				is_wall = true;
				break;
			}
			if (x != player_pos[0]) {
				if (x > player_pos[0]){ x--; }
				else { x++; }
			}
			if (y != player_pos[1]) {
				if (y > player_pos[1]) { y--; }
				else { y++; }
			}
		}
//		int tmp = 2;
	}

	if (distanse <= this->range_see && this->current_state==patrol && !is_wall) {
		if (this->is_focus)this->look = 'X';
		else this->look = 'x';
		this->current_state = attact;
	}
	else if (distanse > this->range_see&& this->current_state == attact) {
		this->look = 'o';
		this->current_state = patrol;
	}

	if (this->current_state == patrol) {
		this->patrol_state(map);
		return false;
	}
	else if (this->current_state == attact) {
		if (this->is_focus)this->look = 'X';
		else this->look = 'x';
	}
	else return true;


}


