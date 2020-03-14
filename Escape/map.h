#pragma oncce

#include "Player.h"
#include "Enemy.h"
class Map
{
public:
	Map(int, int, Player&, Enemy*, int size);
	void draw();
	void update(Player&, Enemy*, int);
	int enemy_draw(Enemy*, int, int, int);
	char map[20][40];
	int room_corner[4][3];
	char is_room_wall(int x, int y);
	void room_generator();
private:
	int width;
	int height;
	void room_generator();
};

