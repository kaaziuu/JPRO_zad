#pragma once
#include <iostream>
#include "Game_item.h"
#include "Person.h"
class Player : public Person
{
public:
    std::string name;
    Game_item back[4];
    Player(int, int);
    const int max_back = 4;
    const char look = '#';
    void stats();
};

