#pragma oncce

#include "Player.h"
#include "Enemy.h"
#include "Room.h"
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
private:
	int width;
	int height;
	Room room[4];
	void room_generator();
};

