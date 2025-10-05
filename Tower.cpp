#include "Tower.hpp"

void Tower::show_stats() const {
    std::cout << "=== TOWER STATS ===" << std::endl;
    Entity::show_stats();
    std::cout << "Spawn Range: " << range_spawn_ 
              << "\nCooldown: " << cooldown_ << "/" << max_cooldown_ << std::endl;
}

bool Tower::spawn_enemy(){
    if (!can_spawn()) return false;
    
    int attempts = 0;
    while(attempts < 20) {
        attempts++;
        
        int dx = rand() % (range_spawn_ * 2 + 1) - range_spawn_;
        int dy = rand() % (range_spawn_ * 2 + 1) - range_spawn_;
        
        int x = get_x() + dx;
        int y = get_y() + dy;
        
        double distance = sqrt(dx*dx + dy*dy);
        if(distance <= sqrt(pow(range_spawn_, 2) + 1) && 
           game_field_.is_cell_passable(x, y) &&
           !game_field_.is_cell_occupied(x, y)){
            
            auto enemy = std::make_unique<Enemy>(50, x, y);
            game_field_.place_enemy(std::move(enemy), x, y);
            reset_cooldown();
            return true;
        }
    }
    return false;
}

void Tower::update() {
    reduce_cooldown();
}