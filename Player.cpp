#include "Player.hpp"

int Player::getScore() const { return score_; }
int Player::getLevel() const { return level_; }
int Player::getHealthPotionCount() const { return health_potions_count_; }

Player::Player(int health, int startX, int startY)
    : Entity(health, startX, startY, WeaponType::SWORD),
      score_(0), level_(0), score_for_next_level_(100), health_potions_count_(3) {}

Player::~Player() = default;

void Player::move(int dx, int dy) {
    position_x_ += dx;
    position_y_ += dy;
}

void Player::addScore(int points) {
    score_ += points;
    
    while (score_ >= score_for_next_level_) {
        level_++;
        score_ -= score_for_next_level_;
        
        score_for_next_level_ += 50;
        
        max_health_ = static_cast<int>(max_health_ * 1.1);
        heal_full();
        weapon_.setDamage(weapon_.getDamage()*1.25);
        
        std::cout << "LEVEL UP! Now level " << level_ 
                  << "\nHealth: " << health_ << "/" << max_health_
                  << "\nDamage: " << weapon_.getDamage() << std::endl;
    }
}

void Player::switchWeapon(WeaponType newWeaponType) {
    if(newWeaponType == weapon_.getType()){
        std::cout << "This weapon is already selected" << std::endl;
        return;
    }

    weapon_ = Weapon(newWeaponType);
    weapon_.setDamage(weapon_.getDamage()*pow(1.25, level_));
    
    std::cout << "Switched to: " << weapon_.getName() 
              << " (Damage: " << weapon_.getDamage() 
              << ", Range: " << weapon_.getRange() << ")" << std::endl;
}

void Player::useHealthPotion() {
    if (health_potions_count_ > 0) {
        health_potions_count_--;
        heal(30);
        std::cout << "Used health potion. Health: " << health_ << std::endl;
    } else {
        std::cout << "No health potions!" << std::endl;
    }
}

void Player::addHealthPotion() {
    health_potions_count_++;
    std::cout << "Health potion added. Total: " << health_potions_count_ << std::endl;
}

void Player::show_stats() const {
    std::cout << "=== PLAYER STATS ===" << std::endl;
    Entity::show_stats();
    
    std::cout << "Health Potions: " << health_potions_count_ 
              << "\nLVL: " << level_ << '/' << score_for_next_level_ <<std::endl;
}

void Player::update() {
    if (level_ >= 10 && health_ < max_health_) {
        int regenAmount = level_ / 10;
        heal(regenAmount);
    }
}