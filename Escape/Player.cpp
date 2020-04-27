#include "Player.h"
Player::Player(int x, int y) {
    std::cout << "# <- to twoj bohater" << std::endl;
    std::cout << "Czas zrobic swojego gracza, Najpierw nadaj mu imie: ";
    std::cin >> this->name;
    this->health = 10;
    this->defense = 0;
    this->power = 0;
    this->x_pos = x;
    this->y_pos = y;
    bool is_ok = true;
    for (int i = 5; i > 0; i--) {
        system("cls");
        if (!is_ok) {
            std::cout << "Nie wlasciwa liczba" << std::endl;
            i++;
            is_ok = true;
        }
        std::cout << "# <- to twoj bohante, ma obecnie \n " << this->power << " sily " << this->defense << " obbrony i "
            << this->health << " zrdrowia" << std::endl;
        std::cout << "1-by dodatac punkt do sily, 2-by dodatak punkt do obriony, Pozostalo ci " << i << " Punktow " << std::endl;
        int dec = 0;
        std::cin >> dec;
        if (dec == 1) {
            this->power += 1;
        }
        else if (dec == 2) {
            this->defense += 1;
        }
        else {
            is_ok = false;
        }
    }

}

void Player::stats() {

    std::cout << "\t\t\tzdrowi: " << this->health << std::endl;
    std::cout << "\t\t\tsila: " << this->power << std::endl;
    std::cout << "\t\t\tobrona: " << this->defense << std::endl;
    std::cout << "\t\t\tmove_point: " << this->current_point << std::endl;
    for (int i=0; i < this->max_back; i++) {
        if (this->back[i].name != "") {
            std::cout << "\t\t\tslot " << (i + 1) << this->back[i].name << std::endl;
        }
        else {
            std::cout << "\t\t\tslot " << (i + 1) << " pusty " << std::endl;
        }
    }
}


void Player::attack(Enemy& to_attack, char Map[20][40]) {
    int x_enemy = to_attack.x_pos;
    int y_enemy = to_attack.y_pos;
    bool can_attack = false;
    if ((y_enemy == this->y_pos && abs(this->x_pos - x_enemy) == 1) || (this->x_pos == x_enemy && abs(this->y_pos - y_enemy))) {
        int demage = this->power - to_attack.defense;
        if (demage <= 0) {
            demage = 1;
        }
        to_attack.health -= demage;
        this->current_point--;
        if (to_attack.health <= 0) {
            to_attack.current_state = dead;
            to_attack.look = 'm';
        }
    }

    
}



