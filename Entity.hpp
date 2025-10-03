#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Weapon.hpp"

class Entity {
public:
    Entity(int health, int x, int y, WeaponType weapon);
    virtual ~Entity() = default;
    
    // Геттеры
    int getHealth() const;
    int getX() const;
    int getY() const;
    int getMaxHealth() const;
    Weapon getCurrentWeapon();
    
    // Сеттеры
    void setPosition(int x, int y);
    void setHealth(int health);
    
    // Основные методы
    void takeDamage(int damage);
    void heal(int amount);
    void healFull();
    bool isAlive() const;
    virtual void showStats() const; // виртуальный для переопределения
    
    // Чисто виртуальные методы (должны быть реализованы в производных классах)
    virtual void update() = 0; // для AI или логики обновления

protected:
    int health_;
    int maxHealth_;
    Weapon weapon_;
    int x_;
    int y_;
};

#endif