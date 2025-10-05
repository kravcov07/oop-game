#include "GameField.hpp"

void test_enemy_ai_with_obstacles() {
    std::cout << "=== ENEMY AI WITH OBSTACLES TEST ===" << std::endl;
    
    // Создаем поле 10x10
    GameField field(10, 10);
    
    // Создаем AFK игрока в углу
    auto player = std::make_unique<Player>(100, 1, 1);
    field.place_player(std::move(player), 1, 1);
    
    // Создаем врага в противоположном углу
    auto enemy = std::make_unique<Enemy>(50, 8, 8);
    field.place_enemy(std::move(enemy), 8, 8);
    
    // Создаем стену между игроком и врагом
    for (int y = 3; y <= 6; y++) {
        field.get_cell(5, y).set_type(CellType::WALL);
    }
    
    std::cout << "\nInitial field state:" << std::endl;
    std::cout << "Player at (1,1), Enemy at (8,8), Wall at x=5 from y=3 to y=6" << std::endl;
    field.draw_minimal();
    
    // Запускаем много обновлений врага
    int max_updates = 30;
    int update_count = 0;
    
    std::cout << "\n=== STARTING ENEMY AI UPDATES ===" << std::endl;
    
    while (update_count < max_updates && field.get_enemies().size() > 0) {
        update_count++;
        
        // Получаем врага и игрока
        auto& enemies = field.get_enemies();
        if (enemies.empty()) break;
        
        Enemy& enemy_ref = *enemies[0];
        Player* player_ptr = field.get_player();
        
        if (!player_ptr) break;
        
        std::cout << "\n--- Update " << update_count << " ---" << std::endl;
        std::cout << "Enemy position: (" << enemy_ref.get_x() << ", " << enemy_ref.get_y() << ")" << std::endl;
        std::cout << "Player position: (" << player_ptr->get_x() << ", " << player_ptr->get_y() << ")" << std::endl;
        std::cout << "Distance: " << 
            std::abs(enemy_ref.get_x() - player_ptr->get_x()) + 
            std::abs(enemy_ref.get_y() - player_ptr->get_y()) << std::endl;
        
        // Обновляем врага
        enemy_ref.update(*player_ptr, field);
        
        // Показываем поле после обновления
        field.draw_minimal();
        
        // Проверяем, дошел ли враг до игрока
        if (std::abs(enemy_ref.get_x() - player_ptr->get_x()) <= 1 && 
            std::abs(enemy_ref.get_y() - player_ptr->get_y()) <= 1) {
            std::cout << "ENEMY REACHED PLAYER! Combat initiated." << std::endl;
            std::cout << "Player health: " << player_ptr->get_health() << std::endl;
            break;
        }
        
        // Небольшая задержка для читаемости (опционально)
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    std::cout << "\n=== TEST COMPLETED ===" << std::endl;
    std::cout << "Total updates: " << update_count << std::endl;
    if (field.get_player()) {
        std::cout << "Final player health: " << field.get_player()->get_health() << std::endl;
    }
    std::cout << "Enemies remaining: " << field.get_enemies().size() << std::endl;
}

int main() {
    // ... существующий код ...
    
    test_enemy_ai_with_obstacles();
    
    return 0;
}