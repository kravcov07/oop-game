#include "Entity.hpp"

Entity::Entity(int health, int x, int y, WeaponType weapon)
    : health_(health), max_health_(health), position_x_(x), position_y_(y),
      weapon_(weapon) {}

void Entity::set_position(int x, int y) {
    position_x_ = x;
    position_y_ = y;
}

void Entity::set_health(int health) {
    if (health < 0) health = 0;
    if (health > max_health_) health = max_health_;
    health_ = health;
}

void Entity::take_damage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

void Entity::heal(int amount) {
    health_ += amount;
    if (health_ > max_health_) {
        health_ = max_health_;
    }
}

void Entity::heal_full() {
    health_ = max_health_;
}

bool Entity::is_alive() const {
    return health_ > 0;
}

void Entity::show_stats() const {
    std::cout << "Health: " << health_ << "/" << max_health_
              << "\nPosition: (" << position_x_ << ", " << position_y_ << ")" 
              << "\nWeapon: " << weapon_.getName()
              << " (Damage: " << weapon_.getDamage() 
              << ", Range: " << weapon_.getRange() << ")" << std::endl;
}