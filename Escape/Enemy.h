#pragma once
#include "Person.h"
enum state
{
	patrol,
	attact,
	dead
};
class Enemy : public Person{
public:

	void init(int, int);
	//o-nie widzi nas, x-atakuje nas, m-martewy
	char look = 'o';
	state current_state = patrol;




};

