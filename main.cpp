#include <iostream>
#include "GameField.hpp"
#include "Tower.hpp"

int main() {
    GameField field(20, 20);
    
    // Создаем 3 башни
    auto t1 = std::unique_ptr<Tower>(new Tower(100, 5, 5, field));
    auto t2 = std::unique_ptr<Tower>(new Tower(100, 10, 10, field));
    auto t3 = std::unique_ptr<Tower>(new Tower(100, 15, 15, field));
    
    field.place_tower(std::move(t1), 5, 5);
    field.place_tower(std::move(t2), 10, 10);
    field.place_tower(std::move(t3), 15, 15);
    
    std::cout << "Создано башен: " << field.get_towers().size() << std::endl;
    
    for (int i = 0; i < 30; i++) {
        for (auto& tower : field.get_towers()) {
            if (tower->spawn_enemy()) {
                std::cout << "Башня " << tower->get_x() << "," << tower->get_y() 
                          << " заспавнила врага!" << std::endl;
            }
        }
    }
    
    std::cout << "Всего врагов: " << field.get_enemies().size() << std::endl;
    field.draw_minimal();
    
    return 0;
}