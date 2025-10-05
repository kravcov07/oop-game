#ifndef ENEMY_H
#define ENEMY_H

#include "Player.hpp"

class GameField;

class Enemy : public Entity {
public:
    Enemy(int health, int startX, int startY);
    
    void move(Player& player, GameField& game_field);
    void update(Player& player, GameField& game_field);
    

    void show_stats() const override;
    void update() override;

private:
    int turns_since_last_move_;
};

#endif