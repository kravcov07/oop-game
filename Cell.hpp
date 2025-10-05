#ifndef CELL_H
#define CELL_H

enum class CellType {
    EMPTY,
    WALL,
    SLOW_ZONE,
    HEALING_ZONE,
    DAMAGE_ZONE
};

class Entity;

class Cell {
public:
    Cell(CellType type = CellType::EMPTY, Entity* entity = nullptr);
    
    CellType get_type() const { return type_; }
    bool is_occupied() const { return entity_ != nullptr; }
    bool is_passable() const { return type_ != CellType::WALL && !is_occupied(); }
    
    int get_effect_value() const;
    
    void set_entity(Entity* entity) { entity_ = entity; }
    Entity* get_entity() const { return entity_; }
    void clear_entity() { entity_ = nullptr; }
    
    void set_type(CellType type) { type_ = type; }
    
    void apply_effect() const;

private:
    CellType type_;
    Entity* entity_;
};

#endif