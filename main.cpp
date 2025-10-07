#include <iostream>
#include <ctime>
#include "GameField.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

void wait_moves(){
    std::cout << "Press Enter to continue";
    std::cin.ignore();
    std::cin.get();
}

void game() {

    GameField field(25, 25);

    auto player = std::make_unique<Player>(100, 12, 12);
    bool result1 = field.place_entity(std::move(player), 12, 12);

    field.spawn_random_towers(1);
    field.spawn_random_enemies(1);

    field.spawn_random_cell_type(10, CellType::SLOW_ZONE);
    field.spawn_random_cell_type(30, CellType::WALL);
    
    std::string command;
    int dx, dy;
    
    system("cls");
    field.draw_field();
    field.get_player()->show_stats();
    
    while(field.get_player()->is_alive()){
        bool action_performed = false;

        if(field.get_player()->is_on_slow_cell(field)){
            std::cout << "You on slow cell, you skeep one move" << std::endl;
            field.update();
            wait_moves();
        }
        
        std::cout << "Command: ";

        if (!(std::cin >> command)) {
            if (std::cin.eof()) {
                std::cout << "\nGame exited" << std::endl;
                return;
            }
            break;
        }
        
        if (command == "move" || command == "w" || command == "a" || command == "s" || command == "d") {
            char direction;
            if (command.length() == 1) {
                direction = command[0];
            } else {
                std::cin >> direction;
            }
            
            switch (direction) {
            case 'w': action_performed = field.get_player()->move(field, 0, -1); break;
            case 'a': action_performed = field.get_player()->move(field, -1, 0); break;
            case 's': action_performed = field.get_player()->move(field, 0, 1); break;
            case 'd': action_performed = field.get_player()->move(field, 1, 0); break;
            default: 
                std::cout << "Invalid direction! Use w/a/s/d" << std::endl;
                wait_moves();
                continue;
            }
            command = "move";
        }
        else if (command == "attack" || command == "e") {
            std::cin >> dx >> dy;
            if(!field.get_player()->attack(field, dx, dy)) continue;
        }
        else if (command == "weapon" || command == "r") {
            std::string weapon_input;
            std::cin >> weapon_input;
            
            WeaponType new_weapon;
            
            if (weapon_input.length() == 1) {
                int weapon_choice = weapon_input[0] - '0';
                
                switch(weapon_choice) {
                    case 1: new_weapon = WeaponType::SWORD; break;
                    case 2: new_weapon = WeaponType::BOW; break;
                    case 3: new_weapon = WeaponType::STAFF; break;
                    case 4: new_weapon = WeaponType::FISTS; break;
                    default:
                        std::cout << "Invalid weapon number! Use 1-4" << std::endl;
                        continue;
                }
            } else {
                if (weapon_input == "sword") new_weapon = WeaponType::SWORD;
                else if (weapon_input == "bow") new_weapon = WeaponType::BOW;
                else if (weapon_input == "staff") new_weapon = WeaponType::STAFF;
                else if (weapon_input == "fists") new_weapon = WeaponType::FISTS;
                else {
                    std::cout << "Invalid weapon! Available: sword, bow, staff, fists" << std::endl;
                    continue;
                }
            }
            field.get_player()->switch_weapon(new_weapon);
        }
        else if (command == "potion" || command == "p") {
            field.get_player()->use_health_potion();
        }
        else if (command == "stat" || command == "stats") {
            field.get_player()->show_stats();
        }
        else if (command == "quit" || command == "q") {
            std::cout << "Goodbye!" << std::endl;
            return;
        }
        else if (command == "help") {
            std::cout << "\n=== AVAILABLE COMMANDS ===" << std::endl;
            std::cout << "MOVEMENT:" << std::endl;
            std::cout << "  w, a, s, d  OR  move [w/a/s/d]" << std::endl;
            std::cout << "COMBAT:" << std::endl;
            std::cout << "  e [dx] [dy]  OR  attack [dx] [dy]" << std::endl;
            std::cout << "WEAPONS:" << std::endl;
            std::cout << "  r [1-4]      OR  weapon [sword/bow/staff/fists]" << std::endl;
            std::cout << "  Weapons: 1-sword, 2-bow, 3-staff, 4-fists" << std::endl;
            std::cout << "ITEMS:" << std::endl;
            std::cout << "  p            OR  potion" << std::endl;
            std::cout << "INFO:" << std::endl;
            std::cout << "  stat         - detailed statistics" << std::endl;
            std::cout << "  enemy/list - show all enemies and towers stats" << std::endl;
            std::cout << "  help         - this message" << std::endl;
            std::cout << "  q            OR  quit" << std::endl;
        }
        else if (command == "enemy" || command == "list") {
            field.show_enemy_stats();
        }
        else {
            std::cout << "Unknown command '" << command << "'. Type 'help' for commands list." << std::endl;
            continue;
        }

        if(command != "move"){
            wait_moves();
        }

        if (action_performed && command != "help" && 
             command != "stat" && command != "enemy") {
            field.update();
            system("cls");
            field.draw_field();
        }

    }
    
    std::cout << "=== GAME OVER ===" << std::endl;
    std::cout << "Player died! Final stats:" << std::endl;
    field.get_player()->show_stats();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    game();

    return 0;
}