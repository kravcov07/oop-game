#include "Player.hpp"

int Player::getScore() const { return score_; }
int Player::getLevel() const { return lvl_; }
int Player::getHealthPotionCount() const { return healthPotions_; }

Player::Player(int health, int startX, int startY)
    : Entity(health, startX, startY, WeaponType::SWORD),
      score_(0), lvl_(0), scoreForNextLevel_(100), healthPotions_(3) {}

Player::~Player() = default;

void Player::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

void Player::addScore(int points) {
    score_ += points;
    
    while (score_ >= scoreForNextLevel_) {
        lvl_++;
        score_ -= scoreForNextLevel_;
        
        scoreForNextLevel_ += 50;
        
        maxHealth_ = static_cast<int>(maxHealth_ * 1.1);
        healFull();
        weapon_.setDamage(weapon_.getDamage()*1.25);
        
        std::cout << "LEVEL UP! Now level " << lvl_ 
                  << "\nHealth: " << health_ << "/" << maxHealth_
                  << "\nDamage: " << weapon_.getDamage() << std::endl;
    }
}

void Player::switchWeapon(WeaponType newWeaponType) {
    if(newWeaponType == weapon_.getType()){
        std::cout << "Уже выбрано это оружие" << std::endl;
        return;
    }

    weapon_ = Weapon(newWeaponType);
    weapon_.setDamage(weapon_.getDamage()*pow(1.25, lvl_));
    
    std::cout << "Switched to: " << weapon_.getName() 
              << " (Damage: " << weapon_.getDamage() 
              << ", Range: " << weapon_.getRange() << ")" << std::endl;
}

void Player::useHealthPotion() {
    if (healthPotions_ > 0) {
        healthPotions_--;
        heal(30);
        std::cout << "Used health potion. Health: " << health_ << std::endl;
    } else {
        std::cout << "No health potions!" << std::endl;
    }
}

void Player::addHealthPotion() {
    healthPotions_++;
    std::cout << "Health potion added. Total: " << healthPotions_ << std::endl;
}

void Player::showStats() const {
    std::cout << "=== PLAYER STATS ===" << std::endl;
    Entity::showStats();
    
    std::cout << "Health Potions: " << healthPotions_ 
              << "\nLVL: " << lvl_ << '/' << scoreForNextLevel_ <<std::endl;
}

void Player::update() {
    if (lvl_ >= 10 && health_ < maxHealth_) {
        int regenAmount = lvl_ / 10;
        heal(regenAmount);
    }
}