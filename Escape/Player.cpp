#include "Player.h"
Player::Player(int x, int y, bool reload) {
    this->x_pos = x;
    this->y_pos = y;
    //this->back = (Game_item*)malloc(this->backsize * sizeof(Game_item));
    this->back = new Game_item[this->backsize];
//    for (int i = 0; i < this->backsize; i++) {
  //      new((void*)&back[i]) Game_item("brak", 0, 0, false);
   // }
    if (!reload) {
        std::cout << "# <- to twoj bohater" << std::endl;
        std::cout << "Czas zrobic swojego gracza, Najpierw nadaj mu imie: ";

        std::cin >> this->name;
        this->health = 20;
        this->defense = 0;
        this->power = 0;

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

}

Player::~Player() {
    for (int i = 0; i< 4; i++) {
        this->back[i].~Game_item();
    }
    delete[] this->back;
}

void Player::stats() {

    std::cout << "\t\t\tzdrowi: " << this->health << std::endl;
    std::cout << "\t\t\tsila: " << this->power << std::endl;
    std::cout << "\t\t\tobrona: " << this->defense << std::endl;
    std::cout << "\t\t\tmove_point: " << this->current_point << std::endl;
    for (int i=0; i < this->backsize; i++) {
        if (this->back[i].name != "") {
            std::cout << "\t\t\tslot " << (i + 1) << this->back[i].name << std::endl;
        }
        else {
            std::cout << "\t\t\tslot " << (i + 1) << " pusty " << std::endl;
        }
    }
}


int Player::attack(Enemy& to_attack, char **Map) {
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
 //           to_attack.current_state = dead;
 //           to_attack.look = 'm';
            Map[to_attack.y_pos][to_attack.x_pos] = 'm';
            return to_attack.id;
        }
    }
    return -1;

    
}

void Player::take_hit(int demage)
{
    demage -= this->defense;
    if (demage <= 0) {
        demage = 1;
    }
    this->health -= demage;
}

void Player::readData(int health, int power, int defense, std::string[])
{
    this->health = health;
    this->power = power;
    this->defense = defense;
}

void Player::pickup(Game_item& new_item, int slot) {
    this->back[slot] = new_item;
    this->power += new_item.attack;
    this->defense += new_item.defense;
}

