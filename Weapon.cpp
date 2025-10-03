#include "Weapon.hpp"
#include <iostream>

std::string Weapon::getName() const { return name_; }
int Weapon::getDamage() const { return damage_; }
int Weapon::getRange() const { return range_; }
void Weapon::setDamage(int damage){ damage_ = damage; }

Weapon::Weapon(WeaponType type) {
    switch(type) {
        case WeaponType::SWORD:
            name_ = "Sword";
            damage_ = 25;
            range_ = 1;
            break;
        case WeaponType::BOW:
            name_ = "Bow";
            damage_ = 15;
            range_ = 5;
            break;
        case WeaponType::STAFF:
            name_ = "Staff";
            damage_ = 20;
            range_ = 3;
            break;
        default:
            name_ = "Fists";
            damage_ = 5;
            range_ = 1;
            break;
    }
}

WeaponType Weapon::getType() const {
    if (name_ == "Sword") return WeaponType::SWORD;
    if (name_ == "Bow") return WeaponType::BOW;
    if (name_ == "Staff") return WeaponType::STAFF;
    return WeaponType::FISTS;
}
