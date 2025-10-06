#include "Cell.hpp"
#include "Entity.hpp"

int Cell::get_effect_value() const {
    switch (type_) {
        case CellType::HEALING_ZONE: return 10;
        case CellType::DAMAGE_ZONE:  return -5;
        default: return 0;
    }
}

void Cell::apply_effect() const {
    if (entity_ == nullptr) return;
    
    int effect = get_effect_value();
    if (effect > 0) {
        entity_->heal(effect);
    } else if (effect < 0) {
        entity_->take_damage(-effect);
    }
}