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

	void init(int, int, int);
	//o-nie widzi nas, x-atakuje nas, m-martewy, X-focus
	char look = 'o';
	int id;
	bool is_hidden = false;
	bool is_focus = false;
	state current_state = patrol;
	bool update(char **map, int player_pos[]);
	void patrol_state(char **map);
	int behavior;
	int scary(char** map, int player_pos[2]);
	int aggressive(char** map, int player_pos[2]);
	int tatician(char** map, int player_pos[2]);
protected:
	int range_see = 4;
	void close_compan(int*, char**);
};
