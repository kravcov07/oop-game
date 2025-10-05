#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <cmath>
#include <iostream>

enum class WeaponType {
    UNARMED,
    FISTS,
    SWORD,
    BOW,
    STAFF
};

class Weapon {
public:
    Weapon(WeaponType type);
    WeaponType getType() const;

    std::string getName() const { return name_; }
    int getDamage() const { return damage_value_; }
    int getRange() const { return attack_range_; }
    void setDamage(int damage){ damage_value_ = damage; }

private:
    std::string name_;
    int damage_value_;
    int attack_range_;
};

#endif