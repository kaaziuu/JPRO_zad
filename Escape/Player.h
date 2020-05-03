#pragma once
#include <iostream>
#include "Game_item.h"
#include "Person.h"
#include "Enemy.h"
//#include "map.h"

class Player : public Person
{
public:
    std::string name;
    Game_item back[4];
    Player(int, int);
    const int max_back = 4;
    const char look = '#';
    bool is_fight = false;
    void stats();
    void attack(Enemy& to_attack, char **map);
};

