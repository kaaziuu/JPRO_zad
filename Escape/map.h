#pragma oncce

#include "Player.h"
#include "Enemy.h"
#include "Room.h"
class Map
{
public:
	Map(int, int, Player&, Enemy*, int size);
	void draw(Enemy&, bool);
	void update(Player&, Enemy*, int size);
	int enemy_draw(Enemy*, int, int, int);
	char** map;
	int room_corner[4][3];
	char room_wall(int x, int y, bool* used_index);
	void move_player(Player&, int);
	bool is_player_move = true;
	int width;
	int height;

private:

	Room room[4];
	void room_generator();
};

