#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Weapon.hpp"

class GameField;

class Entity {
public:
    Entity(int health, int x, int y, WeaponType weapon);
    virtual ~Entity() = default;
    
    int get_health() const { return health_; }
    int get_x() const { return position_x_; }
    int get_y() const { return position_y_; }
    int get_max_health() const { return max_health_; }
    Weapon get_weapon() { return weapon_; }
    
    void set_position(int x, int y);
    void set_health(int health);
    
    void take_damage(int damage);
    void heal(int amount);
    void heal_full();
    bool is_alive() const;
    virtual void show_stats() const;
    
    virtual void update() = 0;
    bool can_attack(GameField& game_field, int dx, int dy);

protected:
    bool is_line_of_sight_clear(GameField& game_field, int start_x, int start_y, int end_x, int end_y) const;
    int health_;
    int max_health_;
    Weapon weapon_;
    int position_x_;
    int position_y_;
};

#endif