#ifndef CELL_H
#define CELL_H

enum class CellType {
    EMPTY,          // Обычная клетка
    WALL,           // Стена (непроходимая)
    SLOW_ZONE,      // Замедляющая клетка
    HEALING_ZONE,   // Лечащая зона
    DAMAGE_ZONE     // Повреждающая зона
};

class Cell {
public:
    Cell(CellType type = CellType::EMPTY, bool is_occupied = false);
    
    CellType get_type() const { return type_; }
    bool is_occupied() const { return is_occupied_; }
    bool is_passable() const { return type_ != CellType::WALL && !is_occupied_; }
    
    int get_effect_value() const;
    
    void set_occupied(bool occupied) { is_occupied_ = occupied; }
    void set_type(CellType type) { type_ = type; }
    
    void apply_effect(class Entity& entity) const;

private:
    CellType type_;
    bool is_occupied_;
};

#endif