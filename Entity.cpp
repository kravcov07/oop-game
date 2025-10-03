#include "Entity.hpp"

Entity::Entity(int health, int x, int y, WeaponType weapon)
    : health_(health), maxHealth_(health), x_(x), y_(y),
      weapon_(weapon) {}

int Entity::getHealth() const { return health_; }
int Entity::getX() const { return x_; }
int Entity::getY() const { return y_; }
int Entity::getMaxHealth() const { return maxHealth_; }
Weapon Entity::getCurrentWeapon() { return weapon_; }

void Entity::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Entity::setHealth(int health) {
    if (health < 0) health = 0;
    if (health > maxHealth_) health = maxHealth_;
    health_ = health;
}

void Entity::takeDamage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

void Entity::heal(int amount) {
    health_ += amount;
    if (health_ > maxHealth_) {
        health_ = maxHealth_;
    }
}

void Entity::healFull() {
    health_ = maxHealth_;
}

bool Entity::isAlive() const {
    return health_ > 0;
}

void Entity::showStats() const {
    std::cout << "Health: " << health_ << "/" << maxHealth_
              << "\nPosition: (" << x_ << ", " << y_ << ")" 
              << "\nWeapon: " << weapon_.getName()
              << " (Damage: " << weapon_.getDamage() 
              << ", Range: " << weapon_.getRange() << ")" << std::endl;
}