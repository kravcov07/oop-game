#ifndef TOWER_H
#define TOWER_H

#include "GameField.hpp"

class Tower: public Entity{
public:
    Tower(int health, int x, int y,
            WeaponType weapon = WeaponType::UNARMED,
            int range_spawn = 3,
            int max_cooldown = 10)
        : Entity(health, x, y, weapon),
            range_spawn_(range_spawn),
            cooldown_(0),
            max_cooldown_(max_cooldown) {}
    
    ~Tower() = default;

    void reduce_cooldown() { if(cooldown_ > 0) cooldown_--; }
    bool can_spawn() const { return cooldown_ <= 0; }
    void reset_cooldown() { cooldown_ = max_cooldown_; }
    int get_range_spawn() const { return range_spawn_; }
    
    void show_stats() const override;
    void update(GameField& game_field);
    bool spawn_enemy(GameField& game_field);
    
    void update() override;

private:
    int range_spawn_;
    int cooldown_;
    int max_cooldown_;
};

#endif