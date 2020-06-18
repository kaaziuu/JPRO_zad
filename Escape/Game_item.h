#pragma once
#include <iostream>
class Game_item
{
public:
    std::string  name = "brak";
    bool is_ranged = false;
    bool is_protect = false;
    float attack = 0;
    float defense = 0;
    float distance = 0;
    void getName();

	Game_item(std::string name, int attack, int defense, bool is_protect);
    Game_item();
	~Game_item();
};
