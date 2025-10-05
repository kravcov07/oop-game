#include "Enemy.hpp"
#include "GameField.hpp"

Enemy::Enemy(int health, int startX, int startY)
    : Entity(health, startX, startY, WeaponType::FISTS),
        turns_since_last_move_(0) {}

void Enemy::move(Player& player, GameField& game_field) {
    int dx = 0, dy = 0;
    
    if (get_x() < player.get_x()) dx = 1;
    else if (get_x() > player.get_x()) dx = -1;
    
    if (get_y() < player.get_y()) dy = 1;
    else if (get_y() > player.get_y()) dy = -1;
    
    if (dx != 0 || dy != 0) {
        int attempts = 4;
        int pos_x = get_x() + dx;
        int pos_y = get_y() + dy;
        while(attempts-- > 0){
            if(game_field.is_cell_passable(pos_x, pos_y)){
                game_field.move_entity(get_x(), get_y(), pos_x, pos_y);
                set_position(pos_x, pos_y);
                break;
            }else{
                if(game_field.is_cell_passable(pos_x+1, pos_y)) pos_x++;
                else if(game_field.is_cell_passable(pos_x-1, pos_y)) pos_x--;
                if(game_field.is_cell_passable(pos_x, pos_y+1)) pos_y++;
                else if(game_field.is_cell_passable(pos_x, pos_y-1)) pos_y--;
            }
        }
    }
    
    int distance = std::abs(get_x() - player.get_x()) + std::abs(get_y() - player.get_y());
    if (distance <= 1) {
        player.take_damage(get_current_weapon().getDamage());
    }
}

void Enemy::update(Player& player, GameField& game_field) {
    if(is_alive()){
        move(player, game_field);
    }else{
        game_field.remove_dead_entity(this);
    }
}

void Enemy::show_stats() const {
    std::cout << "=== ENEMY STATS ===" << std::endl;
    Entity::show_stats();
}

void Enemy::update() {}