#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <cmath>

enum class WeaponType {
    UNARMED,
    FISTS,
    SWORD,
    BOW,
    STAFF
};

class Weapon {
private:
    std::string name_;
    int damage_value_;
    int attack_range_;
public:
    Weapon(WeaponType type);
    std::string getName() const;
    int getDamage() const;
    int getRange() const;
    WeaponType getType() const;
    void setDamage(int damage);
};

#endif