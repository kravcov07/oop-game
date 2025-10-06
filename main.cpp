#include <iostream>
#include <ctime>
#include "GameField.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

void test_place_entity() {

    std::cout << "=== TESTING place_entity FUNCTION ===" << std::endl;
    
    // Создаем поле 10x10
    GameField field(25, 25);
    
    // Тест 1: Размещение игрока
    std::cout << "\n1. Testing Player placement..." << std::endl;
    auto player = std::make_unique<Player>(100, 12, 12);
    bool result1 = field.place_entity(std::move(player), 12, 12);
    std::cout << "Player placement: " << (result1 ? "SUCCESS" : "FAILED") << std::endl;
    std::cout << "Player exists: " << (field.get_player() != nullptr ? "YES" : "NO") << std::endl;
    field.spawn_random_cell_type(20, CellType::WALL);  
    // Тест 2: Размещение врага
    std::cout << "\n2. Testing Enemy placement..." << std::endl;
    auto enemy = std::make_unique<Enemy>(50, 3, 3);
    bool result2 = field.place_entity(std::move(enemy), 3, 3);
    std::cout << "Enemy placement: " << (result2 ? "SUCCESS" : "FAILED") << std::endl;
    std::cout << "Enemies count: " << field.get_enemies().size() << std::endl;
    
    // Тест 3: Размещение башни
    std::cout << "\n3. Testing Tower placement..." << std::endl;
    auto tower = std::make_unique<Tower>(100, 7, 7, WeaponType::UNARMED, 2, 5);
    bool result3 = field.place_entity(std::move(tower), 7, 7);
    std::cout << "Tower placement: " << (result3 ? "SUCCESS" : "FAILED") << std::endl;
    std::cout << "Towers count: " << field.get_towers().size() << std::endl;
    
    // Тест 4: Попытка размещения в занятой клетке
    std::cout << "\n4. Testing occupied cell..." << std::endl;
    auto enemy2 = std::make_unique<Enemy>(50, 5, 5);
    bool result4 = field.place_entity(std::move(enemy2), 5, 5); // Занято игроком
    std::cout << "Occupied cell placement: " << (result4 ? "SUCCESS" : "FAILED") << std::endl;
    
    // Тест 5: Попытка размещения за пределами поля
    std::cout << "\n5. Testing out of bounds..." << std::endl;
    auto enemy3 = std::make_unique<Enemy>(50, 15, 15);
    bool result5 = field.place_entity(std::move(enemy3), 15, 15); // Вне поля
    std::cout << "Out of bounds placement: " << (result5 ? "SUCCESS" : "FAILED") << std::endl;
    
    // Тест 6: Отображение результата
    std::cout << "\n6. Final field state:" << std::endl;
    /* field.spawn_random_enemies(5); */
    field.spawn_random_towers(5);
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    field.update();
    
    field.draw_field();

    
    // Тест 7: Статистика
    std::cout << "\n7. Final statistics:" << std::endl;
    std::cout << "Total enemies: " << field.get_enemies().size() << std::endl;
    std::cout << "Total towers: " << field.get_towers().size() << std::endl;
    std::cout << "Player exists: " << (field.get_player() != nullptr ? "YES" : "NO") << std::endl;
    
    if (field.get_player()) {
        std::cout << "Player position: (" << field.get_player()->get_x() 
                  << ", " << field.get_player()->get_y() << ")" << std::endl;
    }
    
    std::cout << "\n=== TEST COMPLETED ===" << std::endl;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    test_place_entity();
    return 0;
}