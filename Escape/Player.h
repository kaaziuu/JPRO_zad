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
    Game_item* back;
    int backsize =4 ;
    Player(int, int, bool = false);
    ~Player();
    const char look = '#';
    bool is_fight = false;
    void stats();
    void attack(Enemy& to_attack, char **map);
    void take_hit(int demage);
    void readData(int, int, int, std::string[]);
    void pickup(Game_item& new_item, int slot);
};

