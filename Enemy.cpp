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
    
    if (position_x_ < player.get_x()) dx = 1;
    else if (position_x_ > player.get_x()) dx = -1;
    
    if (position_y_ < player.get_y()) dy = 1;
    else if (position_y_ > player.get_y()) dy = -1;
    
    if (dx != 0) {
        move(dx, 0, player);
    } else if (dy != 0) {
        move(0, dy, player);
    }
}

void Enemy::show_stats() const {
    std::cout << "=== ENEMY STATS ===" << std::endl;
    Entity::show_stats();
}

void Enemy::update() {}