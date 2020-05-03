// Escape.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Player.h"
#include "map.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int size = 10;
Enemy enemy_arr[10];

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

Map level(Player& hero) {
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

    Map map(40, 20, hero, enemy_arr, size);
    return map;
}

void player_movment(Map& map, Player& hero) {
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
            player_movment(map, hero);
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
                    hero.current_point = 3;
                }
            }
            else {
                int player_pos[2] = { hero.x_pos, hero.y_pos };
                for (int i = 0; i < size; i++) {
                    if (enemy_arr[i].current_state == attact) {
                        enemy_arr[i].attact_state(map.map, player_pos);
                    }
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
        std::cout << "Witam w grze The Escape" << std::endl;
        std::cout << "1-nowa gra" << std::endl;
        std::cout << "2-wczytaj" << std::endl;
        std::cout << "3-wjscie" << std::endl;
        std::cin >> choose;
        if (choose == 1 || choose == 2 || choose == 3) {
            is_good = true;
        }
    }
    if (choose == 1) {
        system("CLS");
        Player hero(1,1);
        generate_enemy();
        Map map =  level(hero);

        main_loop(hero, map);
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
