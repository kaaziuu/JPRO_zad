// Escape.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <time.h>
#include "Player.h"
#include "map.h"

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

void level(Player& hero) {
    const int size = 10;
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

    Map map(40, 20, hero, enemy_arr, size);
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
        level(hero);
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
