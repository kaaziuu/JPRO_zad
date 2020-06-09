// Escape.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>

#include <Windows.h>
#include <time.h>
#include "Player.h"
#include "map.h"
#include "Game_item.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int size = 10;
Enemy enemy_arr[size];




bool is_reapet_enemy(int* x_pos, int* y_pos, int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (x_pos[i] == x && y_pos[j] == y) {
                return true;
            }
        }
    }
    return false;
}

void save(Map& map, Player& player, int x, int y) {
    std::ofstream  player_Data;
    player_Data.open("player.txt");
    player_Data << player.x_pos << "\n";
    player_Data << player.y_pos << "\n";
    player_Data << player.health << "\n";
    player_Data << player.power << "\n";
    player_Data << player.defense << "\n";
    player_Data.close();

    std::ofstream enemy_data;
    enemy_data.open("enemy.txt");
    for (int i = 0; i < size; i++) {
        enemy_data << enemy_arr[i].x_pos << "\n";
        enemy_data << enemy_arr[i].y_pos << "\n";
        enemy_data << enemy_arr[i].health << "\n";
        enemy_data << enemy_arr[i].power << "\n";
        enemy_data << enemy_arr[i].defense << "\n";
    }
    enemy_data.close();
    
    std::ofstream mapData;
    mapData.open("map.txt");
    for (int i = 0; i < 4; i++){
        mapData << map.room[i].x_start << "\n";
        mapData << map.room[i].y_start << "\n";
        mapData << map.room[i].size << "\n";
    }

    mapData.close();
    mapData.open("mapData.txt");
    mapData << map.width << "\n";
    mapData << map.height;
    mapData.close();
}

void generate_enemy() {
    Enemy enemy_arr[size];
    int x_pos[size];
    int y_pos[size];

    // enemy postion genarton
    for (int i = 0; i < size; i++) {
        int x = (rand() % 37) + 2;
        int y = (rand() % 17) + 2;
        if (is_reapet_enemy(x_pos, y_pos, size, x, y)) {
            i--;
            continue;
        }
        enemy_arr[i].init(x, y, i);
    }
}

Map * level(Player& hero) {
    int x_pos[size];
    int y_pos[size];
    
    // enemy postion genarton
    for (int i = 0; i < size; i++) {
        int x = (rand() % 37) + 2;
        int y = (rand() % 17) + 2;
        if (is_reapet_enemy(x_pos, y_pos, size, x, y)) {
            i--;
            continue;
        }
        enemy_arr[i].init(x, y, i);
    }

    Map * map = new Map(40, 20, hero, enemy_arr, size);
  
    return map;
}

void player_movment(Map& map, Player& hero, bool *isplay) {
    if (GetAsyncKeyState(VK_UP)) {
        map.move_player(hero, 0);
    }
    else if (GetAsyncKeyState(VK_DOWN)) {
        map.move_player(hero, 1);

    }
    else if (GetAsyncKeyState(VK_RIGHT)) {
        map.move_player(hero, 2);

    }
    else if (GetAsyncKeyState(VK_LEFT)) {
        map.move_player(hero, 3);

    }

    if (GetAsyncKeyState(VK_DELETE)) {
        save(map, hero, map.width, map.height);
        *isplay = false;
    }
    if (GetAsyncKeyState(VK_F1)) {
        GroundItem* pick_up_item = map.ItemAround(hero);
        if (pick_up_item) {
            Game_item* item = new Game_item(pick_up_item->name, pick_up_item->attack, pick_up_item->defense, pick_up_item->is_protect);
            hero.pickup(*item, 0);
        }
    }
    


}



void player_fight(Map& map, Player& player, int* onfocus) {
    if (GetAsyncKeyState(VK_TAB)) {
        if (player.is_fight) {
            int i = (*onfocus) + 1;
            while (i != *onfocus)
            {
                if (enemy_arr[i].current_state == attact) {
                    enemy_arr[*onfocus].is_focus = false;
                    *onfocus = i;
                    enemy_arr[i].is_focus = true;
                    break;

                }
                i++;
                if (i >= size) {
                    i = 0;
                }

            }
        }
    }
    if (GetAsyncKeyState(VK_LCONTROL)) {
        player.attack(enemy_arr[*onfocus], map.map);
    }
    else if (GetAsyncKeyState(VK_UP)) {
        map.move_player(player, 0);
        player.current_point--;
    }
    else if (GetAsyncKeyState(VK_DOWN)) {
        map.move_player(player, 1);
        player.current_point--;
    }
    else if (GetAsyncKeyState(VK_RIGHT)) {
        map.move_player(player, 2);
        player.current_point--;
        
    }
    else if (GetAsyncKeyState(VK_LEFT)) {
        map.move_player(player, 3);
        player.current_point--;

    }
}

void enemy_logic(char** map, Player& hero) {
    int player_pos[2] = { hero.x_pos, hero.y_pos };
    bool to_fight = false;
    int counter = 0;
    for (int i = 0; i < size; i++) {

        if (!enemy_arr[i].is_hidden && enemy_arr[i].current_state != dead) {
            bool tmp = enemy_arr[i].update(map, player_pos);
            if (!to_fight && tmp != to_fight)
                to_fight = tmp;
            if (tmp) counter++;
        
        }
    }
    hero.is_fight = to_fight;
}

int aggressive_enemy(char** map, int player_pos[2], Enemy& enemy) {
    return enemy.aggressive(map, player_pos);
}
int tactisc_enemy(char** map, int player_pos[2], Enemy& enemy) {
    return enemy.tatician(map, player_pos);
}
int scary_enemy(char** map, int player_pos[2], Enemy& enemy) {
    return enemy.scary(map, player_pos);
}


// main loop
void main_loop(Player& hero, Map& map) {
    bool is_play = true;
    float time_deley = 0.2;
    float delta_time=2000;
    int* pointer_onfocus;
    int onfocus = -1;
    pointer_onfocus = &onfocus;
    time_t old_time= 0;
    time_t current_time = 0;
       
    int(*enemy_attack_point[])(char**, int[2], Enemy&) = {aggressive_enemy, tactisc_enemy, scary_enemy};

    while (is_play)
    {
        old_time = current_time;
        current_time = time(NULL);
        delta_time += current_time - old_time;
        if (delta_time > time_deley && !hero.is_fight){ 
            if (*pointer_onfocus != -1) {
                enemy_arr[onfocus].is_focus = false;
                *pointer_onfocus = -1;
                if (hero.move_point != hero.current_point) {
                    hero.current_point = hero.move_point;
                }
            }
        
            delta_time = 0;
            // player movment
            player_movment(map, hero, &is_play);
            enemy_logic(map.map, hero);
            map.update(hero, enemy_arr, size);
        }
        // fight mode
        else if (delta_time > time_deley && hero.is_fight) {
            if (*pointer_onfocus == -1) {
                for (int i = 0; i < size; i++) {
                    if (enemy_arr[i].current_state = attact) {
                        *pointer_onfocus = i;
                        enemy_arr[i].is_focus = true;
                        break;
                    }
                }
            }
            delta_time = 0;
            //player_movment(map, hero);
            if (map.is_player_move) {
                player_fight(map, hero, pointer_onfocus);
                if (hero.current_point == 0) {
                    map.is_player_move = false;
                    hero.current_point = hero.move_point;
                }
            }
            else {
                int player_pos[2] = { hero.x_pos, hero.y_pos };
                int hit_point = 0;
                bool next_player = false;
                int point_sum = 0;
                for (int i = 0; i < size; i++) {
                    if (enemy_arr[i].current_state == attact) {
                        hit_point -= (*enemy_attack_point[enemy_arr[i].behavior])(map.map, player_pos, enemy_arr[i]);
                        point_sum += (--enemy_arr[i].current_point);
                    }
                }
                std::cout << point_sum;
                hero.take_hit(hit_point);
                
                if (point_sum == 0) {
                    for (int i = 0; i < size; i++) {
                        if (enemy_arr[i].current_point != enemy_arr[i].move_point) {
                            enemy_arr[i].current_point = enemy_arr[i].move_point;
                        }
                    }
                    map.is_player_move = true;
                }
            }
            enemy_logic(map.map, hero);
            map.update(hero, enemy_arr, size);


        }
        

    }

    
}


int main() {
    srand(time(0));
    int choose;
    bool is_good = false;
    while (!is_good) {
        system("CLS");
       
        std::cout << "Witam w grze The Escape" << std::endl;
        std::cout << "1-nowa gra" << std::endl;
        std::cout << "2-wczytaj" << std::endl;
        std::cout << "3-wjscie" << std::endl;
        std::cin >> choose;

        if (choose == 1) {
            system("CLS");
            Player hero(1, 1);
            generate_enemy();
            Map* map = level(hero);

            main_loop(hero, *map);
            choose = 0;
            //system("CLS");

        }
        if (choose == 2) {
            system("CLS");
            int player_data[5];
            std::ifstream playerData("player.txt");
            std::string data;
            int ct = 0;
            int x_pos;
            int y_pos;
            int health;
            int power;
            int defense;
            std::string::size_type sz;
            std::string item[4] = { "", "", "", "" };
            while (std::getline(playerData, data))
            {
                switch (ct)
                {
                case 0:
                    x_pos = std::stoi(data, &sz);
                    break;
                case 1:
                    y_pos = std::stoi(data, &sz);
                    break;
                case 2:
                    health = std::stoi(data, &sz);
                    break;
                case 3:
                    power = std::stoi(data, &sz);
                    break;
                case 4:
                    defense = std::stoi(data, &sz);
                    break;
                default:
                    item[ct - 5] = data;
                    break;
                }
                ct++;
            }
            
            
            playerData.close();
            Player hero(x_pos, y_pos, true);
            hero.readData(health, power, defense, item);
            //hero.stats();

            std::ifstream enemyData("enemy.txt");
            int index = 0;
            ct = 1;
            while (std::getline(enemyData, data))
            {
                int tmp = ct % 5;
                switch (tmp)
                {
                case 1:
                    x_pos = std::stoi(data, &sz);
                    break;
                case 2:
                    y_pos = std::stoi(data, &sz);
                    break;
                case 3:
                    health = std::stoi(data, &sz);
                    break;
                case 4:
                    power = std::stoi(data, &sz);
                    break;
                case 0:
                    defense = std::stoi(data, &sz);
                    break;
                default:
                    break;
                }
                if (tmp == 0) {
                    enemy_arr[index].init(x_pos, y_pos, index);
                    enemy_arr[index].health = health;
                    enemy_arr[index].power = power;
                    enemy_arr[index].defense = defense;
                    index++;
                    
                }
                ct++;
            }
            enemyData.close();

            std::ifstream mapData("mapData.txt");
            int mct = 0;
            int height;
            int width;
            while (std::getline(mapData, data))
            {
                switch (mct)
                {
                case 0:
                    width = std::stoi(data, &sz);
                    break;
                case 1:
                    height = std::stoi(data, &sz);
                    break;
                default:
                    break;
                }
                mct++;
            }
            mapData.close();
            Map map(width, height, hero, enemy_arr, size, false);
            std::ifstream roomData("map.txt");
            int mdct = 1;
            index = 0;
            int x;
            int y;
            int s;
            while (std::getline(roomData, data))
            {
                int tmp = mdct % 3;
                switch (tmp)
                {
                case 1:
                    x = std::stoi(data, &sz);
                    break;
                case 2:
                    y = std::stoi(data, &sz);
                    break;
                case 0:
                    s = std::stoi(data, &sz);
                    break;
                default:
                    break;
                }
                if (tmp == 0) {
                    map.loadRoom(x, y, s, index);
                    index++;
                }
                mdct++;

            }
            mapData.close();
            map.update(hero, enemy_arr, size);
            main_loop(hero, map);
            choose = 0;

        }
        if (choose == 3) {
            std::cout << "zegnaj";
            break;
        }
    }

    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
