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

void GameField::move_from(GameField&& other){
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
    return x >= 0 && x <= width_ - 1 && y >= 0 && y <= height_ - 1;
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

bool GameField::is_cell_passable(int x, int y) const {
    if (!is_coordinates_valid(x, y)) return false;
    return cells_[y][x].is_passable();
}


bool GameField::place_entity(std::unique_ptr<Entity> entity, int x, int y) {
    if (!is_cell_passable(x, y)) {
        return false;
    }

    Entity* entity_ptr = entity.get();
    
    if (dynamic_cast<Player*>(entity_ptr)) {
        player_ = std::unique_ptr<Player>(static_cast<Player*>(entity.release()));
    } else if (dynamic_cast<Enemy*>(entity_ptr)) {
        enemies_.push_back(std::unique_ptr<Enemy>(static_cast<Enemy*>(entity.release())));
    } else if (dynamic_cast<Tower*>(entity_ptr)) {
        towers_.push_back(std::unique_ptr<Tower>(static_cast<Tower*>(entity.release())));
    } else {
        return false;
    }
    
    cells_[y][x].set_entity(entity_ptr);
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
    
    Entity* entity = from_cell.get_entity();
    to_cell.set_entity(entity);
    from_cell.clear_entity();
    
    return true;
}

void GameField::spawn_random_towers(int count) {
    int spawned = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = count * 10;
    
    while (spawned < count && attempts < MAX_ATTEMPTS) {
        attempts++;
        
        int x = rand() % width_;
        int y = rand() % height_;
        
        if (is_cell_passable(x, y)) {
            auto tower = std::make_unique<Tower>(100, x, y);
            if (place_entity(std::move(tower), x, y)) {
                spawned++;
            }
        }
    }    
}

void GameField::spawn_random_enemies(int count) {
    int spawned = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = count * 10;
    
    while (spawned < count && attempts < MAX_ATTEMPTS) {
        attempts++;
        
        int x = rand() % width_;
        int y = rand() % height_;
    
        if (is_cell_passable(x, y)) {
            auto enemy = std::make_unique<Enemy>(50, x, y);
            if (place_entity(std::move(enemy), x, y)) {
                spawned++;
            }
        }
    }
}

void GameField::spawn_random_cell_type(int count, CellType cell_type){
    int spawned = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = count * 10;
    
    while (spawned < count && attempts < MAX_ATTEMPTS) {
        attempts++;
        
        int x = rand() % width_;
        int y = rand() % height_;
        
        if (is_cell_passable(x, y)) {
            if (player_ && player_->get_x() == x && player_->get_y() == y) {
                continue;
            }
            
            cells_[y][x].set_type(cell_type);
            spawned++;
        }
    }
    
}

void GameField::update() {
    auto enemy_it = enemies_.begin();
    while (enemy_it != enemies_.end()) {
        if (!(*enemy_it)->is_alive()) {
            int x = (*enemy_it)->get_x();
            int y = (*enemy_it)->get_y();

            if(player_){
                player_->add_score((*enemy_it)->get_max_health()/2);
            }

            cells_[y][x].clear_entity();

            enemy_it = enemies_.erase(enemy_it);
        } else {
            (*enemy_it)->update(*this);
            ++enemy_it;
        }
    }
    
    auto tower_it = towers_.begin();
    while (tower_it != towers_.end()) {
        if (!(*tower_it)->is_alive()) {
            int x = (*tower_it)->get_x();
            int y = (*tower_it)->get_y();

            if(player_){
                player_->add_score((*tower_it)->get_max_health()/2);
            }
            
            cells_[y][x].clear_entity();

            tower_it = towers_.erase(tower_it);
        } else {
            (*tower_it)->update(*this);
            ++tower_it;
        }
    }
}

void GameField::draw_field() const {
    std::cout << "   ";
    for (int x = 0; x < width_; x++) {
        std::cout << x << (x < 10 ? "  " : " ");
    }
    std::cout << '\n';
    
    for (int y = 0; y < height_; y++) {
        std::cout << y << (y < 10 ? "  " : " ");
        
        for (int x = 0; x < width_; x++) {
            const Cell& cell = cells_[y][x];
            Entity* entity = cell.get_entity();
            
            if (entity) {
                if (dynamic_cast<Player*>(entity)) {
                    std::cout << "P";
                } else if (dynamic_cast<Enemy*>(entity)) {
                    std::cout << "E";
                } else if (dynamic_cast<Tower*>(entity)) {
                    std::cout << "T";
                } else {
                    std::cout << "O";
                }
            } else {
                switch (cell.get_type()) {
                    case CellType::WALL: std::cout << "#"; break;
                    case CellType::HEALING_ZONE: std::cout << "+"; break;
                    case CellType::DAMAGE_ZONE: std::cout << "x"; break;
                    case CellType::SLOW_ZONE: std::cout << "~"; break;
                    default: std::cout << "."; break;
                }
            }
            std::cout << "  ";
        }
        std::cout << "\n";
    }
}

void GameField::show_enemy_stats() const {
    std::cout << "=== ENEMY STATS ===" << std::endl;
    
    for (const auto& enemy : enemies_) {
        if (enemy->is_alive()) {
            std::cout << "Enemy (" << enemy->get_x() << ", " << enemy->get_y() 
                      << ") HP: " << enemy->get_health() << "/" << enemy->get_max_health() << std::endl;
        }
    }
    
    for (const auto& tower : towers_) {
        if (tower->is_alive()) {
            std::cout << "Tower (" << tower->get_x() << ", " << tower->get_y() 
                      << ") HP: " << tower->get_health() << "/" << tower->get_max_health() << std::endl;
        }
    }
    
    if (enemies_.empty() && towers_.empty()) {
        std::cout << "No enemies or towers on the field" << std::endl;
    }
}