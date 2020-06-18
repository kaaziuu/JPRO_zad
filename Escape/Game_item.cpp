#include "Game_item.h"

Game_item::Game_item(std::string name = NULL, int attack = NULL, int defense = NULL , bool is_protect=NULL)
{
	this->attack = attack;
	this->name = name;
	this->defense = defense;
	this->is_protect = is_protect;
	this->is_ranged = false;
}

Game_item::Game_item()
{
}

Game_item::~Game_item()
{
}
