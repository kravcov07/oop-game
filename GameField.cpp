#include "GameField.hpp"

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
        player_ = std::make_unique<Player>(*other.player_);
    }

    for(const auto& enemy: other.enemies_){
        enemies_.push_back(std::make_unique<Enemy>(*enemy));
    }
}

void GameField::move_from(GameField&& other) noexcept{
    set_dimensions(other.get_width(), other.get_height());
    cells_ = other.cells_;
    player_ = std::move(other.player_);
    enemies_ = std::move(other.enemies_);

    other.set_dimensions(0, 0);
    other.cells_ = nullptr;
}

bool GameField::are_dimensions_valid(int width, int height){
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 25;
    return width >= MIN_SIZE && width <= MAX_SIZE\
            && height >= MIN_SIZE && height <= MAX_SIZE;
}

bool GameField::is_correct_valid(int x, int y) const {
    return x >= 0 && x <= width_ && y >= 0 && y <= height_;
}

bool GameField::is_cell_occupied(int x, int y) const{
    if(!is_correct_valid(x, y)){
        return false;
    }
    return cells_[y][x].is_occupied();
}

Cell& GameField::get_cell(int x, int y){
    if(!is_correct_valid(x, y)){
        throw std::out_of_range("Position is out of field bounds");
    }

    return cells_[y][x];
}

bool GameField::place_player(std::unique_ptr<Player> player, int x, int y) {
    if (!is_correct_valid(x, y) || is_cell_occupied(x, y)) {
        return false;
    }
    
    player_ = std::move(player);
    cells_[y][x].set_occupied(true);
    return true;
}

bool GameField::place_enemy(std::unique_ptr<Enemy> enemy, int x, int y){
    if(are_dimensions_valid(x, y)){
        return false;
    }

    enemies_.push_back(std::move(enemy));
    cells_[y][x].set_occupied(true);

    return true;
}

bool GameField::is_cell_passable(int x, int y) const {
    if (!is_correct_valid(x, y)) return false;
    return cells_[y][x].is_passable();
}