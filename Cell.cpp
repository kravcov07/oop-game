#include "Cell.hpp"
#include "Entity.hpp"

Cell::Cell(CellType type, bool is_occupied) : type_(type), is_occupied_(is_occupied) {}

int Cell::get_effect_value() const {
    switch (type_) {
        case CellType::HEALING_ZONE: return 10;
        case CellType::DAMAGE_ZONE:  return -5;
        default: return 0;
    }
}

void Cell::apply_effect(Entity& entity) const {
    int effect = get_effect_value();
    if (effect > 0) {
        entity.heal(effect);
    } else if (effect < 0) {
        entity.take_damage(-effect);
    }
}