#include "Enemy.hpp"
#include <cstdlib> // для rand()

Enemy::Enemy(int health, int startX, int startY)
    : Entity(health, startX, startY, WeaponType::FISTS),
        turnsSinceLastMove_(0) {}

void Enemy::move(int dx, int dy, Player& player) {
    int newX = x_ + dx;
    int newY = y_ + dy;
    
    if (newX == player.getX() && newY == player.getY()) {
        player.takeDamage(weapon_.getDamage());
        std::cout << "Enemy attacks player for " << weapon_.getDamage() << " damage!" << std::endl;
    } else {
        x_ = newX;
        y_ = newY;
    }
}

void Enemy::update(Player& player) {
    int dx = 0, dy = 0;
    
    if (x_ < player.getX()) dx = 1;
    else if (x_ > player.getX()) dx = -1;
    
    if (y_ < player.getY()) dy = 1;
    else if (y_ > player.getY()) dy = -1;
    
    if (dx != 0) {
        move(dx, 0, player);
    } else if (dy != 0) {
        move(0, dy, player);
    }
}

void Enemy::showStats() const {
    std::cout << "=== ENEMY STATS ===" << std::endl;
    Entity::showStats();
}

void Enemy::update() {}