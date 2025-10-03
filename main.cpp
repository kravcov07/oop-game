#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"

int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ PLAYER ===" << std::endl;
    
    // Тест 1: Создание игрока
    std::cout << "\n--- Тест 1: Создание игрока ---" << std::endl;
    Player player(100, 0, 0);
    player.showStats();
    
    // Тест 2: Движение
    std::cout << "\n--- Тест 2: Движение ---" << std::endl;
    player.move(1, 0);
    player.showStats();
    
    
    // Тест 4: Получение урона и лечение
    std::cout << "\n--- Тест 4: Урон и лечение ---" << std::endl;
    player.takeDamage(30);
    player.showStats();
    player.useHealthPotion();
    player.showStats();
    
    // Тест 5: Добавление зелий
    std::cout << "\n--- Тест 5: Добавление зелий ---" << std::endl;
    player.addHealthPotion();
    player.addHealthPotion();
    std::cout << "Зелья здоровья: " << player.getHealthPotionCount() << std::endl;
    
    // Тест 6: Система уровней
    std::cout << "\n--- Тест 6: Система уровней ---" << std::endl;
    std::cout << "Добавляем 120 очков:" << std::endl;
    player.addScore(120);
    player.showStats();
    
    std::cout << "\nДобавляем еще 150 очков:" << std::endl;
    player.addScore(150);
    player.showStats();
    
    // Тест 7: Бой с врагом
    std::cout << "\n--- Тест 7: Бой с врагом ---" << std::endl;
    Enemy enemy(80, 0, 0);
    enemy.showStats();
    
    std::cout << "\nВраг атакует:" << std::endl;
    enemy.move(1, 0, player); // Враг движется к игроку
    player.showStats();

    // Тест 3: Смена оружия
    std::cout << "\n--- Тест 3: Смена оружия ---" << std::endl;
    player.switchWeapon(WeaponType::BOW);
    player.switchWeapon(WeaponType::STAFF);
    player.switchWeapon(WeaponType::SWORD);
    player.switchWeapon(WeaponType::SWORD); // Попытка выбрать то же оружие
    
    std::cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << std::endl;
    
    return 0;
}