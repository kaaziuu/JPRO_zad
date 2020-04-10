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
        enemy_arr[i].init(x, y);
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
        enemy_arr[i].init(x, y);
    }

    Map map(40, 20, hero, enemy_arr, size);
    return map;
}


// main loop
void main_loop(Player& hero, Map& map) {
    bool is_play = true;
    float time_deley = 0.3;
    float delta_time=2000;
    time_t old_time= 0;
    time_t current_time = 0;
    while (is_play)
    {
        old_time = current_time;
        current_time = time(NULL);
        delta_time += current_time - old_time;
        if (delta_time > time_deley && !hero.is_fight){ 
            delta_time = 0;
            // player movment
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
