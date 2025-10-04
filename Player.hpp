#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include "Weapon.hpp"

class Player : public Entity {
public:
    Player(int health, int startX, int startY);
    ~Player();
    
    int getScore() const;
    int getLevel() const;
    int getHealthPotionCount() const;

    void move(int dx, int dy);
    void addScore(int points);
    void useHealthPotion();
    void addHealthPotion();
    void switchWeapon(WeaponType newWeaponType);
    
    // Переопределенные методы
    void show_stats() const override;
    void update() override;
    
private:
    int score_;
    int score_for_next_level_;
    int level_;
    int health_potions_count_;
    static const int POTION_HEAL_AMOUNT = 50;
};

#endif