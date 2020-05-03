#include "Enemy.h"

void Enemy::init(int x, int y, int id) {
	this->x_pos = x;
	this->y_pos = y;
	this->id = id;
	this->is_focus = false;
	this->health = 5;
	this->power = 2;
	this->defense = 1;
}

// patrol state
void Enemy::patrol_state(char **map) {
	int direct = rand() % 4;
	int start_direct = direct;
	//random movment of enemy, enemy alway will be move if one og direct is bloced enemy will be to other
	do
	{
		if (direct == 0) {
			char target = map[this->y_pos-1][this->x_pos];
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
			char target = map[this->y_pos][this->x_pos+1];
			if (target == ' ' || target == 'd') {
				this->x_pos++;
				break;
			}
		}
		else if (direct == 3) {
			char target = map[this->y_pos][this->x_pos-1];
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

// attact state TODO
void Enemy::attact_state(char **map, int player_pos[2]) {
	std::cout << "enemy attact mode";
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
		int tmp = 2;
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


