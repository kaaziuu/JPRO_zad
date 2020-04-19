#pragma once
#include "Person.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>


enum state
{
	patrol,
	attact,
	dead
};
class Enemy : public Person {
public:

	void init(int, int);
	//o-nie widzi nas, x-atakuje nas, m-martewy
	char look = 'o';
	bool is_hidden = false;
	state current_state = patrol;
	void update(char map[20][40], int player_pos[]);
	void patrol_state(char map[20][40]);
	void attact_state(char map[20][40], int player_pos[2]);

protected:
	int range_see = 3;
};
