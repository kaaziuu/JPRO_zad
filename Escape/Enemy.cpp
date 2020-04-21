#include "Enemy.h"

void Enemy::init(int x, int y) {
	this->x_pos = x;
	this->y_pos = y;
}

// patrol state
void Enemy::patrol_state(char map[20][40]) {
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
void Enemy::attact_state(char map[20][40], int player_pos[2]) {
	std::cout << "enemy attact mode";
}

void Enemy::update(char map[20][40], int player_pos[]) {
	std::cout << player_pos[0];
	//int x_check = player_pos[0];
	//std::cout << std::endl  << x_check;

	float target_vector[2] = { this->x_pos - player_pos[0], this->y_pos - player_pos[1] };
	float distanse = sqrtf(powf(target_vector[0], 2) + powf(target_vector[1], 2));
	bool is_wall = false;

	if(range_see < distanse){
		int x = this->x_pos;
		int y = this->y_pos;
		while (x  != player_pos[0] && y != player_pos[1])
		{
			char check_point = map[y][x];
			if (check_point == 'd' || check_point == '|' || check_point == '/') {
				is_wall == true;
				break;
			}
			if (x != player_pos[0]) {
				(x > player_pos[0]) ? x-- : x++;
			}
			if (y != player_pos[1]) {
				(y > player_pos[1]) ? y-- : y++;
			}
		}
	}

	if (distanse <= this->range_see && this->current_state==patrol && !is_wall) {
		this->look = 'x';
		this->current_state = attact;
	}
	else if (distanse > this->range_see&& this->current_state == attact) {
		this->look = 'o';
		this->current_state = patrol;
	}

	if (this->current_state == patrol) {
		this->patrol_state(map);
	}

	

}


