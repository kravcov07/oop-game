#include "GameField.hpp"
#include "Tower.hpp"

void GameField::set_dimensions(int width, int height){
    if (!are_dimensions_valid(height, width)){
        throw std::invalid_argument("Invalid field dimensions");
    }
    width_ = width;
    height_ = height;
}

GameField::GameField(int width, int height)
    : width_(width), height_(height), cells_(nullptr) {
        if (!are_dimensions_valid(height, width)){
            throw std::invalid_argument("Invalid field dimensions");
        }

        initialize_cells();
    }
    
GameField::GameField(const GameField& other)
    : width_(other.get_width()), height_(other.get_height()), cells_(nullptr){
    
    copy_from(other);
}

GameField::GameField(GameField&& other){
    move_from(std::move(other));
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        cleanup_cells();
        width_ = other.width_;
        height_ = other.height_;
        copy_from(other);
    }
    return *this;
}

GameField& GameField::operator=(GameField&& other){
    if (this != &other) {
        cleanup_cells();
        move_from(std::move(other));
    }
    return *this;
}

GameField::~GameField(){
    cleanup_cells();
}

void GameField::initialize_cells(){
    cells_ = new Cell*[height_];   
    for(int i = 0; i < height_; i++){
        cells_[i] = new Cell[width_];

        for(int j = 0; j < width_; j++){
            if(i == 0 || i == height_ - 1 || j == 0 || j == width_ - 1){
                cells_[i][j].set_type(CellType::WALL);
            }
        }
    }
}

void GameField::cleanup_cells(){
    if(cells_){
        for(int i = 0; i < height_; i++){
            delete[] cells_[i];
       }
       delete[] cells_;
       cells_ = nullptr;
    }
}

void GameField::copy_from(const GameField& other){
    initialize_cells();
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < width_; j++){
            cells_[i][j] = other.cells_[i][j];
        }
    }

    if(other.get_player()){
        player_ = std::unique_ptr<Player>(new Player(*other.player_));
    }

    for(const auto& enemy: other.enemies_){
        enemies_.push_back(std::unique_ptr<Enemy>(new Enemy(*enemy)));
    }
    
    for(const auto& tower: other.towers_){
        towers_.push_back(std::unique_ptr<Tower>(new Tower(*tower)));
    }
}

void GameField::move_from(GameField&& other) noexcept{
    set_dimensions(other.get_width(), other.get_height());
    cells_ = other.cells_;
    player_ = std::move(other.player_);
    enemies_ = std::move(other.enemies_);
    towers_ = std::move(other.towers_);

    other.set_dimensions(0, 0);
    other.cells_ = nullptr;
}

bool GameField::are_dimensions_valid(int width, int height){
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 25;
    return width >= MIN_SIZE && width <= MAX_SIZE\
            && height >= MIN_SIZE && height <= MAX_SIZE;
}

bool GameField::is_coordinates_valid(int x, int y) const {
    return x >= 0 && x <= width_ && y >= 0 && y <= height_;
}

bool GameField::is_cell_occupied(int x, int y) const{
    if(!is_coordinates_valid(x, y)){
        return false;
    }
    return cells_[y][x].is_occupied();
}

Cell& GameField::get_cell(int x, int y){
    if(!is_coordinates_valid(x, y)){
        throw std::out_of_range("Position is out of field bounds");
    }

    return cells_[y][x];
}

bool GameField::place_player(std::unique_ptr<Player> player, int x, int y) {
    if (!is_coordinates_valid(x, y) || is_cell_occupied(x, y)) {
        return false;
    }
    
    player_ = std::move(player);
    cells_[y][x].set_entity(player_.get());
    return true;
}

bool GameField::place_enemy(std::unique_ptr<Enemy> enemy, int x, int y){
    if(!is_coordinates_valid(x, y) || is_cell_occupied(x, y)){
        return false;
    }

    Enemy* enemy_ptr = enemy.get();
    enemies_.push_back(std::move(enemy));
    cells_[y][x].set_entity(enemy_ptr);
    
    return true;
}

bool GameField::place_tower(std::unique_ptr<Tower> tower, int x, int y) {
    if (!is_coordinates_valid(x, y) || is_cell_occupied(x, y)) {
        return false;
    }
    
    Tower* tower_ptr = tower.get();
    towers_.push_back(std::move(tower));
    cells_[y][x].set_entity(tower_ptr);
    return true;
}

bool GameField::move_entity(int from_x, int from_y, int to_x, int to_y) {
    if (!is_coordinates_valid(from_x, from_y) || !is_coordinates_valid(to_x, to_y)) {
        return false;
    }
    
    Cell& from_cell = get_cell(from_x, from_y);
    Cell& to_cell = get_cell(to_x, to_y);
    
    if (!from_cell.is_occupied() || to_cell.is_occupied()) {
        return false;
    }
    
    // Перемещаем указатель
    Entity* entity = from_cell.get_entity();
    to_cell.set_entity(entity);
    from_cell.clear_entity();
    
    return true;
}

bool GameField::is_cell_passable(int x, int y) const {
    if (!is_coordinates_valid(x, y)) return false;
    return cells_[y][x].is_passable();
}

void GameField::remove_dead_entity(Entity* dead_entity) {
    cells_[dead_entity->get_y()][dead_entity->get_x()].clear_entity();
    
    for (auto it = enemies_.begin(); it != enemies_.end(); ++it) {
        if (it->get() == dead_entity) {
            enemies_.erase(it);
            return;
        }
    }
    
    for (auto it = towers_.begin(); it != towers_.end(); ++it) {
        if (it->get() == dead_entity) {
            towers_.erase(it);
            return;
        }
    }
}

void GameField::draw_minimal() const {
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            const Cell& cell = cells_[y][x];
            Entity* entity = cell.get_entity();
            
            if (entity) {
                // Проверяем тип сущности
                if (dynamic_cast<Player*>(entity)) {
                    std::cout << "P ";
                } else if (dynamic_cast<Enemy*>(entity)) {
                    std::cout << "E ";
                } else if (dynamic_cast<Tower*>(entity)) {
                    std::cout << "T ";  // Tower отображается как 'T'
                } else {
                    std::cout << "O ";
                }
            } else {
                // Нет сущности - показываем тип клетки
                switch (cell.get_type()) {
                    case CellType::WALL: std::cout << "# "; break;
                    case CellType::HEALING_ZONE: std::cout << "+ "; break;
                    case CellType::DAMAGE_ZONE: std::cout << "x "; break;
                    case CellType::SLOW_ZONE: std::cout << "~ "; break;
                    default: std::cout << ". "; break;
                }
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nPlayer: " << (player_ ? "YES" : "NO");
    std::cout << " | Enemies: " << enemies_.size();
    std::cout << " | Towers: " << towers_.size() << std::endl;
}