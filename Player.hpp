#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(int health, int startX, int startY)
        : Entity(health, startX, startY, WeaponType::SWORD),
            score_(0),
            level_(0),
            score_for_next_level_(100),
            health_potions_count_(3) {}

    ~Player();
    
    int get_score() const { return score_; }
    int get_level() const { return level_; }
    int get_health_potion_count() const { return health_potions_count_; }

    void move(GameField& game_field, int dx, int dy);
    bool attack(GameField& game_field, int dx, int dy);
    void add_score(int points);
    void use_health_potion();
    void add_health_potion();
    void switch_weapon(WeaponType newWeaponType);
    
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