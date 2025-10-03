#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"
#include "Player.hpp"

class Enemy : public Entity {
public:
    Enemy(int health, int startX, int startY);
    
    // Уникальные методы врага
    void move(int dx, int dy, Player& player);
    void update(Player& player); // AI логика
    
    // Переопределенные методы
    void showStats() const override;
    void update() override;

private:
    // Дополнительные поля для AI
    int turnsSinceLastMove_;
};

#endif