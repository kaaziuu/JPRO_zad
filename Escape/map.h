#pragma oncce

#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "GroundItem.h"
class Map
{
public:
	Map(int, int, Player&, Enemy*, int size, bool=true);
	~Map();
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
	int ct_item = 4;
	void loadRoom(int x, int y, int size, int index);
	Room room[4];
	GroundItem groundItem[4];
	GroundItem* ItemAround(Player& hero);


private:
	void room_generator();
};

