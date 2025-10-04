#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Weapon.hpp"

class Entity {
public:
    Entity(int health, int x, int y, WeaponType weapon);
    virtual ~Entity() = default;
    
    // Геттеры
    int get_health() const { return health_; }
    int get_x() const { return position_x_; }
    int get_y() const { return position_y_; }
    int get_max_health() const { return max_health_; }
    Weapon get_current_weapon() { return weapon_; }
    
    // Сеттеры
    void set_position(int x, int y);
    void set_health(int health);
    
    // Основные методы
    void take_damage(int damage);
    void heal(int amount);
    void heal_full();
    bool is_alive() const;
    virtual void show_stats() const; // виртуальный для переопределения
    
    // Чисто виртуальные методы (должны быть реализованы в производных классах)
    virtual void update() = 0; // для AI или логики обновления

protected:
    int health_;
    int max_health_;
    Weapon weapon_;
    int position_x_;
    int position_y_;
};

#endif