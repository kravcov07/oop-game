#include "Player.hpp"
#include "GameField.hpp"

Player::~Player() = default;

void Player::move(GameField& game_field, int dx, int dy) {
    if(abs(dx) > 1 || abs(dy) > 1){
        throw std::invalid_argument("Invalid coords to move");
    }
    int x = get_x();
    int y = get_y();
    if(game_field.is_cell_passable(x + dx, y + dy)){
        game_field.move_entity(x, y, x + dx, y + dy);
        set_position(x + dx, y + dy);
    }else{}
}

bool Player::attack(GameField& game_field, int dx, int dy){
    int damage = game_field.get_player()->get_weapon().get_damage();

    if(can_attack(game_field, dx, dy)){
        auto entity = game_field.get_cell(get_x() + dx, get_y() + dy).get_entity();
        if(entity){
            entity->take_damage(damage);
            return true;
        }
    }else{
        return false;
    }

    return false;
}

void Player::add_score(int points) {
    score_ += points;
    
    while (score_ >= score_for_next_level_) {
        level_++;
        score_ -= score_for_next_level_;
        
        score_for_next_level_ += 50;
        
        max_health_ = static_cast<int>(max_health_ * 1.1);
        heal_full();
        weapon_.set_damage(weapon_.get_damage()*1.25);
        
        std::cout << "LEVEL UP! Now level " << level_ 
                  << "\nHealth: " << health_ << "/" << max_health_
                  << "\nDamage: " << weapon_.get_damage() << std::endl;
    }
}

void Player::switch_weapon(WeaponType newWeaponType) {
    if(newWeaponType == weapon_.get_type()){
        std::cout << "This weapon is already selected" << std::endl;
        return;
    }

    weapon_ = Weapon(newWeaponType);
    weapon_.set_damage(weapon_.get_damage()*pow(1.25, level_));
    
    std::cout << "Switched to: " << weapon_.get_name() 
              << " (Damage: " << weapon_.get_damage() 
              << ", Range: " << weapon_.get_range() << ")" << std::endl;
}

void Player::use_health_potion(){
    if (health_potions_count_ > 0) {
        health_potions_count_--;
        heal(30);
        std::cout << "Used health potion. Health: " << health_ << std::endl;
    } else {
        std::cout << "No health potions!" << std::endl;
    }
}

void Player::add_health_potion() {
    health_potions_count_++;
    std::cout << "Health potion added. Total: " << health_potions_count_ << std::endl;
}

void Player::show_stats() const {
    std::cout << "=== PLAYER STATS ===" << std::endl;
    Entity::show_stats();
    
    std::cout << "Score: " << score_ 
              << "/" << score_for_next_level_
              << "\nLevel: " << level_
              << "\nHealth Potions: " << health_potions_count_ << std::endl;
}

void Player::update() {
    if (health_ < max_health_) {
        int regenAmount = level_ / 10;
        heal(regenAmount);
    }
}