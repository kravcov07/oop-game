#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "Cell.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class GameField {
public:
    GameField(int width, int height);
    GameField(const GameField& other); // Конструктор копирования
    GameField(GameField&& other); // Конструктор перемещения
    
    // Операторы присваивания
    GameField& operator=(const GameField& other); // Копирующее присваивание
    GameField& operator=(GameField&& other); // Перемещающее присваивание
    
    ~GameField();
    
    // Геттеры
    int get_width() const { return width_; }
    int get_height() const { return height_; }
    Cell& get_cell(int x, int y);
    Player* get_player() const { return player_.get(); }
    const std::vector<std::unique_ptr<Enemy>>& get_enemies() const { return enemies_; }

    bool is_correct_valid(int x, int y) const;
    bool is_cell_occupied(int x, int y) const;
    bool is_cell_passable(int x, int y) const;
    
    void set_dimensions(int width, int height);

    bool place_player(std::unique_ptr<Player> player, int x, int y);
    bool place_enemy(std::unique_ptr<Enemy> enemy, int x, int y);
    
    
private:
    int width_;
    int height_;
    Cell** cells_;
    std::unique_ptr<Player> player_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    
    static bool are_dimensions_valid(int width, int height);
    void initialize_cells();
    void cleanup_cells();
    void copy_from(const GameField& other);
    void move_from(GameField&& other) noexcept;
};

#endif