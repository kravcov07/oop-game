#include "Enemy.hpp"
#include <cstdlib> // для rand()

Enemy::Enemy(int health, int startX, int startY)
    : Entity(health, startX, startY, WeaponType::FISTS),
        turns_since_last_move_(0) {}

void Enemy::move(int dx, int dy, Player& player) {
    int newX = get_x() + dx;
    int newY = get_y() + dy;
    
    if (newX == player.get_x() && newY == player.get_y()) {
        player.take_damage(weapon_.getDamage());
        std::cout << "Enemy attacks player for " << weapon_.getDamage() << " damage!" << std::endl;
    } else {
        position_x_ = newX;
        position_y_ = newY;
    }
}

void Enemy::update(Player& player) {
    int dx = 0, dy = 0;
    
    if (get_x() < player.get_x()) dx = 1;
    else if (get_x() > player.get_x()) dx = -1;
    
    if (get_y() < player.get_y()) dy = 1;
    else if (get_y() > player.get_y()) dy = -1;
    
    // Простое движение к игроку
    if (dx != 0 || dy != 0) {
        // В реальной реализации нужно проверять возможность движения
        set_position(get_x() + dx, get_y() + dy);
    }
    
    // Атака, если рядом с игроком
    int distance = std::abs(get_x() - player.get_x()) + std::abs(get_y() - player.get_y());
    if (distance <= 1) {
        player.take_damage(get_current_weapon().getDamage());
    }
}

void Enemy::show_stats() const {
    std::cout << "=== ENEMY STATS ===" << std::endl;
    Entity::show_stats();
}

void Enemy::update() {}