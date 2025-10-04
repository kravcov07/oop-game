#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "GameField.hpp"
#include "Cell.hpp"

void test_player_functionality() {
    std::cout << "=== PLAYER FUNCTIONALITY TESTS ===" << std::endl;
    
    // Test 1: Player Creation
    std::cout << "\n--- Test 1: Player Creation ---" << std::endl;
    Player player(100, 5, 5);
    player.show_stats();
    
    // Test 2: Movement
    std::cout << "\n--- Test 2: Movement ---" << std::endl;
    std::cout << "Initial position: (" << player.get_x() << ", " << player.get_y() << ")" << std::endl;
    player.move(1, 0);
    std::cout << "After moving right: (" << player.get_x() << ", " << player.get_y() << ")" << std::endl;
    player.move(0, -1);
    std::cout << "After moving down: (" << player.get_x() << ", " << player.get_y() << ")" << std::endl;
    
    // Test 3: Weapon Switching
    std::cout << "\n--- Test 3: Weapon Switching ---" << std::endl;
    player.switchWeapon(WeaponType::BOW);
    player.switchWeapon(WeaponType::STAFF);
    player.switchWeapon(WeaponType::SWORD);
    player.switchWeapon(WeaponType::SWORD); // Attempt to switch to same weapon
    
    // Test 4: Damage and Healing
    std::cout << "\n--- Test 4: Damage and Healing ---" << std::endl;
    player.take_damage(30);
    std::cout << "After taking 30 damage: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    player.useHealthPotion();
    std::cout << "After using health potion: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    
    // Test 5: Health Potions Management
    std::cout << "\n--- Test 5: Health Potions Management ---" << std::endl;
    std::cout << "Initial potions: " << player.getHealthPotionCount() << std::endl;
    player.addHealthPotion();
    player.addHealthPotion();
    std::cout << "After adding 2 potions: " << player.getHealthPotionCount() << std::endl;
    
    // Test 6: Level System
    std::cout << "\n--- Test 6: Level System ---" << std::endl;
    std::cout << "Adding 120 score points:" << std::endl;
    player.addScore(120);
    player.show_stats();
    
    std::cout << "\nAdding 150 more score points:" << std::endl;
    player.addScore(150);
    player.show_stats();
    
    std::cout << std::endl; // Добавляем пустую строку для разделения
}

void test_enemy_functionality() {
    std::cout << "=== ENEMY FUNCTIONALITY TESTS ===" << std::endl;
    
    // Test 1: Enemy Creation
    std::cout << "\n--- Test 1: Enemy Creation ---" << std::endl;
    Enemy enemy(80, 3, 3);
    enemy.show_stats();
    
    // Test 2: Enemy Movement and Attack
    std::cout << "\n--- Test 2: Enemy Movement and Attack ---" << std::endl;
    Player player(100, 5, 5);
    std::cout << "Player position: (" << player.get_x() << ", " << player.get_y() << ")" << std::endl;
    std::cout << "Enemy position: (" << enemy.get_x() << ", " << enemy.get_y() << ")" << std::endl;
    
    // Simulate enemy AI movement toward player
    enemy.update(player);
    std::cout << "Enemy position after update: (" << enemy.get_x() << ", " << enemy.get_y() << ")" << std::endl;
    
    std::cout << std::endl;
}

void test_cell_functionality() {
    std::cout << "=== CELL FUNCTIONALITY TESTS ===" << std::endl;
    
    // Test 1: Basic Cell Types
    std::cout << "\n--- Test 1: Basic Cell Types ---" << std::endl;
    Cell empty_cell(CellType::EMPTY);
    Cell wall_cell(CellType::WALL);
    Cell healing_cell(CellType::HEALING_ZONE);
    Cell damage_cell(CellType::DAMAGE_ZONE);
    Cell slow_cell(CellType::SLOW_ZONE);
    
    std::cout << "Empty cell passable: " << empty_cell.is_passable() << std::endl;
    std::cout << "Wall cell passable: " << wall_cell.is_passable() << std::endl;
    std::cout << "Healing cell effect value: " << healing_cell.get_effect_value() << std::endl;
    std::cout << "Damage cell effect value: " << damage_cell.get_effect_value() << std::endl;
    
    // Test 2: Cell Occupancy
    std::cout << "\n--- Test 2: Cell Occupancy ---" << std::endl;
    std::cout << "Empty cell occupied: " << empty_cell.is_occupied() << std::endl;
    empty_cell.set_occupied(true);
    std::cout << "Empty cell after setting occupied: " << empty_cell.is_occupied() << std::endl;
    std::cout << "Empty cell passable when occupied: " << empty_cell.is_passable() << std::endl;
    
    std::cout << std::endl;
}

void test_game_field_functionality() {
    std::cout << "=== GAME FIELD FUNCTIONALITY TESTS ===" << std::endl;
    
    // Test 1: Field Creation
    std::cout << "\n--- Test 1: Field Creation ---" << std::endl;
    try {
        GameField field(15, 15);
        std::cout << "Field created successfully: " << field.get_width() << "x" << field.get_height() << std::endl;
        
        // Test 2: Cell Access
        std::cout << "\n--- Test 2: Cell Access ---" << std::endl;
        Cell& center_cell = field.get_cell(7, 7);
        std::cout << "Center cell type: " << static_cast<int>(center_cell.get_type()) << std::endl;
        std::cout << "Center cell passable: " << center_cell.is_passable() << std::endl;
        
        // Test 3: Border Walls
        std::cout << "\n--- Test 3: Border Walls ---" << std::endl;
        Cell& top_left_cell = field.get_cell(0, 0);
        Cell& bottom_right_cell = field.get_cell(14, 14);
        std::cout << "Top-left cell type (should be wall): " << static_cast<int>(top_left_cell.get_type()) << std::endl;
        std::cout << "Bottom-right cell type (should be wall): " << static_cast<int>(bottom_right_cell.get_type()) << std::endl;
        std::cout << "Top-left cell passable: " << top_left_cell.is_passable() << std::endl;
        
        // Test 4: Position Validation
        std::cout << "\n--- Test 4: Position Validation ---" << std::endl;
        std::cout << "Valid position (5,5): " << field.is_correct_valid(5, 5) << std::endl;
        std::cout << "Invalid position (-1,5): " << field.is_correct_valid(-1, 5) << std::endl;
        std::cout << "Invalid position (20,20): " << field.is_correct_valid(20, 20) << std::endl;
        
        // Test 5: Player Placement
        std::cout << "\n--- Test 5: Player Placement ---" << std::endl;
        auto player = std::make_unique<Player>(100, 0, 0);
        bool player_placed = field.place_player(std::move(player), 5, 5);
        std::cout << "Player placed at (5,5): " << player_placed << std::endl;
        if (field.get_player()) {
            std::cout << "Player health: " << field.get_player()->get_health() << std::endl;
        }
        
        // Test 6: Enemy Placement
        std::cout << "\n--- Test 6: Enemy Placement ---" << std::endl;
        auto enemy = std::make_unique<Enemy>(80, 0, 0);
        bool enemy_placed = field.place_enemy(std::move(enemy), 8, 8);
        std::cout << "Enemy placed at (8,8): " << enemy_placed << std::endl;
        std::cout << "Number of enemies: " << field.get_enemies().size() << std::endl;
        
        // Test 7: Cell Passability
        std::cout << "\n--- Test 7: Cell Passability ---" << std::endl;
        std::cout << "Empty cell passable: " << field.is_cell_passable(5, 5) << std::endl;
        std::cout << "Wall cell passable: " << field.is_cell_passable(0, 0) << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error creating field: " << e.what() << std::endl;
    }
    
    // Test invalid field size
    std::cout << "\n--- Test 8: Invalid Field Size ---" << std::endl;
    try {
        GameField invalid_field(5, 5); // Too small
    } catch (const std::exception& e) {
        std::cout << "Correctly caught error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
}

void test_weapon_functionality() {
    std::cout << "=== WEAPON FUNCTIONALITY TESTS ===" << std::endl;
    
    // Test 1: Weapon Creation
    std::cout << "\n--- Test 1: Weapon Creation ---" << std::endl;
    Weapon sword(WeaponType::SWORD);
    Weapon bow(WeaponType::BOW);
    Weapon staff(WeaponType::STAFF);
    Weapon fists(WeaponType::FISTS);
    
    std::cout << "Sword - Name: " << sword.getName() << ", Damage: " << sword.getDamage() << ", Range: " << sword.getRange() << std::endl;
    std::cout << "Bow - Name: " << bow.getName() << ", Damage: " << bow.getDamage() << ", Range: " << bow.getRange() << std::endl;
    std::cout << "Staff - Name: " << staff.getName() << ", Damage: " << staff.getDamage() << ", Range: " << staff.getRange() << std::endl;
    std::cout << "Fists - Name: " << fists.getName() << ", Damage: " << fists.getDamage() << ", Range: " << fists.getRange() << std::endl;
    
    // Test 2: Weapon Type Detection
    std::cout << "\n--- Test 2: Weapon Type Detection ---" << std::endl;
    std::cout << "Sword type: " << static_cast<int>(sword.getType()) << std::endl;
    std::cout << "Bow type: " << static_cast<int>(bow.getType()) << std::endl;
    
    // Test 3: Damage Modification
    std::cout << "\n--- Test 3: Damage Modification ---" << std::endl;
    std::cout << "Sword damage before: " << sword.getDamage() << std::endl;
    sword.setDamage(30);
    std::cout << "Sword damage after: " << sword.getDamage() << std::endl;
    
    std::cout << std::endl;
}

void test_combat_simulation() {
    std::cout << "=== COMBAT SIMULATION TESTS ===" << std::endl;
    
    // Test 1: Basic Combat
    std::cout << "\n--- Test 1: Basic Combat ---" << std::endl;
    Player player(100, 0, 0);
    Enemy enemy(80, 2, 0);
    
    std::cout << "Initial state:" << std::endl;
    std::cout << "Player:" << std::endl;
    player.show_stats();
    std::cout << "\nEnemy:" << std::endl;
    enemy.show_stats();
    
    // Simulate enemy attacking player
    std::cout << "\n--- Enemy attacks player ---" << std::endl;
    int enemy_damage = enemy.get_current_weapon().getDamage();
    std::cout << "Enemy deals " << enemy_damage << " damage to player" << std::endl;
    player.take_damage(enemy_damage);
    std::cout << "Player after attack:" << std::endl;
    player.show_stats();
    
    // Test 2: Healing Effects
    std::cout << "\n--- Test 2: Healing Effects ---" << std::endl;
    Cell healing_cell(CellType::HEALING_ZONE);
    player.take_damage(20);
    std::cout << "Player health after 20 damage: " << player.get_health() << std::endl;
    healing_cell.apply_effect(player);
    std::cout << "Player health after healing cell: " << player.get_health() << std::endl;
    
    // Test 3: Damage Zone Effects
    std::cout << "\n--- Test 3: Damage Zone Effects ---" << std::endl;
    Cell damage_cell(CellType::DAMAGE_ZONE);
    std::cout << "Player health before damage zone: " << player.get_health() << std::endl;
    damage_cell.apply_effect(player);
    std::cout << "Player health after damage zone: " << player.get_health() << std::endl;
    
    std::cout << std::endl;
}

int main() {
    std::cout << "=== COMPREHENSIVE GAME SYSTEM TESTS ===" << std::endl;
    std::cout << std::endl;
    
    try {
        test_player_functionality();
        test_enemy_functionality();
        test_cell_functionality();
        test_game_field_functionality();
        test_weapon_functionality();
        test_combat_simulation();
        
        std::cout << "=== ALL TESTS COMPLETED SUCCESSFULLY ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n!!! TEST FAILED WITH EXCEPTION: " << e.what() << " !!!" << std::endl;
        return 1;
    }
    
    return 0;
}