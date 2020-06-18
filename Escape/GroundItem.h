#pragma once
#include "Game_item.h"
class GroundItem : public Game_item
{
public:

	int pos_x;
	int pos_y;
	char look = 'I';
	bool isactive = true;
	void show();
	void init(std::string name, int attack, int defense, bool is_protect, int x, int y);
};



