#include "GroundItem.h"

void GroundItem::init(std::string name, int attack, int defense, bool is_protect, int x, int y)
{
	this->attack = attack;
	this->name = name;
	this->defense = defense;
	this->is_protect = is_protect;
	this->is_ranged = false;
	this->pos_x = x;
	this->pos_y = y;
	this->look = 'I';
	
}
